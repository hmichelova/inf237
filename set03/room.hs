import Data.List

main :: IO ()
main = interact (show . process . readInput)

readInput :: String -> [Integer]
readInput = (map read) . words

process :: [Integer] -> Integer
process (n : m : xs) = calculate cans colors
    where
        cans = sort $ take (fromIntegral n) xs
        colors = sort $ drop (fromIntegral n) xs

calculate :: [Integer] -> [Integer] -> Integer
calculate _        []       = 0
calculate (x : xs) (y : ys) = if x < y
    then calculate xs (y : ys)
    else x - y + calculate (x : xs) ys

