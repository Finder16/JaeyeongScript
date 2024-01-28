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
The work presented in this project draws inspiration from Vlang. The majority of the code contained within the files array.c, string.c, and map.c, io.c, error.c etc. has been directly sourced from the Vlang project's source code repository. It is important to note that the code obtained from the Vlang project is governed by the MIT License.

While we have diligently marked most of the functions and structures sourced from Vlang with the Doxygen @copyright tag, there is a possibility that some instances may have been inadvertently overlooked. Nonetheless, it remains unequivocally clear that any code imported from the Vlang project is subject to the terms of the MIT License.

Furthermore, it is imperative to understand that all code unique to the JaeyeongScript project is licensed under the terms of the GNU Affero General Public License version 3 (AGPL-3). For a comprehensive understanding of the rights and obligations associated with the use and distribution of the JaeyeongScript codebase, we strongly encourage you to refer to the LICENSE file provided within this repository.

## References

- none

## Changelog

See [CHANGELOG.md](CHANGELOG.md) for release notes and version history.

## Issue Reporting and Feature Requests

To report bugs or request new features, please open an issue on the [issue tracker](https://github.com/Finder16/JaeyeongScript/issues).