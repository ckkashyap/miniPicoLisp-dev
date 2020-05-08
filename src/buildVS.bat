@cl /nologo /Zi gen3m2.c
@gen3m2.exe 0 init.s lib.s pilog.s

@del ram2.d rom2.d sym2.d
@ren ram.d ram2.d
@ren rom.d rom2.d
@ren sym.d sym2.d

@cl /nologo /Zi gen3m.c
@gen3m.exe 0 init.s lib.s pilog.s

diff ram.d ram2.d
diff rom.d rom2.d
diff sym.d sym2.d

@cl /nologo /Zi /Fe: picolisp.exe main.c gc.c apply.c flow.c sym.c subr.c math.c io.c
