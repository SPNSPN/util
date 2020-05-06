set nocompatible
set number
set tabstop=4
set shiftwidth=4
set backspace=start,eol,indent
set cindent
set autochdir
syntax on
filetype on

command SjisUtf8 e ++enc=cp932 | set fileencoding=utf-8
set clipboard=unnamed,autoselect

augroup IndentSettiong
	autocmd!
	autocmd BufRead,BufNewFile *.lisp setl nocindent autoindent lisp
	autocmd BufRead,BufNEwFile *.lsp setl nocindent autoindent lisp
	autocmd BufRead,BufNEwFile *.mal setl nocindent autoindent lisp filetype=scheme
	autocmd BufRead,BufNEwFile *.snv setl nocindent autoindent lisp filetype=scheme
augroup END

 augroup PrevimSettings
 	autocmd!
 	autocmd BufNewFile,BufRead *.{md,mdwn,mkd,mkdn,mark*} set filetype=markdown
 augroup END
 

au BufRead,BufNewFile *.hy set filetype=clojure
