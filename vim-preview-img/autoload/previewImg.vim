let s:Script_path = expand('<sfile>:p:h')

function! s:create_popup(opts) abort
  let s:popup_create = {buf -> popup_create(buf, #{
    \ col: a:opts.posx,
    \ line: a:opts.posy,
    \ minwidth: a:opts.width,
    \ maxwidth: a:opts.width,
    \ minheight: a:opts.height,
    \ maxheight: a:opts.height,
    \ border: [1, 1, 1, 1],
    \ padding: [0,1,0,1],
    \ zindex: 1000,
  \ })}
  autocmd TerminalOpen * ++once call s:popup_create(str2nr(expand('<abuf>')))
endfunction

function! s:previewImage(imgPos)
  let l:width_offset = 0.2
  let l:height_offset = 0.2
  let l:posX = float2nr(&columns * l:width_offset / 2)
  let l:posY = float2nr(&lines * l:height_offset / 2)
  let l:width = float2nr(&columns * (1 - l:width_offset))
  let l:height = float2nr(&lines * (1 - l:height_offset))

  let l:termCom = [s:Script_path . '/../showImg', l:posX, l:posY,
        \ l:width, l:height, a:imgPos]
  call s:create_popup({
    \ 'posx': l:posX, 'posy': l:posY, 'width': l:width, 'height': l:height
  \ })
  call term_start(l:termCom, { 'term_kill': 'term', 'hidden': 1 ,
        \ 'term_finish': 'close'})
  call setwinvar(winnr(), '&wincolor', 'Normal')
  setlocal nospell bufhidden=wipe nobuflisted nonumber
endfunction

function! previewImg#Jsj_getAbsPostoShowImg(imgPos)
  if a:imgPos[0] == '.' && a:imgPos[1] == '.'
    call s:previewImage(expand('%:p:h') . '/' . a:imgPos)
  elseif a:imgPos[0] == '~'
    let l:lists = split(a:imgPos, '/')
    let l:lists[0] = expand(a:imgPos[0])
    call s:previewImage(join(l:lists, '/'))
  elseif a:imgPos[0] == '/'
    call s:previewImage(a:imgPos)
  else
    echohl ErrorMsg
    echo "It's not a right path!!!"
    echohl None
  endif
endfunction
