let sumSelect predFn selectFn list =
    let mutable sum = 0
    for n in list do
        if predFn n then
            sum <- sum + selectFn n
    sum

let identity n =
    n

[<EntryPoint>]
let main argv = 
    let nums = seq {1 .. 10}
    
    // Sum all.
    nums
    |> sumSelect (fun x -> true) (fun x -> x)
    |> printfn "The sum of all integers is: %d"

    let nums = seq {-10 .. 10}
    
    // Sum all positive integers.
    nums
    |> sumSelect (fun x -> (x > 0)) (fun x -> x)
    |> printfn "The sum of all positive integers is: %d"

    let strs = seq ["aaaa"; "aaaa"; "aaaa"; "aaa"]
    
    // Sum of all strings with length greater than 3.
    strs
    |> sumSelect (fun x -> (x.Length > 3)) (fun x -> x.Length)
    |> printfn "The sum of all strings with length greater than 3 is: %d"

    let tups = seq [(true, 1); (false, 2); (false, 3)]

    // Sum of all integers in tuple of type (bool * int), where bool is false.
    tups
    |> sumSelect (fun x -> not (fst x)) (fun x -> snd x)
    |> printfn "The sum of all integers in tuple of type (bool * int), where bool is false is: %d"

    0 // return an integer exit code
