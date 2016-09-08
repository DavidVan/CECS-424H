module project2

open System

let isPrime n =
    let mutable result = true
    let max = int64(Math.Ceiling(Math.Sqrt(float(n))))
    let mutable counter = 2L
    while counter <= max && result do
        if n % counter = 0L && counter <> n then
            result <- false
        counter <- counter + 1L
    result

let sumPrime max =
    let mutable sum = 2L
    for i in 3L .. 2L .. max do
        if isPrime i then
            sum <- sum + i
    sum

[<EntryPoint>]
let main argv =
    printfn "The sum is: %d" (sumPrime 2000000L)
    0