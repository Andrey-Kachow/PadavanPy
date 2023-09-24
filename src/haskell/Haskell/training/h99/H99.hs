module H99 where

import Data.Tuple
import Data.List hiding (group)
import System.Random hiding (split)
import Control.Monad.IO.Class

-- PROBLEM 1

myLast :: [a] -> a
myLast []     = error ""
myLast [x]    = x
myLast (_:xs) = myLast xs

-- PROBLEM 2

myButLast :: [a] -> a
myButLast (x0:[_]) = x0
myButLast (_:xs)   = myButLast xs
myButLast xs       = error ""

-- PROBLEM 3

elementAt :: [a] -> Int -> a
elementAt [] _     = error ""
elementAt (x:_) 1  = x
elementAt (_:xs) k = elementAt xs (k - 1)

-- PROBLEM 4

myLength :: [a] -> Int
myLength []     = 0
myLength (_:xs) = 1 + myLength xs

-- PROBLEM 5

myReverse :: [a] -> [a]
myReverse []     = []
myReverse (x:xs) = (myReverse xs) ++ [x]

-- PROBLEM 6

isPalindrome :: (Eq a) => [a] -> Bool
isPalindrome []     = True
isPalindrome [x]    = True
isPalindrome (x:xs) =
  let
    (y:sy) = myReverse xs
  in
    x == y && isPalindrome sy

-- PROBLEM 7

data NestedList a = Elem a | List [NestedList a]

flatten :: NestedList a -> [a]
flatten (Elem x)        = [x]
flatten (List [])       = []
flatten (List (e : es)) = (flatten e) ++ (flatten (List es))

-- PROBLEM 8

compress :: (Eq a) => [a] -> [a]
compress []         = []
compress [x]        = [x]
compress (x1:x2:xs)
  | x1 == x2  = rest
  | otherwise = x1 : rest
    where
      rest = compress (x2:xs)

-- PROBLEM 9

pack :: (Eq a) => [a] -> [[a]]
pack []  = []
pack [x] = [[x]]
pack (x:xs)
  | x == y    = ((x:y:ys):zs)
  | otherwise = ([x]:(y:ys):zs)
    where
      ((y:ys):zs) = pack xs

-- PROBLEM 10

encode :: (Eq a) => [a] -> [(Int,  a)]
encode xs = map (\yys@(y:ys) -> (myLength yys, y)) (pack xs)

-- PROBLEM 11

data Encoding a = Single a | Multiple Int a
                  deriving (Show, Eq)

toEncoding :: [a] -> Encoding a
toEncoding []  = error ""
toEncoding [x] = Single x
toEncoding xs@(x:_)  = Multiple (myLength xs) x

encodeModified :: (Eq a) => [a] -> [Encoding a]
encodeModified xs = map toEncoding (pack xs)

-- PROBLEM 12

decodeModified :: [Encoding a] -> [a]
decodeModified [] = []
decodeModified ((Single x):xs)
  = x : decodeModified xs
decodeModified ((Multiple n x):xs)
  = (take n (repeat x)) ++ decodeModified xs

-- PROBLEM 13

encodeDirect :: (Eq a) => [a] -> [Encoding a]
encodeDirect zs = reverse $ countEncode zs []
  where
    countEncode [] res            = res
    countEncode (x:xs) []         = countEncode xs [Single x]
    countEncode (x:xs) (enc:encs) =
      let
        push x (Single y)
          | x == y    = let pairOf = 2 in [Multiple pairOf x]
          | otherwise = [Single x, Single y]
        push x other@(Multiple n y)
          | x == y    = [Multiple (n + 1) x]
          | otherwise = [Single x, other]
      in
        countEncode xs ((push x enc) ++ encs)

-- PROBLEM 14

dupli :: [a] -> [a]
dupli []     = []
dupli (x:xs) = x : x : dupli xs

-- PROBLEM 15

repli :: [a] -> Int -> [a]
repli [] _     = []
repli (x:xs) n = (take n (repeat x)) ++ repli xs n

-- PROBLEM 16

dropEvery :: [a] -> Int -> [a]
dropEvery xs i = dropEveryAux xs i i
  where
    dropEveryAux [] _ _     = []
    dropEveryAux (x:xs) i 1 = dropEveryAux xs i i
    dropEveryAux (x:xs) i j = x : dropEveryAux xs i (j - 1)

-- PROBLEM 17

split :: [a] -> Int -> ([a], [a])
split [] _     = ([], [])
split xs 0     = ([], xs)
split (x:xs) i = (x:us, vs)
  where
    (us, vs) = split xs (i - 1)

-- PROBLEM 18

