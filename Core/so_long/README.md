# So Long

**And thanks for all the fish!** - A 2D game built with MiniLibX where players navigate a map to collect items and reach the exit.

## Project Information

| Field | Description |
|-------|-------------|
| **Program Name** | `so_long` |
| **Files** | `Makefile`, `*.h`, `*.c`, `maps/`, `textures/` |
| **Makefile Targets** | `NAME`, `all`, `clean`, `fclean`, `re` |
| **Arguments** | A map file in `.ber` format |
| **External Functions** | MiniLibX, `open`, `close`, `read`, `write`, `malloc`, `free`, `perror`, `strerror`, `exit`, math library |
| **Libft Authorized** | Yes (includes custom ft_printf) |

## 🎮 Game Overview

A 2D top-down game where the player must:
- Collect all collectibles on the map
- Find the shortest route to the exit
- Navigate using WASD or arrow keys
- Avoid walls and boundaries

## 🗺️ Map Specifications

### Valid Map Characters
- `0` - Empty space
- `1` - Wall
- `C` - Collectible
- `E` - Exit
- `P` - Player starting position

### Map Validation Rules
- ✅ Must contain exactly **1 exit**, **1 starting position**, and **at least 1 collectible**
- ✅ Must be **rectangular** 
- ✅ Must be **surrounded by walls**
- ✅ Must have a **valid path** to all collectibles and exit
- ✅ File extension must be `.ber`

## 🏗️ Architecture & File Structure

```
so_long/
├── Makefile
├── ft_printf/           # Custom printf implementation
│   ├── ft_addptr.c
│   ├── ft_numbers.c
│   ├── ft_printf.c
│   └── ft_words.c
├── inc/
│   ├── ft_printf.h
│   └── so_long.h        # Main header with structs and prototypes
├── map/                 # Test maps (valid and error cases)
│   ├── v_map.ber        # Valid maps
│   ├── e_notrect.ber    # Error maps for testing
│   └── ...
├── src/
│   ├── so_long.c        # Main program and map loading
│   ├── map_check.c      # Map validation and dimension checks
│   ├── elem_check.c     # Element counting and validation
│   ├── flood_fill.c     # Path validation algorithm
│   ├── mlx_stuff.c      # MiniLibX initialization and rendering
│   ├── movements.c      # Player movement and collision
│   ├── handle_error.c   # Error handling and cleanup
│   ├── inits.c          # Structure initialization
│   └── ft_libft.c       # Utility functions
└── textures/            # Game assets (64x64 pixels)
    ├── player.xpm
    ├── wall.xpm
    ├── collectibles.xpm
    ├── exit.xpm
    └── floor.xpm
```

## 🎯 Core Features

### Mandatory Requirements
- ✅ **Window Management** - Smooth window operations, ESC and close button handling
- ✅ **Movement System** - WASD and arrow keys, collision detection with walls
- ✅ **Game Logic** - Collect all items before exiting, move counter in shell
- ✅ **Map Validation** - Comprehensive error checking for invalid maps
- ✅ **Graphics** - Texture rendering using MiniLibX images
- ✅ **Memory Management** - No leaks, proper cleanup on exit

### Map Validation System
```c
// Comprehensive error checking
void map_check(char **argv, t_map *map_s)
{
    if (!read_map(map_s, argv))
        ft_error("", map_s);
    map_dimension(map_s);
    if (!rect_check(map_s))
        ft_error("Error: Map is not a rectangle.\n", map_s);
    if (!wall_check(map_s))
        ft_error("Error: Map is not surrounded by walls.\n", map_s);
    if (!valid_elem(map_s))
        ft_error("Error: Invalid elements in the map.\n", map_s);
    count_elems(map_s);
    check_elem(map_s);
    startfill(map_s);  // Flood fill path validation
}
```

## 🛠️ Build & Usage

### Compilation
```bash
make
```

### Running the Game
```bash
./so_long maps/v_map.ber
```

