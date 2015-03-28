if &cp | set nocp | endif
let s:cpo_save=&cpo
set cpo&vim
inoremap <Nul> 
inoremap <expr> <Up> pumvisible() ? "\" : "\<Up>"
inoremap <expr> <S-Tab> pumvisible() ? "\" : "\<S-Tab>"
inoremap <expr> <Down> pumvisible() ? "\" : "\<Down>"
nnoremap <silent>  :CtrlP
nmap [c <Plug>GitGutterPrevHunk
nnoremap \d :YcmShowDetailedDiagnostic
nmap \hp <Plug>GitGutterPreviewHunk
nmap \hr <Plug>GitGutterRevertHunk
nmap \hs <Plug>GitGutterStageHunk
nmap ]c <Plug>GitGutterNextHunk
nmap gx <Plug>NetrwBrowseX
nnoremap <silent> <Plug>NetrwBrowseX :call netrw#NetrwBrowseX(expand("<cfile>"),0)
xnoremap <silent> <Plug>(signify-motion-outer-visual) :call sy#util#hunk_text_object(1)
onoremap <silent> <Plug>(signify-motion-outer-pending) :call sy#util#hunk_text_object(1)
xnoremap <silent> <Plug>(signify-motion-inner-visual) :call sy#util#hunk_text_object(0)
onoremap <silent> <Plug>(signify-motion-inner-pending) :call sy#util#hunk_text_object(0)
nnoremap <silent> <expr> <Plug>(signify-prev-hunk) &diff ? '[c' : ":\call sy#jump#prev_hunk(v:count1)\"
nnoremap <silent> <expr> <Plug>(signify-next-hunk) &diff ? ']c' : ":\call sy#jump#next_hunk(v:count1)\"
nnoremap <silent> <Plug>GitGutterPreviewHunk :GitGutterPreviewHunk
nnoremap <silent> <Plug>GitGutterRevertHunk :GitGutterRevertHunk
nnoremap <silent> <Plug>GitGutterStageHunk :GitGutterStageHunk
nnoremap <silent> <expr> <Plug>GitGutterPrevHunk &diff ? '[c' : ":\execute v:count1 . 'GitGutterPrevHunk'\"
nnoremap <silent> <expr> <Plug>GitGutterNextHunk &diff ? ']c' : ":\execute v:count1 . 'GitGutterNextHunk'\"
vmap <BS> "-d
inoremap <expr> 	 pumvisible() ? "\" : "\	"
let &cpo=s:cpo_save
unlet s:cpo_save
set backspace=indent,eol,start
set balloonexpr=eclim#util#Balloon(eclim#util#GetLineError(line('.')))
set completefunc=youcompleteme#Complete
set completeopt=preview,menuone
set cpoptions=aAceFsB
set expandtab
set fileencodings=ucs-bom,utf-8,default,latin1
set guifont=Anonymice\ Powerline:h14
set guitablabel=[%N]\ %t\ %M
set helplang=en
set hlsearch
set langmenu=none
set laststatus=2
set omnifunc=youcompleteme#OmniComplete
set runtimepath=~/.vim,~/.vim/bundle/Vundle.vim,~/.vim/bundle/vim-colors-solarized,~/.vim/bundle/ctrlp.vim,~/.vim/bundle/syntastic,~/.vim/bundle/YouCompleteMe,~/.vim/bundle/vim-airline,~/.vim/bundle/vim-gitgutter,~/.vim/bundle/vim-signify,~/.vim/bundle/vim-fugitive,/usr/local/Cellar/macvim/7.4-73_1/MacVim.app/Contents/Resources/vim/vimfiles,/usr/local/Cellar/macvim/7.4-73_1/MacVim.app/Contents/Resources/vim/runtime,/usr/local/Cellar/macvim/7.4-73_1/MacVim.app/Contents/Resources/vim/vimfiles/after,~/.vim/after,~/.vim/bundle/Vundle.vim,~/.vim/bundle/Vundle.vim/after,~/.vim/bundle/vim-colors-solarized/after,~/.vim/bundle/ctrlp.vim/after,~/.vim/bundle/syntastic/after,~/.vim/bundle/YouCompleteMe/after,~/.vim/bundle/vim-airline/after,~/.vim/bundle/vim-gitgutter/after,~/.vim/bundle/vim-signify/after,~/.vim/bundle/vim-fugitive/after,~/.vim/eclim,~/.vim/eclim/after
set shiftwidth=4
set smartindent
set tabstop=4
set updatetime=2000
" vim: set ft=vim :
