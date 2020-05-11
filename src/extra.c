#include <windows.h>
#include <stdio.h>
#include <sys/stat.h>

#include "pico.h"

typedef void (*ACTION)(void);
typedef int (*RENDERER_TYPE)(int, int, ACTION);
typedef void (*DRAWLINE_TYPE)(int, int, int, int);
typedef void (*CLEAR_TYPE)(void);
typedef void (*SWAP_TYPE)(void);

RENDERER_TYPE RENDERER;
DRAWLINE_TYPE DRAWLINE;
CLEAR_TYPE CLEAR;
SWAP_TYPE SWAP;

any CB;

HANDLE DL_LOADER_HANDLE = NULL;

int getIntParam(any x)
{
    if (!isNil(x) && isNum(x))
    {
        return unBox(x);
    }
    return 700;
}

any doSDLClear(any x)
{
    CLEAR();
}

any doSDLSwap(any x)
{
    SWAP();
}

any doSDLLine(any x)
{
    int x1 = getIntParam(car(cdr(x)));
    int y1 = getIntParam(car(cdr(cdr(x))));
    int x2 = getIntParam(car(cdr(cdr(cdr(x)))));
    int y2 = getIntParam(car(cdr(cdr(cdr(cdr(x))))));
    DRAWLINE(x1, y1, x2, y2);
    return x;
}


void perform()
{
    EVAL(CB);
}

any doSDL(any x)
{
    any p1 = car(cdr(x));
    any p2 = car(cdr(cdr(x)));

    int width = getIntParam(p1);
    int height = getIntParam(p2);

    DL_LOADER_HANDLE = LoadLibrary("glue.dll");

    if (DL_LOADER_HANDLE == NULL)
    {
        printf("Failed to load the DLL\n");
        return x;
    }

    RENDERER = (RENDERER_TYPE)GetProcAddress(DL_LOADER_HANDLE, "glue");
    DRAWLINE = (DRAWLINE_TYPE)GetProcAddress(DL_LOADER_HANDLE, "DrawLine");
    CLEAR = (CLEAR_TYPE)GetProcAddress(DL_LOADER_HANDLE, "Clear");
    SWAP =  (SWAP_TYPE)GetProcAddress(DL_LOADER_HANDLE, "Swap");


    if (RENDERER == NULL)
    {
        printf("BAD renderer\n");
        return x;
    }

    any p3 = cdr(cdr(cdr(x)));
    CB = p3;

    RENDERER(width, height, perform);

    //any xx = cons(car(p3), cons(box(65), Nil));
    //if (!isNil(p3))
    //{
    //    EVAL(xx);
    //}

    FreeLibrary(DL_LOADER_HANDLE);
    DL_LOADER_HANDLE = NULL;

    return x;
}


// (do 'flg|num ['any | (NIL 'any . prg) | (T 'any . prg) ..]) -> any
any doDo2(any x) {
   any f, y, z, a;

   x = cdr(x);
   if (isNil(f = EVAL(car(x))))
      return Nil;
   if (isNum(f) && num(f) < 0)
      return Nil;
   x = cdr(x),  z = Nil;
   for (;;) {
      if (isNum(f)) {
         if (f == Zero)
            return z;
         f = (any)(num(f) - 4);
      }
      y = x;
      do {
         if (!isNum(z = car(y))) {
            if (isSym(z))
            {
               z = val(z);
               printf("BEFORE\n");
               EVAL(y);
               printf("AFTER\n");
                break;
            }
            else if (isNil(car(z))) {
               z = cdr(z);
               if (isNil(a = EVAL(car(z))))
                  return prog(cdr(z));
               val(At) = a;
               z = Nil;
            }
            else if (car(z) == T) {
               z = cdr(z);
               if (!isNil(a = EVAL(car(z)))) {
                  val(At) = a;
                  return prog(cdr(z));
               }
               z = Nil;
            }
            else {
                any p1 = car(z);
               z = evList(z);
            }
         }
      } while (isCell(y = cdr(y)));
   }
}
