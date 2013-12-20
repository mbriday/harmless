" Vim syntax file
" Language:	HADL
" Maintainer:	G. Savaton
" URL: http://www.dummy.fr
" Last Change:	2004-05-19

" For version 5.x: Clear all syntax items
" For version 6.x: Quit when a syntax file was already loaded
if version < 600
 syntax clear
elseif exists("b:current_syntax")
 finish
endif

" Atl is case-sensitive.
syn case match

" We don't need to look backwards to highlight correctly;
" this speeds things up greatly.
syn sync minlines=1 maxlines=1

syn keyword hadlElement         architecture extends model aggregate alternative behavior format syntax number pipeline component match context
syn keyword hadlClause          do maps to prefix suffix echo init stage priority reusable data instructions release bypass in
syn keyword hadlDeclaration     external var att out field resource port default slice
syn keyword hadlStatement       if then else elseif end for loop when return run as inline is
syn keyword hadlOperator        rem lsl lsr asr asl ror and or not xor extend
syn keyword hadlPredefined      true false self
syn keyword hadlPseudoType      void

" Identifiers
syn match hadlIdentifier		"[a-zA-Z_][a-zA-Z0-9_]*"
syn match hadlLabel		        "[@#][a-zA-Z_][a-zA-Z0-9_]*"
syn match hadlType                      "[us]'[0-9][0-9]*"

" Todo (only highlighted in comments)
syn keyword hadlTodo contained	TODO FIXME XXX

" Comments.
syn region  hadlComment	oneline contains=hadlTodo start="--"  end="$"

" Strings and numbers
syn region  hadlString		start=+"+ end=+"+
syn match   hadlNumber		"\<[0-9]\+\>\|\<0[xX][0-9a-fA-F]\+\>\|\<0[oO][0-7]\+\>"

" Delimiters

syn match   hadlDelimiter        "[();,{}|:\[\]<>&^$-+*/]"

" Define the default highlighting.
" For version 5.7 and earlier: only when not done already
" For version 5.8 and later: only when an item doesn't have highlighting yet
if version >= 508 || !exists("did_atl_syn_inits")
  if version < 508
    let did_atl_syn_inits = 1
    command -nargs=+ HiLink hi link <args>
  else
    command -nargs=+ HiLink hi def link <args>
  endif

  " The default methods for highlighting. Can be overridden later.
  HiLink hadlComment	        Comment
  HiLink hadlElement	        Keyword
  HiLink hadlClause              Keyword
  HiLink hadlStatement           Keyword
  HiLink hadlDeclaration           Keyword
  HiLink hadlOperator           Operator
  HiLink hadlTodo	        Todo
  HiLink hadlIdentifier          Identifier
  HiLink hadlLabel               PreProc
  HiLink hadlString              String
  HiLink hadlNumber              Number
  HiLink hadlDelimiter           Delimiter
  HiLink hadlPredefined          Keyword
  HiLink hadlType               Type
  HiLink hadlPseudoType               Type

  delcommand HiLink
endif

let b:current_syntax = "hadl"

" vim: ts=8
