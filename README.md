# RenderingEngine in C with OpenGL

### Objectives:
   - Simple OpenGL-Wrapper functions
      - Located in the engine-core
   - Example applications that use the wrapper functions       
      - Sandbox: Box-Picker (2D)
      - WrathGL: Terrain-Creator (3D)  
      - PowderTrain: Falling-Sand-Simulation (2D)
   - Written entirely in C
   - Bulletpoints marked with (X) are already implemented

### General functionalities
   - Basic OpenGL-Wrapping (VAO, VBO, IBO, Shader, Texture, Errorhandling)  (X)  
   - Windowcreation for 2D and 3D (X)
   - GUI-Library (X)
   - 2D Sprite-Renderer (X)
      - Instanced rendering (X)
   - 3D Model-Renderer (X)
      - Dynamic mesh creation (X)
      - OBJ-Loading
   - Text rendering (X)
      - Batch rendering system (X)   
   - Camerasystem (X)
   - Audiomanager for sounds and backgroundmusic

### Example applications   
   #### Sandbox App (2D)
      - GUI (X)
      - Box picking and placing (X)
         - Instanced rendering (X)
      - 2D Physics (X)
      - Liquids   
      - AI
   #### WrathGL App (3D)            
      - 3D Mesh creation (planes, tiles) (X)
      - Terrain creation (X)
         - Vertices (X)
            - Procedural generated with noise-function (X)
            - Dynamic and changeable (X)
            - Backgroundthread calculates new terrain (X)
            - Renderthread renders new terrain (X)
         - Colors (X)
            - Dynamic, based on height (X)
         - Lighting (X)
      - Water (X)
   #### PowderTrain App (2D)
      - GUI (X)   
      - Pixel-Renderer (X)
      - Sand-Simulation (X)
         - Different materials/substances -> different reactions (X)

### Credits
   - [log.c](https://github.com/rxi/log.c)
   - [stb_image](https://github.com/nothings/stb/blob/master/stb_image.h)
   - [cglm](https://github.com/recp/cglm)
   - [glad](https://github.com/Dav1dde/glad)
   - [FreeType](https://freetype.org/index.html)
   - [Chipmunk2D](https://github.com/slembcke/Chipmunk2D)
   - [GLFW](https://github.com/glfw/glfw) 

### Using & Compiling
   - Currently only for linux, using CMake as a buildsystem
      - Clone the repository
      - Install the dependencies (cglm, FreeType, Chipmunk2D, GLFW) 
         - Take a look at the credits to find the repositories
      - mkdir build
      - cd build/
      - cmake ..
      - make
      - Run the demo applications  

### License
   - This code is provided under a BSD-style license. See the file LICENSE for details

### Structure of the example application "Sandbox"
   - To show the collaboration of the different modules
   - Just for visualization purposes, not UML conform    

   ![Application structure](res/screenshots/Structure_003.png)

### Look of the Sandbox App
   ![Sandbox](res/screenshots/Screenshot_SB_007.png)

### Look of the WrathGL App
   ![WrathGL_far](res/screenshots/Screenshot_WR_011_far.png)
   ![WrathGL_close](res/screenshots/Screenshot_WR_011_close.png)

### Look of the PowderTrain App
   ![PowderTrain](res/screenshots/Screenshot_PT_003.png)   