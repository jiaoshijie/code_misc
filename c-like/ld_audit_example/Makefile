V := @

help:
	@echo "Just simply look at this file and do what you want to do, OK?"

ld_preload:
	$(V)cc -fPIC -shared -o libpreload.so preloadlib.c -lm

ld_audit:
	$(V)cc -fPIC -shared -o libaudit.so auditlib.c

main: ld_preload ld_audit
	$(V)cc main.c -o main -lm
	LD_PRELOAD=./libpreload.so LD_AUDIT=./libaudit.so ./main argument1

clean:
	rm -rf main *.so
