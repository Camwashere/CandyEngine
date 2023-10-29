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

* GumSystem UI Library
  * An expansive, customizable, graphics api based ui library that allows for limitless possibilities
  * Doesn't rely on OS calls, so you can render any graphic or effect you can possibly imagine while mainting a consistent look across platforms.
  * Supports both retained mode and immediate mode. Use immediate mode for quick, single state ui tasks like debugging and prototyping and retained mode for more fleshed out, finalized work. Or ignore one entirely, they can be used together however you wish!
  * Create your own custom events, handlers, filters, listeners, etc. Event capturing and bubbling can be completely controlled by the user
  * Effortless integration with Candy Engine. Since the editor/ui of Candy Engine is built using GumSystem, you can easily change, extend and customize everything in both your application's ui, and the CandyEngine itself to create the perfect enviorment for you.
  * Highly customizable. Feel free to abandon the premade/helper functionality entirely and submit your own completely custom vertex data, collision handling, events, and more for 100% control whenever you need it.
  * 3D functionality for gizmos, debug tools, animations and unique UI designs

* Utility everywhere
  * Supports the latest features of c++23
  * Collections library including generic data buffers, multidimensional arrays, dualmaps, etc
  * Powerful debuging and logging tools, easy to use timers/stopwatches, versioning, etc
  * Fast, easy to use serialization and file management
  * Way too many other utilities to name