slice :: [a] -> Int -> Int -> [a]
slice xs i j = sliceAux xs i j 0
  where
    sliceAux [] _ _ _ = []
    sliceAux (x:xs) i j cur =
      let
        next = sliceAux xs i j (cur + 1)
        result
          | cur < i              = next
          | i <= cur && cur <= j = x : next
          | otherwise            = []
      in
        result

-- PROBLEM 19

rotate :: [a] -> Int -> [a]
rotate xs n =
  let
    (us, vs) = split xs splitPoint
    splitPoint
      | n >= 0    = n
      | otherwise = n + myLength xs
  in
    vs ++ us

-- PROBLEM 20

removeAt :: Int -> [a] -> (a, [a])
removeAt _ [] = error ""
removeAt 1 (x:xs) = (x, xs)
removeAt n (x:xs) =
  let
    (removedElem, ys) = removeAt (n - 1) xs
  in
    (removedElem, x:ys)

-- PROBLEM 21

insertAt :: a -> [a] -> Int -> [a]
insertAt y [] 0 = [y]
insertAt _ [] _ = error ""
insertAt y xs 0 = y:xs
insertAt y (x:xs) i = x : (insertAt y xs (i - 1))

-- PROBLEM 22

range :: Int -> Int -> [Int]
range i j = [i..j]

-- PROBLEM 23

rndSelect :: MonadIO m => [a] -> Int -> m [a]
rndSelect xs n = do
  g <- newStdGen
  return $ map (\i -> xs !! i) (take n $ nub (randomRs (0, length xs - 1) g))

-- PROBLEM 24

diffSelect :: MonadIO m => Int -> Int -> m [Int]
diffSelect n m = rndSelect [1..m] n

-- PROBLEM 25

rndPermu :: MonadIO m => [a] -> m [a]
rndPermu xs = rndSelect xs (length xs)

-- PROBLEM 26

fact :: Int -> Int
fact 0 = 1
fact 1 = 1
fact x = x * fact (x - 1)

numCombinations :: Int -> Int -> Int
numCombinations n r = (fact n) `div` ((fact r) * (fact (n - r)))

combinations :: [a] -> Int -> [[a]]
combinations [] _       = []
combinations xs 1       = map (\x -> [x]) xs
combinations (x : xs) n = withX ++ withoutX
  where
    withX    = map (\pair -> x:pair) $ combinations xs (n - 1)
    withoutX = combinations xs n

-- PROBLEM 27

noClashes :: (Eq a) => [[a]] -> Bool
noClashes xs = length concated == length (nub concated)
  where
    concated = concat xs

group :: (Eq a) => [Int] -> [a] -> [[[a]]]
group _ []      = []
group [] _      = error ""
group [n] xs    = [combinations xs n]
group (n:ns) xs = foldr (++) [] $ groups
  where
    combs   = combinations xs n
    groups  = map (\comb -> map (\g -> comb : g) (group ns (xs \\ comb))) combs

-- PROBLEM 28

lsort :: [[a]] -> [[a]]
lsort []     = []
lsort (l:ls) = lsort smallerLists ++ [l] ++ lsort largerLists
  where
    smallerLists = [li | li <- ls, length l > length li]
    largerLists  = [li | li <- ls, length l <= length li]

-- PROBLEM 29
-- PROBLEM 30
-- PROBLEM 31

isPrime :: Int -> Bool
isPrime n = all (\x -> n `mod` x /= 0) [2..(n - 1)]

-- PROBLEM 32

myGCD :: Int -> Int -> Int
myGCD a b
  | b > a     = myGCD b a
  | r == 0    = b
  | otherwise = myGCD b r
    where
      r = a `mod` b

-- PROBLEM 33

coprime :: Int -> Int -> Bool
coprime a b = myGCD a b == 1

-- PROBLEM 34

totient :: Int -> Int
totient m = length $ filter (coprime m) [1..(m - 1)]

-- PROBLEM 35

primeFactors :: Int -> [Int]
primeFactors 0 = []
primeFactors n
  | f == noFactor = []
  | otherwise     = f : (primeFactors q)
    where
      noFactor = -1
      f        = findFactor n 2
      q        = n `div` f
      findFactor m i
        | i > m          = noFactor
        | m `mod` i == 0 = i
        | otherwise      = findFactor m (i + 1)

-- PROBLEM 36

primeFactorsMult :: Int -> [(Int, Int)]
primeFactorsMult n = map swap $ encode $ primeFactors n

-- PROBLEM 37

isZero :: Int -> Bool
isZero 0 = True
isZero _ = False

phi :: Int -> Int
phi n = foldr (*) 1 $ map (\(p, m) -> (p - 1) * p ^ (m - 1)) (primeFactorsMult n)

-- PROBLEM 38
-- PROBLEM 39

primesR :: Int -> Int -> [Int]
primesR n m = filter isPrime [n..m]

