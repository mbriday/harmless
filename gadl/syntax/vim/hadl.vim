" Vim syntax file
" This file should be installed in folder: ~/.vim/syntax (create it if it does
" not exists)
" Language:	HADL
" Maintainer:	M. Briday
" initial version: G. Savaton.
" URL: http://harmless.rts-software.org
" Last Change:	2012/06/29
" updated Mik : rev 1146 gadl

" For version 5.x: Clear all syntax items
" For version 6.x: Quit when a syntax file was already loaded
if version < 600
 syntax clear
elseif exists("b:current_syntax")
 finish
endif

" Harmless is case-sensitive.
syn case match

" We don't need to look backwards to highlight correctly;
" this speeds things up greatly.
syn sync minlines=1 maxlines=1

syn keyword hadlElement model except include port device architecture write shared behavior format select component every interrupt memory width address type RAM ROM register stride read program counter pipeline stage machine bypass release in maps to stall default instruction fetch debug big little endian typedef out when field on slice is others signed or syntax switch number octal decimal hexadecimal binary suffix prefix size jumpTaken add cycle use timing signal emit broadcast activation wait for until loop while 
syn keyword hadlTree            case
syn keyword hadlStatement       error warning do nop return print if then elseif else end true false
syn keyword hadlOperator        ror rol cat
syn keyword hadlPseudoType      void

" Identifiers
syn match hadlIdentifier		"[a-zA-Z_][a-zA-Z0-9_]*"
syn match hadlLabel		        "[@#][a-zA-Z_][a-zA-Z0-9_]*"
syn match hadlType                      "[us][0-9][0-9]*"


" Strings and numbers
syn region  hadlString		start=+"+ end=+"+
" binary, dec, hex and octal, postfixed with nothing, or s or kb or mb.
syn match   hadlNumber		"\<\([0-9_]\+\|\<[xX][0-9a-fA-F_]\+\|\<[oO][0-7_]\+\|\<[bB][0-1_]\+\)\(s\|kb\|mb\|\)\>"
syn match   hadlNumber		"\<[mM][0-1\-_]\+"

" Comments.
syn region  hadlComment	oneline contains=hadlTodo start="--"  end="$"
" Todo (only highlighted in comments)
syn keyword hadlTodo contained	TODO FIXME XXX


" Delimiters

syn match   hadlDelimiter        "[();,{}|:=\[\]<>&^$-+*/]"

" Define the default highlighting.
" For version 5.7 and earlier: only when not done already
" For version 5.8 and later: only when an item doesn't have highlighting yet
if version >= 508 
  command -nargs=+ HiLink hi def link <args>

  " The default methods for highlighting. Can be overridden later.
  HiLink hadlComment		Comment
  HiLink hadlElement		Keyword
  HiLink hadlTree		PreProc
  HiLink hadlStatement		Keyword
  HiLink hadlOperator		Operator
  HiLink hadlTodo		Todo
  HiLink hadlIdentifier		Identifier
  HiLink hadlLabel		PreProc
  HiLink hadlString		String
  HiLink hadlNumber		Number
  HiLink hadlDelimiter		Delimiter
  HiLink hadlType		Type
  HiLink hadlPseudoType		Type
  delcommand HiLink
endif

let b:current_syntax = "hadl"

" vim: ts=8
