let gcd x y =
    let mutable xM = x
    let mutable yM = y
    while xM <> yM do
        if xM > yM then
            xM <- xM - yM
        else
            yM <- yM - xM
    xM

printf "%d\n" (gcd 111 259)