-- PROBLEM 40

goldbach :: Int -> (Int, Int)
goldbach x =
  let
    relevantPrimes = primesR 2 (x - 2 )
  in
    head [(a, b) | a <- relevantPrimes, b <- relevantPrimes, a + b == x]

-- PROBLEM 41

goldbachList :: Int -> Int -> [(  Int, Int)]
goldbachList l u = map goldbach $ filter even [l..u]

-- PROBLEM 42
-- PROBLEM 43
-- PROBLEM 44
-- PROBLEM 45
-- PROBLEM 46

bools :: [Bool]
bools = [False, True]

table :: (Bool -> Bool -> Bool) -> IO ()
table p = do
  putStrLn ("(False, False) --> " ++ (show $ p False False))
  putStrLn ("(False, True) --> " ++ (show $ p False True))
  putStrLn ("(True, False) --> " ++ (show $ p True False))
  putStrLn ("(True, True) --> " ++ (show $ p True True))

-- PROBLEM 47
-- PROBLEM 48

boolPerms :: Int -> [[Bool]]
boolPerms 0 = []
boolPerms 1 = [[False], [True]]
boolPerms n = [(b:bs) | b <- bools, bs <- boolPerms (n - 1)]

tablenList :: Int -> ([Bool] -> Bool) -> [([Bool], Bool)]
tablenList n p = map (\bs -> (bs, p bs)) (boolPerms n)

tablen :: Int -> ([Bool] -> Bool) -> IO ()
tablen n p =
  let
    showRow ([], res)
      = "--> " ++ show res
    showRow ((a:as), res)
      = show a ++ (if a then "  " else " ") ++ showRow (as, res)
  in do
    mapM_ (putStrLn.showRow) (tablenList n p)

-- PROBLEM 49

gray :: Int -> [String]
gray 0 = []
gray 1 = ["0", "1"]
gray n =
  let
    prev = gray (n - 1)
  in
    (map ("0"++) prev) ++ (map ("1"++) (reverse prev))

-- PROBLEM 50

insertOrderedBy :: Ord b => (a -> b) -> a -> [a] -> [a]
insertOrderedBy _ x [] = [x]
insertOrderedBy f x (y:ys)
  | f x < f y = x:y:ys
  | otherwise = y:(insertOrderedBy f x ys)

data HuffTree a = HTLeaf a Int | HTBranch Int (HuffTree a) (HuffTree a)

huffman :: Eq a => [(a, Int)] -> [(a, String)]
huffman stats = map htPath stats
  where
    sortedStats = sortOn snd stats
    sortedLeafs = map (\(x, f) -> HTLeaf x f) sortedStats
    ht          = head (getHufftree sortedLeafs)

    countOf (HTLeaf _ c)     = c
    countOf (HTBranch c _ _) = c

    getHufftree []  = error ""
    getHufftree [t] = [t]
    getHufftree (t1:t2:ts) =
      let
        newTree = HTBranch (countOf t1 + countOf t2) t1 t2
      in
        getHufftree $ insertOrderedBy countOf newTree ts

    htPath (x, _) = (x, traverseHT ht "")
      where
        traverseHT (HTLeaf y _) path
          | x == y    = path
          | otherwise = ""
        traverseHT (HTBranch _ t1 t2) path
          = (traverseHT t1 (path ++ "0")) ++ (traverseHT t2 (path ++ "1"))

-- PROBLEM 51
-- PROBLEM 52
-- PROBLEM 53
-- PROBLEM 54
-- PROBLEM 55
-- PROBLEM 56
-- PROBLEM 57
-- PROBLEM 58
-- PROBLEM 59
-- PROBLEM 60
-- PROBLEM 61
-- PROBLEM 62
-- PROBLEM 63
-- PROBLEM 64
-- PROBLEM 65
-- PROBLEM 66
-- PROBLEM 67
-- PROBLEM 68MonadIO
-- PROBLEM 69
-- PROBLEM 70
-- PROBLEM 71
-- PROBLEM 72
-- PROBLEM 73
-- PROBLEM 74
-- PROBLEM 75
-- PROBLEM 76
-- PROBLEM 77
-- PROBLEM 78
-- PROBLEM 79
-- PROBLEM 80
-- PROBLEM 81
-- PROBLEM 82
-- PROBLEM 83
-- PROBLEM 84
-- PROBLEM 85
-- PROBLEM 86
-- PROBLEM 87
-- PROBLEM 88
-- PROBLEM 89
-- PROBLEM 90
-- PROBLEM 91
-- PROBLEM 92
-- PROBLEM 93
-- PROBLEM 94
-- PROBLEM 95
-- PROBLEM 96
-- PROBLEM 97
-- PROBLEM 98
-- PROBLEM 99
