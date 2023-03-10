// © Copyright 2014-2022, Juan Linietsky, Ariel Manzur and the Godot community (CC-BY 3.0)
#include "libfbx2gltf.h"

#include <godot_cpp/classes/editor_file_system_import_format_support_query.hpp>
#include <godot_cpp/classes/editor_scene_format_importer.hpp>
#include <godot_cpp/classes/gltf_document.hpp>
#include <godot_cpp/classes/gltf_state.hpp>
#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/project_settings.hpp>
#include <godot_cpp/classes/ref.hpp>
#include <godot_cpp/classes/resource_importer.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/error_macros.hpp>

#include "FBX2glTF.h"
#include "fbx/Fbx2Raw.hpp"
#include "gltf/Raw2Gltf.hpp"
#include "utils/File_Utils.hpp"
#include "utils/String_Utils.hpp"

#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

using namespace godot;

bool verboseOutput = true;

Variant EditorSceneFormatImporterFBX2GLTF::_get_option_visibility(
    const String& p_path,
    bool p_for_animation,
    const String& p_option) const {
  return true;
}

void EditorSceneFormatImporterFBX2GLTF::_get_import_options(const String& p_path) {}

Object* EditorSceneFormatImporterFBX2GLTF::_import_scene(
    const String& p_path,
    uint32_t p_flags,
    const Dictionary& p_options) {
  // Get global paths for source and sink.
  const String imported_folder = String("res://.godot/imported/");
  const String source_global = ProjectSettings::get_singleton()->globalize_path(p_path);
  std::string inputPath = source_global.utf8().get_data();
  const String sink =
      imported_folder + p_path.get_file().get_basename() + String("-") + p_path.md5_text() + String(".gltf");
  const String sink_global = ProjectSettings::get_singleton()->globalize_path(sink);
  std::string outputPath = sink_global.utf8().get_data();

  GltfOptions gltfOptions;

  gltfOptions.usePBRMetRough = true;
  gltfOptions.embedResources = false;
  gltfOptions.outputBinary = false;
  const String sink_binary = p_path.get_basename() + String("-") +
      p_path.md5_text() + ".bin";
  const String sink_binary_global = ProjectSettings::get_singleton()->globalize_path(sink_binary);
  const std::string binaryPath = sink_binary_global.utf8().get_data();
  gltfOptions.extBufferFilename = sink_binary_global.get_file().utf8().get_data();

  const auto& suffix = FileUtils::GetFileSuffix(outputPath);

  ModelData* data_render_model = nullptr;
  RawModel raw;

  if (verboseOutput) {
    fmt::printf("Loading FBX File: %s\n", inputPath);
  }
  if (!LoadFBXFile(raw, inputPath, {"png", "jpg", "jpeg"}, gltfOptions)) {
    fmt::fprintf(stderr, "ERROR:: Failed to parse FBX: %s\n", inputPath);
    return nullptr;
  }

  raw.Condense(gltfOptions.maxSkinningWeights, gltfOptions.normalizeSkinningWeights);
  raw.TransformGeometry(gltfOptions.computeNormals);

  std::ofstream outStream;
  const auto streamStart = outStream.tellp();

  outStream.open(outputPath, std::ios::trunc | std::ios::ate | std::ios::out | std::ios::binary);
  if (outStream.fail()) {
    fmt::fprintf(stderr, "ERROR:: Couldn't open file for writing: %s\n", outputPath.c_str());
    return nullptr;
  }
  const String sink_folder_global =
      ProjectSettings::get_singleton()->globalize_path(p_path.get_base_dir());
  std::string outputFolderPath = sink_folder_global.utf8().get_data();
  data_render_model = Raw2Gltf(outStream, outputFolderPath, raw, gltfOptions);
  outStream.flush();
  FILE* fp = fopen(binaryPath.c_str(), "wb");
  if (fp == nullptr) {
    fmt::fprintf(stderr, "ERROR:: Couldn't open file '%s' for writing.\n", binaryPath);
    delete data_render_model;
    return nullptr;
  }

  if (data_render_model->binary->empty() == false) {
    const unsigned char* binaryData = &(*data_render_model->binary)[0];
    unsigned long binarySize = data_render_model->binary->size();
    if (fwrite(binaryData, binarySize, 1, fp) != 1) {
      fmt::fprintf(
          stderr, "ERROR: Failed to write %lu bytes to file '%s'.\n", binarySize, binaryPath);
      fclose(fp);
      delete data_render_model;
      return nullptr;
    }
    fclose(fp);
    fmt::printf("Wrote %lu bytes of binary data to %s.\n", binarySize, binaryPath);
  }
  delete data_render_model;

  // Import the generated glTF.

  Ref<GLTFDocument> gltf;
  gltf.instantiate();
  Ref<GLTFState> state;
  state.instantiate();
  Error err = gltf->append_from_file(sink, state, p_flags, p_path.get_base_dir());
  if (err != OK) {
    return nullptr;
  }

  return gltf->generate_scene(
      state,
      (float)p_options["animation/fps"],
      (bool)p_options["animation/trimming"],
      (bool)p_options["animation/remove_immutable_tracks"]);
}

PackedStringArray EditorSceneFormatImporterFBX2GLTF::_get_extensions() const {
  PackedStringArray extensions;
  extensions.push_back("fbx");
  return extensions;
}

uint32_t EditorSceneFormatImporterFBX2GLTF::_get_import_flags() const {
  return EditorSceneFormatImporter::IMPORT_SCENE | EditorSceneFormatImporter::IMPORT_ANIMATION;
}
