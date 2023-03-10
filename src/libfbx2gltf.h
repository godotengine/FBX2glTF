// © Copyright 2014-2022, Juan Linietsky, Ariel Manzur and the Godot community (CC-BY 3.0)
#ifndef SUMMATOR_CLASS_H
#define SUMMATOR_CLASS_H

// We don't need windows.h in this plugin but many others do and it throws up on itself all the time
// So best to include it and make sure CI warns us when we use something Microsoft took for their
// own goals....
#ifdef WIN32
#include <windows.h>
#endif

#include <godot_cpp/classes/editor_scene_format_importer.hpp>
#include <godot_cpp/classes/ref.hpp>

using namespace godot;

extern bool verboseOutput;

class EditorSceneFormatImporterFBX2GLTF : public EditorSceneFormatImporter {
  GDCLASS(EditorSceneFormatImporterFBX2GLTF, EditorSceneFormatImporter);

 protected:
  static void _bind_methods() {}

 public:
  virtual uint32_t _get_import_flags() const override;
  virtual PackedStringArray _get_extensions() const override;
  virtual Object* _import_scene(const String& p_path, uint32_t p_flags, const Dictionary& p_options)
      override;

  virtual void _get_import_options(const String& p_path) override;

  virtual Variant _get_option_visibility(
      const String& p_path,
      bool p_for_animation,
      const String& p_option) const override;
};

#endif // SUMMATOR_CLASS_H
