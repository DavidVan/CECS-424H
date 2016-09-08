let concat (str:string) = str + str
let harmonicMean x y = 1.0 / ((1.0/x) + (1.0/y))
let repeatString str n =
    let mutable count = 1
    let mutable ret = str
    while count < n do
        ret <- ret + "," + str
        count <- count + 1
    ret

printfn "%s" (concat "test")
printfn "%f" (harmonicMean 1.4 2.3)
printfn "%s" (repeatString "hello" 5)