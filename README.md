# RenderingEngine in C with OpenGL

### Objectives:
   - Simple OpenGL-Wrapper functions
      - Located in the engine-core
   - Example applications to show how use the wrapper functions       
      - Sandbox: Box-Picker (2D)
      - WrathGL: Terrain-Creator (3D)  
   - Written entirely in C
      - It really should be 100% C-Code -> sometimes github detects C++ files for whatever reason

### Planned functionalities
   - Basic OpenGL-Wrapping (VAO, VBO, IBO, Shader, Texture, Errorhandling)  (X)  
   - Windowcreation for 2D and 3D (X)
   - 2D Sprite-Renderer (X)
   - Text rendering (X)
      - Batch rendering system (X)
   - OBJ-Loading
   - Camerasystem (X)
   - Audiomanager for sounds and backgroundmusic        

### Example applications   
   #### Sandbox App
      - GUI (X)
      - Box picking and placing (X)
         - Instanced rendering (X)
      - 2D Physics (X)
      - Liquids   
      - AI
   #### WrathGL App            
      - 3D Mesh creation (planes, tiles) (X)
      - Terrain creation
         - Vertices
         - Colors
         - Lighting
      - Water
      - Models

### Credits
   - [SDL2](https://www.libsdl.org/index.php)
   - [log.c](https://github.com/rxi/log.c)
   - [stb_image](https://github.com/nothings/stb/blob/master/stb_image.h)
   - [cglm](https://github.com/recp/cglm)
   - [glad](https://github.com/Dav1dde/glad)
   - [FreeType](https://freetype.org/index.html)
   - [Chipmunk2D](https://github.com/slembcke/Chipmunk2D)
   - [GLFW](https://github.com/glfw/glfw) 

### Using & Compiling
   - Currently only for linux
   - There will be a guide on how to build the engine or a script that does everything for you, when it's a bit more matured
   - For now:   
      - Clone the repository
      - Install the dependencies (SDL2, cglm, FreeType, Chipmunk2D, GLFW) 
         - Take a look at the credits to find the repositories
      - Execute one of the shell scripts or the Makefile itself to build the demo applications
      - Run the demo applications  

### License
   - This code is provided under a BSD-style license. See the file LICENSE for details

### Structure of the 2D example application "Sandbox"
   - To show the collaboration of the different modules
   - Just for visualization purposes, not UML conform    

   ![Application structure](Structure_001.png)

### Look of the Sandbox app
   ![Sandboxlevel](Screenshot_SB_006.png)

### Look of the WrathGL app
   ![Sandboxlevel](Screenshot_WR_000.png)