# Cub3D - My First RayCaster with miniLibX

A 3D ray-casting engine inspired by Wolfenstein 3D, built using the miniLibX graphics library.

## 📋 Project Overview

This project creates a realistic 3D graphical representation of a maze from a first-person perspective using ray-casting principles. The program renders textured walls, handles player movement and camera rotation, and includes several bonus features.

## 🎮 Features

### Mandatory Features
- **3D Ray-casting engine** with first-person perspective
- **Textured walls** with different textures for each cardinal direction (N, S, E, W)
- **Customizable floor and ceiling colors**
- **Smooth window management** and event handling
- **Player movement** using W, A, S, D keys
- **Camera rotation** using left/right arrow keys
- **Map parsing** from `.cub` configuration files
- **Proper error handling** and clean resource management

### Bonus Features (Implemented)
- **✅ Wall collisions** - Players cannot walk through walls
- **✅ Minimap system** - Real-time minimap display
- **✅ Doors** - Interactive doors that can open and close
- **✅ Animated sprites** - Moving coin animations
- **❌ Mouse rotation** - *Not implemented (reason for 120/125 score)*

## 🏗️ Project Structure

```
cub3D/
├── Makefile                    # Build system
├── bonus/                      # Bonus feature implementations
│   ├── direction_updates_bonus.c
│   ├── draw_minimap_bonus.c    # Minimap rendering
│   ├── draw_render_bonus.c
│   ├── free_n_err1_bonus.c
│   ├── free_n_err_bonus.c
│   ├── ft_hooks_bonus.c        # Extended input handling
│   ├── helper_bonus.c
│   ├── hook_door_bonus.c       # Door interaction system
│   ├── inits2_bonus.c
│   ├── inits_bonus.c
│   ├── locate_door_bonus.c     # Door detection
│   ├── location_updates_bonus.c
│   ├── main_bonus.c           # Bonus main program
│   ├── map_check2_bonus.c
│   ├── map_check_bonus.c
│   ├── map_helper2_bonus.c
│   ├── map_helper3_bonus.c
│   ├── map_helper_bonus.c
│   ├── parse_textures2_bonus.c
│   ├── parse_textures3_bonus.c
│   ├── parse_textures4_bonus.c
│   ├── parse_textures5_bonus.c
│   ├── parse_textures_bonus.c
│   ├── render_bonus.c
│   ├── render_helper_2_bonus.c
│   ├── render_helper_3_bonus.c
│   └── render_helper_bonus.c
├── inc/
│   └── cub3d.h                # Main header file
├── inc_bonus/
│   └── cub3d.h                # Bonus header file
├── libft/                     # Custom C library
│   ├── Makefile
│   ├── ft_*.c                 # Standard library functions
│   └── libft.h
├── map/                       # Mandatory maps
│   ├── map1.cub
│   ├── map2.cub
│   ├── map3.cub
│   ├── map4.cub
│   ├── map5.cub
│   └── max.cub
├── map_bo/                    # Bonus maps with extra features
│   ├── map1.cub
│   ├── map2.cub
│   ├── map3.cub
│   ├── map4.cub
│   └── map5.cub
├── src/                       # Mandatory source files
│   ├── direction_updates.c    # Player rotation
│   ├── draw_render.c          # Rendering system
│   ├── free_n_err.c           # Error handling
│   ├── ft_hooks.c             # Input handling
│   ├── helper.c               # Utility functions
│   ├── inits.c                # Initialization
│   ├── inits2.c
│   ├── location_updates.c     # Player movement
│   ├── main.c                 # Main program
│   ├── map_check.c            # Map validation
│   ├── map_check2.c
│   ├── map_helper.c           # Map parsing utilities
│   ├── map_helper2.c
│   ├── map_helper3.c
│   ├── parse_textures.c       # Texture loading
│   ├── parse_textures2.c
│   ├── parse_textures3.c
│   ├── parse_textures4.c
│   ├── render.c               # Main rendering loop
│   └── render_helper.c
└── textures/                  # Game textures
    ├── coin.xpm               # Animated coin sprites
    ├── coin2.xpm
    ├── coin3.xpm
    ├── coin4.xpm
    ├── coin_00.xpm
    ├── coin_01.xpm
    ├── coin_02.xpm
    ├── coin_03.xpm
    ├── coin_04.xpm
    ├── coin_05.xpm
    ├── coin_06.xpm
    ├── coin_07.xpm
    ├── door.xpm               # Door textures
    ├── door1.xpm
    ├── wall_east.xpm          # Wall textures
    ├── wall_north.xpm
    ├── wall_south.xpm
    └── wall_west.xpm
```

## 🚀 Installation & Compilation

### Prerequisites
- **miniLibX** graphics library (Linux version)
- **GCC compiler**
- **Make** build system
- **X11** window system

### Compilation Commands

```bash
# Compile mandatory version
make

# Compile bonus version (includes all bonus features)
make bonus

# Clean object files
make clean

# Full clean (objects and binaries)
make fclean

# Recompile from scratch
make re
```

## 🎯 Usage

### Running the Game

```bash
# Run mandatory version
./cub3D map/map1.cub

# Run bonus version
./cub3D_bonus map_bo/map1.cub
```

### Available Maps
- **Mandatory maps**: `map/map1.cub` to `map/map5.cub`, `map/max.cub`
- **Bonus maps**: `map_bo/map1.cub` to `map_bo/map5.cub` (include doors and collectibles)

## 🎮 Controls

### Movement
- **W** - Move forward
- **S** - Move backward  
- **A** - Strafe left
- **D** - Strafe right
- **← →** - Rotate camera left/right

