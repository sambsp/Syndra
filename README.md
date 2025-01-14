<img align="left" width="150" src="https://github.com/ErfanMo77/Syndra/blob/master/Syndra-Editor/assets/Logo/GITLOGO.png"/>

# Syndra Engine
Syndra is an early-stage 3D game engine with a focus on real-time rendering. Syndra uses **OpenGL** graphics API and is being developed for the Windows platform.

# Motivation
Syndra is my bachelor's thesis project, where I wanted to study how to build 3D game engines. The purpose of this project is not to make 3D games; rather, my primary motivation for making Syndra is to test and learn new algorithms and techniques used mainly in graphics and real-time rendering.

# Download
[Syndra-Engine v1.1.1-alpha](https://github.com/ErfanMo77/Syndra/releases/download/v1.1.1-alpha/Syndra-v1.1.1-alpha.rar)

# Showcase

[![](https://raw.githubusercontent.com/ErfanMo77/Syndra/master/Showcase/video_img_show.png)](https://www.youtube.com/watch?v=PlPZ7A7ZCdA)
[![](https://raw.githubusercontent.com/ErfanMo77/Syndra/develop/Showcase/Screenshot1_show.png)](https://raw.githubusercontent.com/ErfanMo77/Syndra/develop/Showcase/Screenshot1.png)

[![](https://raw.githubusercontent.com/ErfanMo77/Syndra/develop/Showcase/Screenshot3_show.png)](https://raw.githubusercontent.com/ErfanMo77/Syndra/develop/Showcase/Screenshot3.png)


# Features
* Engine
  * Editor (with docking support)
  * Entity Component System (ECS)
  * Event system
  * Console logging
  * Model and texture loading (40+ model file formats support using Assimp)
  * Scene saving and loading using YAML serialization and deserialization
  * Debug visualizer (GBuffer, HDRI map, ...)
  * Immediate mode GUI
  * Component editor (material, mesh, light, tag and camera)
  * Viewport gizmos
  * HDRI skymap loading
  
* Rendering
  * Deferred Rendering
  * PBR Rendering (Cook–Torrance BRDF)
  * Materials (with texture loading)
  * Dynamic shadows
  * Different light types (directional, point lights and spot lights)
  * Soft shadows using **PCSS** algorithm
  * Image Based Lighting (IBL)
  * Fast Approximate Anti-Aliasing (FXAA)
  * Normal mapping

# Future
* Engine
  * Asset manager and content Browser
  * Physics engine
  * CPU and GPU profiling
  * Scripting system


* Rendering
  * More debug visualizers (grid, wireframe, ...)
  * SSAO (Screen Space Ambient Occlusion)
  * SSR (Screen Space Reflection)
  * Procedural atmospheric sky
  * Point light shadows
  * Bloom
  * Compute shaders for IBL calculations
  
# Compiling
Syndra only supports windows for now.
Visual Studio 2019 is recommended.

Start by cloning the repository with `git clone --recursive https://github.com/ErfanMo77/Syndra-Engine`.
If the repository was cloned non-recursively previously, use `git submodule update --init` to clone the necessary submodules.

Syndra requires Vulkan SDK to compile shaders, so first, you have to run **scripts/setup.py** to install Vulkan SDK on your device.
Then, you can execute GenerateProjects.bat to generate a visual studio solution file and compile the engine.

# Third Party Libraries
- [GLFW](https://www.glfw.org) : Handling windows and mouse and keyboard events.
- [Glad](https://glad.dav1d.de) : OpenGL functions loader.
- [spdlog](https://github.com/gabime/spdlog) : Console debugger logging.
- [stb_image](https://github.com/nothings/stb) : Reading and loading textures.
- [ImGui](https://github.com/ocornut/imgui) : Immediate mode GUI used in editor UI.
- [ImGuizmo](https://github.com/CedricGuillemet/ImGuizmo) : Editor gizmos.
- [Entt](https://github.com/skypjack/entt) : Used in Entity Component System (ECS).
- [GLM](https://github.com/g-truc/glm) : Matrix and vector operations.
- [Assimp](https://github.com/assimp/assimp) : Loading 3D models with support for more than 40 file formats.
- [yaml-cpp](https://github.com/jbeder/yaml-cpp) : Scene serialization and deserialization.
- [Vulkan SDK](https://www.lunarg.com/vulkan-sdk) : Shader compilation and reflection.
- [Premake](https://premake.github.io) : Projects configuration and visual studio solution generator. 

# Dependencies
* Windows 10.
* [Microsoft Visual C++ Redistributable for Visual Studio 2019](https://aka.ms/vs/16/release/VC_redist.x64.exe).

# Authors
[ErfanMo77](https://github.com/ErfanMo77) - **Erfan Momeni** 

# Acknowledgments
[LearnOpenGL](https://learnopengl.com/) Great OpenGL tutorials!

[The Cherno](https://www.youtube.com/channel/UCQ-W1KE9EYfdxhL6S4twUNw) game engine series

Logo design : [AmirMohammad Abedini](https://gitlab.com/musashi1997)

# License
Licensed under the Apache License 2.0, see [LICENSE](https://github.com/ErfanMo77/Syndra/blob/master/LICENSE) for details.

