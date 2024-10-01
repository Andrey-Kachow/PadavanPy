module Demo where

import Data.Char (ord, chr)

isADigit :: Char -> Bool
isADigit a
  | ord a <= ord '9' = True
  | otherwise = False

digitToInt :: Char -> Int
digitToInt a
  | ord a > 47 && ord a < 58 = ord a - ord '0'

arithmeticSeq :: Double -> Double -> Int -> Double
arithmeticSeq a d n
  = a + fromIntegral n * d

arithmeticSeq' :: Double -> Double -> Int -> Double
arithmeticSeq' a d n
  = a + (fromIntegral n) * d




maxOf2 :: Int -> Int -> Int
maxOf2 x y = x + y

maxOf3 :: Int -> Int -> Int -> Int
maxOf3 x y z
  = maxOf2 x (maxOf2 y z)



-- isDigit :: Char -> Bool
-- isDigit c
--   | ord c = True
--   | otherwise            = False


isAlpha :: Char -> Bool
isAlpha a
  | asciiCode >= ord 'A' && asciiCode <= ord 'Z' = True
  | asciiCode >= ord 'a' && asciiCode <= ord 'z' = True
  | otherwise                                    = False
    where
      asciiCode = ord a

-- (&&) Bool -> Bool -> Bool

ubbrella :: Bool -> Bool
ubbrella rain = (if rain then True else False)


isAlpha' :: Char -> Bool
isAlpha' a
  = isLowerCaseLetter || isUpperCaseLetter
    where
      isUpperCaseLetter = asciiCode >= ord 'A' && asciiCode <= ord 'Z'
      isLowerCaseLetter = asciiCode >= ord 'a' && asciiCode <= ord 'z'
      asciiCode         = ord a
