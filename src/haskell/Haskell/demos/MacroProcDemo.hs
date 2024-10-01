module MacroProcDemo where

import Data.Maybe
import Test.QuickCheck

type Keyword      = String
type KeywordValue = String
type KeywordDefs  = [(Keyword, KeywordValue)]




lookUp :: String -> [(String, a)] -> [a]
lookUp search itemPairs
  = [number | (letter,number) <- itemPairs, letter == search]




funLookUp :: String -> [(String, a)] -> [a]
funLookUp search itemPairs
  = map snd $ filter ((search==).fst) itemPairs



lambdaFunLookUp :: String -> [(String, a)] -> [a]
lambdaFunLookUp search itemPairs
  = map snd $ filter whatever itemPairs
    where
      whatever (k, v) = k == search





combine :: String -> [String] -> [String]
combine _ [w] = [w]
combine (s:ss) (w:ws)
  = w : [s] : combine ss ws





-- Function combine with safer case coverage

combine' :: String -> [String] -> [String]
-- combine' _ []     = error "ep"
combine' [] (w:_) = [w]
combine' (s:ss) (w:ws)
  = w : [s] : combine ss ws



-- You may wish to uncomment and implement this helper function
-- when implementing expand
replaceWord_ :: String -> KeywordDefs -> String
replaceWord_ "" keywordDefs = ""
replaceWord_ word keywordDefs
  | lu == []  = word
  | otherwise = head lu
    where
      lu = lookUp word keywordDefs





replaceWord'' :: String -> KeywordDefs -> String
replaceWord'' kw kwdefs = matchLookupCaseOf (lookUp kw kwdefs)
  where
    matchLookupCaseOf []    = kw
    matchLookupCaseOf (r:_) = r







-- You can pattern match over any expression you like with case...of expression
-- Not just function arguments



replaceWord :: String -> KeywordDefs -> String
replaceWord kw kwdefs = case lookUp kw kwdefs of
  []    -> kw
  (r:_) -> r


replaceWord' :: String -> KeywordDefs -> String
replaceWord' kw kwdefs = case lookup kw kwdefs of
  Nothing  -> kw
  Just def -> def


-- Speaking of Maybe data type we can safely unpack it by providing default value

-- import Data.Maybe

replaceWord''' :: String -> KeywordDefs -> String
replaceWord''' kw kwdefs = fromMaybe kw (lookup kw kwdefs)











-- Why !! bad. Very Slow


succElem :: [Int] -> Int -> Int
succElem xs i = succ (xs !! i)


succElems :: [Int] -> [Int]
succElems xs = [succElem xs i | i <- [0..((length xs) - 1)]]

succElems' :: [Int] -> [Int]
succElems' xs = map succ xs


printSuccs xs = do
  (putStrLn.show) (sum $ succElems' xs)
  (putStrLn.show) (sum $ succElems xs)







splitText :: [Char] -> String -> (String, [String])
splitText listSep [] = ("",[""])
splitText listSep (x:xs) = if x `elem` listSep then (x:sep,([""]++(word:[])++words)) --add my word to the list and update sep
                                               else (sep,(x:word):words) --adding new char to word
  where (sep,word:words) = splitText listSep xs



getKeywordDefs :: [String] -> KeywordDefs
getKeywordDefs [] = []
getKeywordDefs (k:ks) = if keyword == "" then getKeywordDefs keywords
                                         else [(first, concat (combine seps rest))] ++ (getKeywordDefs keywords)
  where ((sep:seps),(first:rest)) = splitText " " keyword

   --using " " instead of (seperators) will help us reduce number of computations
   --because it is known that the keyword is seperated from the rest using " "
   --and splitting based on other separators is useless



   --
   --
   --
   -- -- WARNING (!!) BAD!
   --
   -- mI :: [[Int]]
   -- mI = [ [1, 0, 0]
   -- , [0, 1, 0]
   -- , [0, 0, 1]
   -- ]
   --
   --
   -- mt1 :: [[Int]]
   -- mt1 = [ [1, 2, 3]
   -- , [2, 1, 4]
   -- , [4, 0, 1]
   -- ]
   --
   -- mt2 :: [[Int]]
   -- mt2 = [ [7, 5, 3]
   -- , [2, 0, 2]
   -- , [4, 1, 0]
   -- ]
   --
   --
   -- -- test answer
   -- mt3 :: [[Int]]
   -- mt3 = [ [23,  8,  7]
   -- , [32, 14,  8]
   -- , [32, 21, 12]
   -- ]
   --
   --
   --
   --
   -- matrixMul :: [[Int]] -> [[Int]] -> [[Int]]
   -- matrixMul m1 m2
   -- = [
   -- [
   -- sum [ (row !! k) * (col !! k)
   -- | k <- ks
   -- , let row = getRow i m1
   -- , let col = getCol j m2
   -- ]
   -- | j <- js
   -- ]
   -- | i <- is
   -- ]
   -- where
   --   width    = length $ head m2
   --   height   = length m1
   --   interior = length m2
   --
   --   getCol x m = map (!!x) m
   --   getRow y m = m !! y
   --
   --   is = [0..(height - 1)]
   --   js = [0..(width - 1)]
   --   ks = [0..(interior - 1)]
   --
   --   -- quickCheck (withMaxSuccess 10000 matAssocProperty)
   --
   --
   --
   --
   --   matFromSeq :: Int -> Int -> [Int] -> [[Int]]
   --   matFromSeq n m l  = buildMat s
   --   where
   --     s = take (n * m) $ (concat.repeat) l
   --
   --     buildMat [] = []
   --     buildMat xs = us : (buildMat vs)
   --     where
   --       (us, vs) = splitAt m xs
   --
   --
   --       matAssocProperty :: Int -> [Int] -> [Int] -> [Int] -> Bool
   --       matAssocProperty 0 _ _ _  = True
   --       matAssocProperty 1 _ _ _  = True
   --       matAssocProperty _ [] _ _ = True
   --       matAssocProperty _ _ [] _ = True
   --       matAssocProperty _ _ _ [] = True
   --       matAssocProperty _ [x] _ _ = True
   --       matAssocProperty _ _ [x] _ = True
   --       matAssocProperty _ _ _ [x] = True
   --       matAssocProperty dim s1 s2 s3
   --       = matrixMul (matrixMul a b) c == matrixMul a (matrixMul b c)
   --       where
   --         a = matFromSeq dim dim s1
   --         b = matFromSeq dim dim s2
   --         c = matFromSeq dim dim s3
