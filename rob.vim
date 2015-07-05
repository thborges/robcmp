" Vim syntax file
" Language: Robcmp Small LLVM Arduino Frontend
" Maintainer: Thiago Borges de Oliveira
" Latest Revision: 10 June 2015

if exists("b:current_syntax")
    finish
endif

syn keyword loopKeywords while
syn keyword conditionalKeywords if
syn keyword functionsKeywords delay

syn match integerConstants "\<\d\+\>" 
syn match floatConstants "\<\d\+\.\d\+\>"
syn match inPortKey "\<in\d\+\>"
syn match outPortKey "\<out\d\+\>"

syn region stmtBlock start="{" end="}" fold transparent
syn region commentBlock start="/\*" end="\*/" fold

let b:current_syntax = "rob"

hi def link loopKeywords Repeat
hi def link conditionalKeywords Conditional
hi def link functionsKeywords Identifier
hi def link integerConstants Constant
hi def link floatConstants Constant
hi def link inPortKey Identifier
hi def link outPortKey Identifier
hi def link commentBlock Comment
