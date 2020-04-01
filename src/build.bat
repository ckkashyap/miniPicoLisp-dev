@echo off
set MINGW=mingw32
rem set MINGW=mingw64

if not exist %MINGW% (
    if not exist %MINGW%.zip powershell invoke-webrequest "https://github.com/ckkashyap/mingw/blob/master/%MINGW%-03-29-2020.zip?raw=true" -outfile %MINGW%.zip
    powershell expand-archive %MINGW%.zip
)

set WIDTH=
if "mingw32" == "%MINGW%" set WIDTH=-DWORD_TYPE=int32_t -DUNSIGNED_WORD_TYPE=uint32_t

%MINGW%\bin\gcc -o gen3m.exe gen3m.c
gen3m.exe 0 init.s lib.s pilog.s
%MINGW%\bin\gcc -c -O2 -pipe -falign-functions -fomit-frame-pointer -fno-strict-aliasing -W -Wimplicit -Wreturn-type -Wunused -Wformat -Wuninitialized -Wstrict-prototypes %WIDTH% -D_GNU_SOURCE  main.c
%MINGW%\bin\gcc -c -O2 -pipe -falign-functions -fomit-frame-pointer -fno-strict-aliasing -W -Wimplicit -Wreturn-type -Wunused -Wformat -Wuninitialized -Wstrict-prototypes %WIDTH% -D_GNU_SOURCE  gc.c
%MINGW%\bin\gcc -c -O2 -pipe -falign-functions -fomit-frame-pointer -fno-strict-aliasing -W -Wimplicit -Wreturn-type -Wunused -Wformat -Wuninitialized -Wstrict-prototypes %WIDTH% -D_GNU_SOURCE  apply.c
%MINGW%\bin\gcc -c -O2 -pipe -falign-functions -fomit-frame-pointer -fno-strict-aliasing -W -Wimplicit -Wreturn-type -Wunused -Wformat -Wuninitialized -Wstrict-prototypes %WIDTH% -D_GNU_SOURCE  flow.c
%MINGW%\bin\gcc -c -O2 -pipe -falign-functions -fomit-frame-pointer -fno-strict-aliasing -W -Wimplicit -Wreturn-type -Wunused -Wformat -Wuninitialized -Wstrict-prototypes %WIDTH% -D_GNU_SOURCE  sym.c
%MINGW%\bin\gcc -c -O2 -pipe -falign-functions -fomit-frame-pointer -fno-strict-aliasing -W -Wimplicit -Wreturn-type -Wunused -Wformat -Wuninitialized -Wstrict-prototypes %WIDTH% -D_GNU_SOURCE  subr.c
%MINGW%\bin\gcc -c -O2 -pipe -falign-functions -fomit-frame-pointer -fno-strict-aliasing -W -Wimplicit -Wreturn-type -Wunused -Wformat -Wuninitialized -Wstrict-prototypes %WIDTH% -D_GNU_SOURCE  math.c
%MINGW%\bin\gcc -c -O2 -pipe -falign-functions -fomit-frame-pointer -fno-strict-aliasing -W -Wimplicit -Wreturn-type -Wunused -Wformat -Wuninitialized -Wstrict-prototypes %WIDTH% -D_GNU_SOURCE  io.c
%MINGW%\bin\gcc -o picolisp.exe main.o gc.o apply.o flow.o sym.o subr.o math.o io.o -lm
