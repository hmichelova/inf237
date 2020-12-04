readInput :: String -> [Integer]
readInput = (map read) . tail . words

writeOutput :: [Integer] -> String
writeOutput = unlines . map (\number -> show number ++ " is " ++ 
    if even number then "even" else "odd")

main :: IO ()
main = interact (writeOutput . readInput)
