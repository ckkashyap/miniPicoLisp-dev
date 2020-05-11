cl /Zi gen3m.c
gen3m.exe 0 init.s lib.s pilog.s
cl /Zi /Fe: picolisp.exe main.c gc.c apply.c flow.c sym.c subr.c math.c io.c extra.c
cl /I SDL2-2.0.12\include SDL2-2.0.12\lib\x86\SDL2.lib /LD glue.c /Fe:glue.dll
