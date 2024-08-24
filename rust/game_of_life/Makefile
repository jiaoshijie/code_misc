# V := @

wasm:
	$(V)rustc --edition 2021 -C lto -C opt-level=s --crate-type cdylib --target wasm32-unknown-unknown life.rs -o life.wasm
	$(V)wasm-strip life.wasm

server:
	$(V)python3 -m http.server

wat:
	$(V)wasm2wat life.wasm

clean:
	$(V)rm -rf *.wasm *.o
