set tabstop=8 shiftwidth=8
set autoindent
set smartindent
set cindent
command! -nargs=1 BettyFormat call system('betty --style=check ' . shellescape(<q-args>) . ' && betty --style=fix ' . shellescape(<q-args>))
nnoremap <Leader>b :BettyFormat <c-r>%<cr>
