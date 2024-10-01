module CryptoDemo where


-- Calculates (u, v, d) the gcd (d) and Bezout coefficients (u and v)
-- such that au + bv = d
computeCoeffs :: Int -> Int -> (Int, Int)
computeCoeffs a 0 = (1, 0)
computeCoeffs a b
  = (coef2, coef1 - q * coef2)
  where
    (coef1, coef2) = computeCoeffs b r
    (q, r) = quotRem a b



-- The above function uses fst and snd instead of pattern mathing over pairs.
-- Could also use quotRem instead of div and mod



-- Returns the smallest integer that is coprime with phi
smallestCoPrimeOf :: Int -> Int
smallestCoPrimeOf num = head [x | x <- [2..], gcd num x == 1]






-- The above function can remove the upper limit in a sequnce and hence remove
-- the first two cases. There's also a minor issue with double negation





-- -----------------------------------------------------------------------------



-- Inverse of a modulo m
inverse :: Int -> Int -> Int
inverse a m = u `mod` m
  where
    (u,_) = computeCoeffs a m



-- DONTCARES demo. Run with n = 33xx

slowFib :: Integer -> Integer
slowFib 0 = 0
slowFib 1 = 1
slowFib n = slowFib (n - 1) + slowFib (n - 2)


slowPair :: Integer -> (Integer, Integer)
slowPair n = (n, slowFib n)



useFirstOnly :: Integer -> Integer
useFirstOnly n =
  let
    (x, _) = slowPair n
  in
    x


useSecondOnly :: Integer -> Integer
useSecondOnly n =
  let
    (_, y) = slowPair n
  in
    y


useFirstOnly' :: Integer -> Integer
useFirstOnly' n =
  let
    (x, y) = slowPair n
  in
    x


useSecondOnly' :: Integer -> Integer
useSecondOnly' n =
  let
    (x, y) = slowPair n
  in
    y


-- Calculates (a^k mod m)
modPow :: Int -> Int -> Int -> Int
modPow a k m
  | k == 0    = 1 `mod` m
  | even k    = recur
  | otherwise = a * recur `mod` m
    where
      recur = modPow ((a * a) `mod` m) (k `div` 2) m



-- The redndant bit is in (k - 1) instead of just k. But after that you spot duplication
-- which can be further eliminated.




alphabetSize :: Int
alphabetSize = 26



-- You may saw in the lectures
even' :: Int -> Bool
even' 0 = True
even' 1 = False
even' n = even' (n - 2)
-- even' x = x `mod` 2 == 0

modPow' a k 1 = 0
modPow' a 0 m = 1
modPow' a k m
  | even k   = recur
  | otherwise = (recur * a) `mod` m
    where
      recur = modPow' (a ^ 2 `mod` m) (k `div` 2) m