### Testing with Different Maps
```bash
# Valid maps
./so_long maps/v_smallmap.ber
./so_long maps/v_bigmap.ber

# Error maps (should display appropriate errors)
./so_long maps/e_notrect.ber      # Not rectangular
./so_long maps/e_cnotreach.ber    # Collectibles not reachable
./so_long maps/e_invalidc.ber     # Invalid characters
```

## 🎮 Game Controls

| Key | Action |
|-----|--------|
| `W` / `↑` | Move Up |
| `A` / `←` | Move Left |
| `S` / `↓` | Move Down |
| `D` / `→` | Move Right |
| `ESC` | Quit Game |

## 🔧 Technical Implementation

### Data Structures
```c
typedef struct s_map {
    char    **map;       // Original map
    char    **map_cp;    // Copy for flood fill
    int     map_w;       // Map width
    int     map_h;       // Map height
    int     player_x;    // Player X position
    int     player_y;    // Player Y position
    int     player;      // Player count
    int     exit;        // Exit count
    int     collect;     // Collectible count
} t_map;

typedef struct s_game {
    void    *mlx;        // MiniLibX instance
    void    *win;        // Window instance
    void    *player;     // Player texture
    void    *wall;       // Wall texture
    void    *exit;       // Exit texture
    void    *floor;      // Floor texture
    void    *collectible;// Collectible texture
    int     moves;       // Move counter
    t_map   *map;        // Map data
} t_game;
```

### Key Algorithms

#### 1. Flood Fill Path Validation
```c
void floodfill(t_map *map_s, int y, int x, t_temp *temp)
{
    // Recursively explores all reachable positions
    // Counts accessible collectibles and exits
}
```

#### 2. Movement System
```c
void movement(t_game *game, int new_y, int new_x, int key)
{
    // Validates movement
    // Updates collectible count
    // Checks win condition
    // Renders new position
}
```

## 🧪 Testing & Validation

### Map Testing Suite
The project includes comprehensive test maps:
- **Valid maps**: Various sizes and layouts
- **Error maps**: Tests for specific validation failures
- **Edge cases**: Maximum size, minimal requirements

### Manual Testing Commands
```bash
# Test map validation
./so_long maps/e_notrect.ber        # Should show rectangle error
./so_long maps/e_cnotreach.ber      # Should show path error
./so_long maps/e_invalidc.ber       # Should show invalid char error

# Test game functionality
./so_long maps/v_map.ber            # Should run game normally
```

## 🚀 Features Highlight

### Robust Error Handling
- **File errors**: Invalid format, missing files, permission issues
- **Map errors**: Invalid characters, missing requirements, path issues
- **Memory errors**: Allocation failures, proper cleanup
- **Graphics errors**: Texture loading failures

### Efficient Rendering
- **Texture caching**: Loads images once, reuses efficiently
- **Partial updates**: Only updates changed positions
- **Smooth window management**: Proper event handling

### Comprehensive Validation
- **Pre-game**: Full map validation before starting
- **Runtime**: Continuous collision and win condition checking
- **Post-game**: Clean exit with memory freeing

## 🎯 Evaluation Guide

### During Defense
1. **Demonstrate map validation** - Show error cases working
2. **Play the game** - Show collection and win condition
3. **Explain algorithms** - Flood fill, movement system
4. **Discuss memory management** - No leaks, proper cleanup

### Key Technical Points
- **Flood fill algorithm** for path validation
- **MiniLibX integration** for graphics
- **Linked movement system** with collision detection
- **Comprehensive error handling** throughout

## ⚠️ Important Notes

- **Map size limit**: 560 bytes maximum (can be adjusted in BUFFER_SIZE)
- **Texture requirements**: 64x64 pixel XPM files
- **Memory management**: All allocated memory properly freed
- **Norm compliance**: Follows 42 coding standards

---

**Pro Tip**: The flood fill algorithm is crucial for map validation. Make sure it correctly identifies unreachable collectibles and exits before the game starts!
