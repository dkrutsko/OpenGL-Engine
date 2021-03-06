# OpenGL Engine

<p align="justify">This application features a sample testing environment running on a custom-built 3D game engine. The engine uses OpenGL 3 and offers a variety of different features, see below. Most of the technology was made for prototyping however the overall engine provides a nice foundation for future projects. Portions of the engine architecture were inspired by the Microsoft XNA Framework.</p>

**Caution:** This project has not been extensively tested.

### Movement
* W - Move Forward
* S - Move Backward
* A - Turn Left
* D - Turn Right
* A + RMB - Strafe Left
* D + RMB - Strafe Right
* LMB - Look Around the Screen
* SPACE - Move Up
* CTRL - Move Down
* Q - Reset Camera Position
* HOLD SHIFT - Faster Movement

### Controls
* Keypad 1 - Switch to Camera 1
* Keypad 2 - Switch to Camera 2
* Keypad 3 - Switch to Shadow Camera
* Keypad 5 - Disable Rain Effects

### Compiling
* Extract zip file inside the libraries directory
* **Warning:** Only works with Visual Studio 2010

### Features
* OpenGL 3 based rendering pipeline
* All statically build (/MT and /MTd)
  * No pesky DLL's
  * No need to download any additional libraries
* VBO, IBO and VAO Mesh rendering
* Fully featured custom math library
* Phong lighting with up to 8 lights
* Bump mapping using a normal map
* Shadows using Variance Shadow Mapping
* 2D sprite rendering support
* Shader based particle systems
* Extended FPS camera(s)
* Strict error detection in debug mode
* Highly optimized release build
* Handy debug console for outputting messages
* Advanced content management system
  * Drag and drop over exe to compile assets
  * Manages all assets within the game
  * Compile assets to optimize loading
  * Advanced lossless compression
  * All assets can be created dynamically in code
  * Fully extensible to support new formats

### Author
* Email: <dave@krutsko.net>
* Home: [dave.krutsko.net](http://dave.krutsko.net)
* GitHub: [github.com/dkrutsko](https://github.com/dkrutsko)