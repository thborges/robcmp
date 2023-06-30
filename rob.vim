" Vim syntax file
" Language: Robcmp Small LLVM Arduino Frontend
" Maintainer: Thiago Borges de Oliveira
" Latest Revision: 10 June 2015

if exists("b:current_syntax")
    finish
endif

syn keyword keywords while if delay print return true false
syn keyword typeKeywords void char short int long unsigned float double bool
syn keyword operatorKeywords and or quando esta servo

syn match integerConstants "\<\d\+\>" 
syn match floatConstants "\<\d\+\.\d\+\>"
syn match inPortKey "\<in\d\+\>"
syn match outPortKey "\<out\d\+\>"
syn match stringSpecial "\\."

syn region stmtBlock start="{" end="}" fold transparent
syn region commentBlock start="/\*" end="\*/" fold
syn region commentLine start="//" end="\n" fold
syn region stringConstant start=+"+ skip=+\\\\\|\\"+  end=+"+ contains=stringSpecial

let b:current_syntax = "rob"

hi def link keywords Repeat
hi def link integerConstants Constant
hi def link floatConstants Constant
hi def link stringConstant String
hi def link stringSpecial Special
hi def link inPortKey Identifier
hi def link outPortKey Identifier
hi def link typeKeywords Type
hi def link commentBlock Comment
hi def link commentLine Comment
hi def link operatorKeywords Operator
