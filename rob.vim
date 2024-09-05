" Vim syntax file
" Language: Robcmp Small LLVM Arduino Frontend
" Maintainer: Thiago Borges de Oliveira
" Latest Revision: 4 Aug 2023

if exists("b:current_syntax")
    finish
endif

syn keyword keywords while loop if else delay print return register at volatile const asm type interface implements use copy bind to singleton transient
syn keyword keywords naked weak section inline noinline
syn keyword typeKeywords void char int8 int16 int32 int64 uint8 uint16 uint32 uint64 long float double bool enum
syn keyword operatorKeywords and or quando esta servo
syn keyword booleanKeyword true false

syn match integerConstants "\<\d\+\([Ee][=+]\?[0-9]\+\)\?[Uu]\?\>" 
syn match hexConstants "\<0x[0-9a-fA-F]\+\>" 
syn match floatConstants "\<\d\+\.\d\+\([Ee][-+]\?[0-9]\+\)\?L\?D\?\>"
syn match charConstants "'\\\?.'"
syn match inPortKey "\<in\d\+\>"
syn match outPortKey "\<out\d\+\>"
syn match stringSpecial "\\."
syn match commentLine "\/\/.*"

syn region stmtBlock start="{" end="}" fold contains=ALL transparent
syn region stringConstant start=+"+ skip=+\\\\\|\\"+  end=+"+ contains=stringSpecial
syn region commentBlock start="/\*" end="\*/" fold contains=ALL 

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
