# CppAssetPacker
Minimalistic utility tool for packing up asset files into an includable class.

## Getting started
### Usage
This software is still in early development, for now you'll need to compile it yourself. Luckily, it's a simple process.

### Building and installation
1. If available, download the latest release, if not <br> `git clone https://github.com/Txar/CppAssetPacker.git` && `cd CppAssetPacker-main`
#### Linux
2. `make` in root directory of the project to build
#### Windows
2. `mingw32-make` in root directory of the project to build

3. The executable should be created in the `build` directory. From there, you can copy it into the desired place in your project.

### Configuration
Configuration
- `files` - list of files that get packed into the output class, each one in a new line (can be a filename or a relative path from the `assetsDirectory`)
- `assetsDirectory` - path to assets directory
- `outputPath` - path to the outputed .cpp file

## License
This project is licensed under the MIT License - see `LICENSE` file for details.

## WIP
- A more sophisticated installer
- Better config files
- Better code readibility
