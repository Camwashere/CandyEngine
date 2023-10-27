# CandyEngine
A Vulkan based cross-platform rendering engine for 2D and 3D applications. 

## Features


## Library Features

* Fully featured Math Library built from scratch
  
  * Built from the ground up to be highly optimized using SIMD intrinsics, expression templates and more.
  * An abundance of convience functions, additional tools and clear code to reduce boilerplate and the need for manual additions
  * Extremely flexible, allowing seemless integration with custom types
  * Supports linear algebra, geometry, statistics, procedural noise, psuedo random number work, curves, ranges and more
  * Tons of additional niche functionality such as quicker approximations at the cost of accuracy, directions, etc.

* Vulkan based graphics library
  * Specifically designed and focused to take full advantage of vulkan
  * Robust shader functionality including runtime shader compilation/hot reloading/smart reloading, shader caching, shader pre/post processing and reflection, automatic pipeline layout construction and a high degree of control
  * Flexible levels of control. Choose when and where you want the complexities of vulkan abstracted away, and when access to the lower level internals is required. CandyEngine will never tell you 'no'.
  * Shader profiles/configurations, custom render pass and render target configuration, vulkan features/extensions management can all be easily tuned/extended/customized with easy to use configuration files and an intuitive api that lets you dig into even the most advanced vulkan features without needing to recompile
  * RenderPass scheduler and render target api allows for extremely complex alterations with very minimal (if any) changes to code, perfect for experimentation.
  * Powerful highly optimized rendering api for batch rendering static meshes, 2D shapes, sprites, and more with full support for dynamic vertex data and custom types
  * Loads of easily overriden convience features from abstracting descriptor sets with ids, automatic gpu memory management, easy to use vertex/index buffers, render command recording, object deletion, debugging, multiple frames in flight handling, pipeline management, and more.
  * 

