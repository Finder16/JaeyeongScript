# JaeyeongScript

## Overview

JaeyeongScript is a simple compiler project written in C language. JaeyeongScript is compiled into an executable binary by the C language compiler that is included in the distribution by default.

## Features

- Supports the most basic language constructs such as variables, functions, and control flow statements. (Coming soon)
- Compiles to a variety of languages such as C, JS, Rust, Zig, etc. (Coming soon)
- By default, JaeyeongScript is compiled into C and then compiled with C language compilers such as tcc and gcc.
- 
## Getting Started

To build and run JaeyeongScript, follow these steps:

1. First, download mingw (for developers, we used `llvm-mingw-20231128-ucrt-x86_64`). Also, move the files inside the downloaded mingw folder to `C:\mingw64` (all directories and files such as `aarch64-w64-mingw32`, `armv7-w64-mingw32`, `bin`, `i686-w64-mingw32`, `include`, `lib`, `python`, `share`, `x86_64-w64-mingw32`, etc).

2. Clone the repository:

```
git clone https://github.com/Finder16/JaeyeongScript.git
cd JaeyeongScript
```


For more options and usage examples, refer to the documentation in the `docs` directory.

## Contributing

Contributions are welcome! If you find a bug or want to suggest a new feature, please open an issue or submit a pull request.

## License
Certain portions of the source code in this project have been adapted from Vlang. Specifically, the code segments found in array.c, string.c, map.c, io.c etc. have been derived from the Vlang project's source code repository. It should be noted that these particular sections of code obtained from Vlang are governed by the MIT License.

Although extensive efforts have been made to appropriately attribute functions and structures sourced from Vlang by employing the Doxygen @copyright tag, there remains a possibility that some instances may have been inadvertently overlooked. Nonetheless, it is indisputably clear that any code segments imported from the Vlang project are subject to the terms outlined in the MIT License.

Additionally, it is important to clarify that all other components of the JaeyeongScript project, not derived from Vlang, are licensed under the GNU Affero General Public License version 3 (AGPL-3). For comprehensive insights into the rights and obligations associated with the usage and distribution of the JaeyeongScript codebase, we strongly recommend consulting the [LICENSE](LICENSE) file included within this repository.

## References

- none

## Changelog

See [CHANGELOG.md](CHANGELOG.md) for release notes and version history.

## Issue Reporting and Feature Requests

To report bugs or request new features, please open an issue on the [issue tracker](https://github.com/Finder16/JaeyeongScript/issues).