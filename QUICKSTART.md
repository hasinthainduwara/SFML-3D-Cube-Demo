# Quick Start Guide

Get the 3D Rotating Cube project running in under 5 minutes!

## Prerequisites Check

✅ **Required**: CMake 3.8+  
✅ **Required**: Visual Studio 2022 or Ninja  
✅ **Included**: SFML 3.x libraries  

## Fastest Way to Build

### Option 1: Visual Studio (Recommended for Windows)

```bash
# 1. Configure with Visual Studio generator
cmake --preset windows

# 2. Build the project
cmake --build --preset windows-debug

# 3. Run the application
./out/build/windows/CMakeProject1.exe
```

### Option 2: Ninja (Fastest builds)

```bash
# 1. Configure with Ninja
cmake --preset x64-debug

# 2. Build the project
cmake --build out/build/x64-debug

# 3. Run the application
./out/build/x64-debug/CMakeProject1/CMakeProject1.exe
```

## What You'll See

After building and running, you should see:
- A black window (800x600 pixels)
- A white wireframe cube rotating smoothly
- The cube rotates around both X and Y axes

## Troubleshooting Quick Fixes

| Problem | Solution |
|---------|----------|
| "CMake not found" | Install CMake from [cmake.org](https://cmake.org/download/) |
| "SFML DLL missing" | The DLLs should copy automatically. Check `SFML/bin/` exists |
| "C++17 not supported" | Update to Visual Studio 2019+ or GCC 7+ |
| Build fails | Delete `build/` and `out/` folders, try again |

## Next Steps

- Modify `rotationSpeed` in `CMakeProject1.cpp` to change rotation speed
- Add new 3D objects by extending the vertex arrays
- Experiment with different projection parameters

## Need Help?

- Check the full [README.md](README.md) for detailed documentation
- Look at the build output for specific error messages
- Ensure all prerequisites are installed correctly
