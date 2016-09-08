module project1

open System

let placeTarget() =
    (new Random()).NextDouble() * 1000.0 // System.Random

let getAngle() =
    printfn "Enter an angle between 0.0 and 90.0."
    let mutable angle = float (Console.ReadLine()) // System.Console
    while angle < 0.0 || angle > 90.0 do
        if angle < 0.0 then
            printfn "That angle is less than 0.0. Please enter an angle between 0.0 and 90.0."
            angle <- float (Console.ReadLine())
        elif angle > 90.0 then
            printfn "That angle is greater than 90.0. Please enter an angle between 0.0 and 90.0."
            angle <- float (Console.ReadLine())
    angle

let getGunpowder() =
    printfn "Enter an amount of gunpowder to use in kilograms. Amount must be positive."
    let mutable gunpowderAmount = float (Console.ReadLine())
    while gunpowderAmount < 0.0 do
        printfn "That amount is negative! Please enter a positive amount of gunpowder to use."
        gunpowderAmount <- float (Console.ReadLine())
    gunpowderAmount

let calculateDistance angle gunpowderAmount =
    let velocity = gunpowderAmount * 30.0
    let angleInDegrees = angle * Math.PI / 180.0
    (velocity * velocity * Math.Sin(2.0 * angleInDegrees))/9.8

let isHit location distance =
    distance <= location + 1.0 && distance >= location - 1.0
        

//[<EntryPoint>] // Commented out at the moment to run the other program.
let main argv = 
    let distanceToTarget = (new Random()).NextDouble() * (1000.0 - 1.0) + 1.0
    printfn "Distance to target is: %f" distanceToTarget
    let mutable hit = false
    while not hit do
        let angle = getAngle()
        let gunpowderAmount = getGunpowder()
        let estimatedDistance = calculateDistance angle gunpowderAmount
        // printfn "DEBUG: Estimated Distance: %f" estimatedDistance
        if isHit distanceToTarget estimatedDistance then
            printfn "You hit the target!"
            hit <- true
        else
            if estimatedDistance > distanceToTarget + 1.0 then
                printfn "You missed the target! (%fm long)" (estimatedDistance - distanceToTarget)
            elif estimatedDistance < distanceToTarget - 1.0 then
                printfn "You missed the target! (%fm short)" (distanceToTarget - estimatedDistance)
    0 // Return integer exit code for successful run