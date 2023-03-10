@tool
extends EditorPlugin

var import_plugin


func _enter_tree():
	import_plugin = EditorSceneFormatImporterFBX2GLTF.new()
	add_scene_format_importer_plugin(import_plugin, true)


func _exit_tree():
	remove_scene_format_importer_plugin(import_plugin)
	import_plugin = null
