" Vim syntax file
" Language: Robcmp Small LLVM Arduino Frontend
" Maintainer: Thiago Borges de Oliveira
" Latest Revision: 4 Aug 2023

if exists("b:current_syntax")
    finish
endif

syn keyword keywords while loop if else delay print return register at volatile const asm type
syn keyword typeKeywords void char int8 int16 int32 int64 long unsigned float double bool
syn keyword operatorKeywords and or quando esta servo
syn keyword booleanKeyword true false

syn match integerConstants "\<\d\+\>" 
syn match hexConstants "\<0x[0-9a-fA-F]\+\>" 
syn match floatConstants "\<\d\+\.\d\+L\?D\?\>"
syn match charConstants "'\\\?.'"
syn match inPortKey "\<in\d\+\>"
syn match outPortKey "\<out\d\+\>"
syn match stringSpecial "\\."
syn match commentLine "\/\/.*"

syn region commentBlock start="/\*" end="\*/" fold containedin=stmtBlock
syn region stringConstant start=+"+ skip=+\\\\\|\\"+  end=+"+ contains=stringSpecial
syn region stmtBlock start="{" end="}" keepend transparent fold

let b:current_syntax = "rob"

hi def link keywords Repeat
hi def link integerConstants Constant
hi def link hexConstants Constant
hi def link floatConstants Constant
hi def link charConstants Constant
hi def link stringConstant String
hi def link stringSpecial Special
hi def link inPortKey Identifier
hi def link outPortKey Identifier
hi def link typeKeywords Type
hi def link commentBlock Comment
hi def link commentLine Comment
hi def link operatorKeywords Operator
hi def link booleanKeyword Boolean
