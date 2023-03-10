#include "register_types.h"
#include "libfbx2gltf.h"
#include <gdextension_interface.h>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/core/defs.hpp>
#include <godot_cpp/godot.hpp>

using namespace godot;

class EditorSceneFormatImporterFBX2GLTF;

void initialize_fbx2gltf_types(ModuleInitializationLevel p_level)
{
	if (p_level != MODULE_INITIALIZATION_LEVEL_EDITOR) {
		return;
	}
	ClassDB::register_class<EditorSceneFormatImporterFBX2GLTF>();
}

void uninitialize_fbx2gltf_types(ModuleInitializationLevel p_level) {
	if (p_level != MODULE_INITIALIZATION_LEVEL_EDITOR) {
		return;
	}
}

extern "C"
{
	// Initialization.

	GDExtensionBool GDE_EXPORT fbx2gltf_library_init(const GDExtensionInterface *p_interface, const GDExtensionClassLibraryPtr p_library, GDExtensionInitialization *r_initialization)
	{
		GDExtensionBinding::InitObject init_obj(p_interface, p_library, r_initialization);

		init_obj.register_initializer(initialize_fbx2gltf_types);
		init_obj.register_terminator(uninitialize_fbx2gltf_types);
		init_obj.set_minimum_library_initialization_level(MODULE_INITIALIZATION_LEVEL_EDITOR);

		return init_obj.init();
	}
}
