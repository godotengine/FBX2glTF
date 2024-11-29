# FBX2glTF

> [!NOTE]
>
> As of Godot 4.3, FBX2glTF is no longer used. The engine now relies on
> [ufbx](https://github.com/ufbx/ufbx) instead, which is a built-in library
> instead of an external command-line tool.
>
> As such, **in Godot 4.3 or later, you no longer need to set up FBX2glTF**
> to import FBX scenes.
>
> We no longer actively maintain this repository as we won't be needing it
> going forward. If you want to build on top of it for your own use cases,
> feel free to fork it.

A command-line tool for the conversion of 3D model assets on the FBX file format
to the glTF file format.

This is a fork of [facebookincubator/FBX2glTF](https://github.com/facebookincubator/FBX2glTF)
to fix issues for the needs of [Godot Engine](https://godotengine.org/).

Change skinning-weights to 4 with `--skinning-weights 4`, if your engine does not support the 8 bone weights feature.

Change the default import of the engine to be different from 30 fps if needed, with `--anim-framerate (bake24|bake30|bake60)`.

## License

The FBX2glTF command line tool is distributed under the 3-clause BSD license.

Precompiled binaries include **proprietary code** from the Autodesk FBX SDK 2020,
which is distributed under the
[Autodesk LICENSE AND SERVICES AGREEMENT](https://github.com/godotengine/FBX2glTF/releases/latest/download/FBX-SDK-License.rtf).

**By downloading and using this tool, you agree to the terms of that Autodesk
proprietary license.**

## Platform binaries

Check the [latest release](https://github.com/godotengine/FBX2glTF/releases/latest/)
for the last precompiled binaries for Linux, macOS, and Windows.

- Linux x86_64: [`FBX2glTF-linux-x86_64.zip`](https://github.com/godotengine/FBX2glTF/releases/latest/download/FBX2glTF-linux-x86_64.zip)
  * It is built on Ubuntu 20.04 and requires glibc 2.31 or newer.
- macOS x86_64: [`FBX2glTF-macos-x86_64.zip`](https://github.com/godotengine/FBX2glTF/releases/latest/download/FBX2glTF-macos-x86_64.zip)
  * It should work fine for macOS ARM64 too using Rosetta 2.
- Windows x86_64: [`FBX2glTF-windows-x86_64.zip`](https://github.com/godotengine/FBX2glTF/releases/latest/download/FBX2glTF-windows-x86_64.zip)
  * [**Requires Microsot Visual C++ Redistributable.**](https://learn.microsoft.com/en-us/cpp/windows/latest-supported-vc-redist)

There are also artifacts of the latest commit for Linux, macOS, and Windows
in the [GitHub Actions](https://github.com/godotengine/FBX2glTF/actions) tab.

## Build instructions

Reference the [GitHub workflow](https://github.com/godotengine/FBX2glTF/blob/master/.github/workflows/build.yaml).
