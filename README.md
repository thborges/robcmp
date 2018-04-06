# robcmp
LLVM frontend for Arduino

Project Developed at Universidade Federal de Goiás - Regional Jataí
http://computacao.jatai.ufg.br

This code is a framework to build LLVM compiler frontend's. It uses the compiler backend in https://github.com/avr-llvm/llvm.

The purpose of the framework is to provide basic support for academics, taking the Compiler course, to build their own language an run it on Arduino boards.

The files [rob.l](/rob.l) and [rob.y](/rob.l) implements a general purpose example language, using the framework in [node.h](/node.h) file. Examples of the language are provided in [test](/test) folder.

Academics build their own specific language using the framework provided, to run on an arduino board connected to a robot arm (1). The project file is provided in the [proj](/proj) folder, file [project.pdf](/proj/project.pdf), writen in Brazilian Portuguese.

1:
![arm robot](/proj/robotarm.jpg)
