
(de square (X Y S)
    (let ( X1 X X2 (+ X S) Y1 Y Y2 (+ Y S))
        (sdlLine X1 Y1 X1 Y2)
        (sdlLine X1 Y2 X2 Y2)
        (sdlLine X2 Y2 X2 Y1)
        (sdlLine X2 Y1 X1 Y1)

    )
)


(de render ()
    (sdlColor 0 0 0)
    (sdlClear)
    (sdlColor 255 255 0)
    (sdlLine 10 10 200 200)
    (sdlLine 200 200 300 200)

    (sdlColor 0 255 0)
    (for I 10
        (square (* I 20) 400 15)
     )

    (sdlColor 0 0 255)
    (square 10 500 20)

    (sdlSwap)
)
(sdl 600 600 render)
(bye)