### Interaction (Bonus Features)
- **SPACE** - Open/close doors

### System
- **ESC** - Exit game
- **Window X button** - Close window and exit

## 📁 Map File Format (.cub)

### Configuration Elements
```
NO ./textures/wall_north.xpm    # North texture
SO ./textures/wall_south.xpm    # South texture
WE ./textures/wall_west.xpm     # West texture
EA ./textures/wall_east.xpm     # East texture
F 220,100,0                     # Floor color (RGB)
C 225,30,0                      # Ceiling color (RGB)
```

### Map Layout
- **1** - Wall
- **0** - Empty space (walkable)
- **N/S/E/W** - Player start position and direction
- **D** - Door (bonus feature)
- **C** - Collectible coin (bonus feature)

### Example Map
```
111111
1N0001
1010D1
1C0011
111111
```

## 🔧 Technical Implementation

### Core Systems

#### 1. Ray-casting Engine
- **DDA Algorithm** for efficient wall detection
- **Texture mapping** with correct perspective
- **Field of view** calculation using camera plane

#### 2. Rendering Pipeline
- **Double buffering** with image creation
- **Efficient pixel manipulation** using `mlx` functions
- **Color blending** for floor and ceiling

#### 3. Player Physics
- **Collision detection** using map grid checking
- **Smooth movement** with frame-independent updates
- **Camera rotation** using rotation matrices

#### 4. Bonus Systems
- **Minimap rendering** with player and environment
- **Door state management** with interactive toggling
- **Sprite animation system** for collectibles
- **Extended map parsing** for bonus elements

### Key Data Structures

```c
typedef struct s_game {
    void        *mlx;           // MLX instance
    void        *win;           // Window instance
    t_player    *p;             // Player data
    t_map       *map;           // Map data
    // ... other members
} t_game;

typedef struct s_player {
    double  x, y;               // Position
    double  dir_x, dir_y;       // Direction vector
    double  pln_x, pln_y;       // Camera plane
} t_player;

typedef struct s_ray {
    double  ray_dir_x, ray_dir_y; // Ray direction
    int     map_x, map_y;       // Current map cell
    double  wall_dist;          // Distance to wall
    int     side;               // Wall orientation
    // ... other members
} t_ray;
```

## 🧪 Evaluation Checks

### Basic Functionality Tests

```bash
# 1. Program Compilation
make && make bonus
# Should compile without errors or warnings

# 2. Argument Validation
./cub3D                              # Should show usage error
./cub3D invalid_file.txt            # Should show format error
./cub3D map/map1.cub               # Should run successfully

# 3. Map Validation
./cub3D map/invalid_map.cub        # Should detect map errors
```

### Runtime Checks

#### 4. Movement and Collision
```bash
# Test wall collisions by trying to walk into walls
# Test door interactions with SPACE key
# Verify player cannot exit map boundaries
```

#### 5. Rendering Verification
- Walls should display correct textures based on orientation
- Floor and ceiling should show specified colors
- No visual artifacts or texture bleeding
- Smooth 60 FPS performance

#### 6. Bonus Feature Tests
- **Minimap** should show in corner with player position
- **Doors** should open/close with SPACE when facing them
- **Coins** should animate
- **All textures** should load without errors

### Memory Management
```bash
# Check for memory leaks
valgrind --leak-check=full ./cub3D map/map1.cub

# Program should exit cleanly with no memory leaks
```

### Error Handling Tests
```bash
# Test various error conditions:
# - Missing texture files
# - Invalid color values
# - Non-enclosed maps
# - Multiple player positions
# - Invalid map characters
```

## 🐛 Troubleshooting

### Common Issues

1. **MLX Initialization Failed**
   - Ensure miniLibX is properly installed
   - Check X11 dependencies

2. **Texture Loading Errors**
   - Verify all texture paths in .cub files
   - Ensure texture files exist and are valid .xpm format

3. **Segmentation Faults**
   - Run with valgrind to identify memory issues
   - Check map file validity

4. **Performance Issues**
   - Ensure efficient ray-casting algorithm
   - Verify texture sizes are power of two

## 👥 Team Contributions

This project was developed in collaboration with **[nann5an1](https://github.com/nann5an1)**.

### Core Ray-casting Engine & Rendering System
**Implemented by [ysetiawa](https://github.com/ysetiawa)**
- `src/direction_updates.c` `src/draw_render.c` `src/render.c` `src/render_helper.c`
- Ray-casting algorithm implementation using DDA
- Wall rendering with perspective-correct texture mapping
- Player movement physics and collision detection
- Camera rotation system using rotation matrices
- Main rendering loop and frame management

### Bonus Features & Extended Systems
**Implemented by [nann5an1](https://github.com/nann5an1)**
- `bonus/draw_minimap_bonus.c` `bonus/hook_door_bonus.c` `bonus/locate_door_bonus.c`
- Real-time minimap rendering with player position
- Interactive door system with open/close mechanics
- Animated sprite system for collectible coins
- Extended input handling for bonus interactions
- Enhanced map parsing for bonus elements

### Project Infrastructure & Core Systems
**Collaborative Implementation**
- Map parsing and validation system
- Error handling and memory management
- Texture loading and resource management
- MLX window initialization and event handling
- Code optimization and performance tuning

## 📚 Resources

- [miniLibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx)
- [Ray-casting Tutorial](https://lodev.org/cgtutor/raycasting.html)
- [Wolfenstein 3D Reference](http://users.atw.hu/wolf3d/)

---

**Note**: This project demonstrates advanced C programming, mathematical implementation of 3D graphics, and efficient resource management in a constrained environment.
