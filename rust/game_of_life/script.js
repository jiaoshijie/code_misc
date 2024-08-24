let g_wasm_obj = undefined;

WebAssembly.instantiateStreaming(
  fetch("life.wasm"), {
    Math: {
      random: () => Math.random(),
    },
    IO: {
      print: (ptr, len) => {
        const linearMem = new Uint8Array(g_wasm_obj.instance.exports.memory.buffer);
        str = new TextDecoder().decode(linearMem.slice(ptr, ptr + len));
        console.log(str);
      },
    }
  })
  .then((wasm_obj) => {
    g_wasm_obj = wasm_obj;

    console.log('The answer is: ', g_wasm_obj.instance.exports.add_one_random(102));
    g_wasm_obj.instance.exports.greeting();
  });

