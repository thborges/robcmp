# robcmp
LLVM frontend for Arduino

Project Developed at Universidade Federal de Goiás - Regional Jataí
http://computacao.jatai.ufg.br

This code is a framework to build LLVM compiler frontend's. It uses the compiler backend in https://github.com/avr-llvm/llvm.

The purpose of the framework is to provide basic support for academics, taking the Compiler course, to build their own language an run it on Arduino boards.

The files rob.l and rob.y implements a general purpose example language, using the framework in node.h file. Examples of the language are provided in the folder test.

Academics has built their own specific language, to run an arduino connect to a robot arm. The project file is provided in the folder proj, file project.pdf, described in Brazilian Portuguese.
