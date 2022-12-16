command! -nargs=? -complete=file ShowImg
      \ call previewImg#Jsj_getAbsPostoShowImg(<q-args>)

nnoremap <silent> <leader>P :ShowImg <cfile><cr>
