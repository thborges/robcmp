# robcmp

Robcmp is a compiler for a programming language designed for robotics, developed at the Universidade Federal de Jataí in Brazil. The language goal is to isolate microcontroller specificities, providing a hardware abstraction layer within the compiler itself, rather than relying on frameworks or libraries. This approach allows developers to write code once, without the need for conditional compilation directives (IFDEFs) or other preprocessing techniques. By leveraging the compiler's semantic analysis, common errors encountered when developing firmware in a non-domain specific language, such as C/C++, can be prevented.

Currently, Robcmp is integrated with the AVR and ARM backends of LLVM, and is able to upload code to avr328p and stm32f1 based boards. The language is still in the experimental stage and lacks support for various features, including string processing, dynamic arrays, debugging, and others. We warmly welcome any contributions in these areas, whether in the form of pull requests, financial aid for our students, or any other form of assistance. If you are interested in the project, please feel free to reach out to us!

You can install Robcmp in Visual Code and Platformio following the instructions below.

The project initially began in 2015 as a framework for building LLVM compiler frontends, utilizing the compiler backend available at https://github.com/avr-llvm/llvm. Its primary objective at the time was to provide basic support for academics enrolled in the Compiler course, enabling them to construct their own language and run it on Arduino boards. Over time, the AVR backend was integrated into LLVM as experimental and eventually became a fully supported backend.

# Setup

To test robcmp in your computer, run the following commands in a console after installing Visual Code and the Platformio extension. There are support for syntax highlighting, building, uploading and debugging for some AVR and STM32 based boards. You can even test your AVR project in an integrated simulator.

```
[Linux] wget https://bit.ly/robcmp-linux-00-2 -O robcmp-linux-0.2.tar.gz
[Osx]   wget https://bit.ly/robcmp-darwin-0-2 -O robcmp-darwin-0.2.tar.gz
mkdir robcmp && cd robcmp && tar xfz robcmp-*.tar.gz
./install
code examples/avr328p-blink [for avr]
code examples/stm32f1-blink [for stm32]
```

This commands will install the robcmp platform in ~/.platformio/platforms and the syntax highlight extension in ~/.vscode/extensions. The last command will open the basic-blink sample on vscode. Hit build and then upload it to a supported board.


# Robcmp Development Setup

To build robcmp from source, you will need to follow these steps. Please note that currently, only Linux and OSX are supported:

- Install LLVM version 18 or newer:
  - On Linux, you can follow the instructions provided at https://apt.llvm.org to install llvm. Install the following packages: apt install llvm-18 cmake flex bison zlib1g-dev libzstd-dev git lld-18 gdb-avr binutils-avr clang
  - On macOS, you can use Homebrew by running the command brew install llvm17.
- Flex (version 2.6.4 or newer) and Bison (version 3.8.2 or newer) are required.
- Clone the robcmp repository: `git clone https://github.com/thborges/robcmp.git && cd robcmp`
- Switch to the most recent or desired branch: `git checkout llvm18`
- Create a builder folder: `mkdir build && cd build`
- Configure the source code with cmake: `cmake -DCMAKE_BUILD_TYPE="Debug" ..`
- Execute the make command: `$ make`

To debug .rob programs using visual code, you should also build the source code at https://github.com/thborges/simavr.git, branch pr-test
- apt install avr-gcc avr-libc libglut-dev libelf-dev
- git clone https://github.com/thborges/simavr.git
- cd simavr && git checkout pr-test
- make
- cp examples/robcmp-simavr-debug/**/robcmp-simavr-debug ~/robcmp/build

To integrate robcmp with Visual Code:
- cd ~/robcmp (return to robcmp folder)
- ./platformio/integrate2vc
