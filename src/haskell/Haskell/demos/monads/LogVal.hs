module LogVal where

import Control.Applicative
import Control.Monad

-- Program with output string messages
data LogProg a = Fail [String] | OK a [String] deriving Show

logsOf :: LogProg a -> [String]
logsOf (Fail ls) = ls
logsOf (OK _ ls) = ls

logged :: (a -> b) -> String -> LogProg (a -> b)
logged f msg = OK f [msg]

instance Functor LogProg where
  -- fmap :: (a -> b) -> LogProg a -> LogProg b
  fmap _ (Fail ls) = Fail ls
  fmap f (OK x ls) = OK (f x) ls


apply :: LogProg (a -> b) -> LogProg a -> LogProg b
apply _ (Fail ls)           = Fail ls
apply application (OK x ls) =
  let
    ls' = logsOf application ++ ls
  in
    case application of
      Fail _ -> Fail ls'
      OK f _ -> OK (f x) ls'


instance Applicative LogProg where
  -- pure :: a -> LogProg a
  pure x = OK x []

  (<*>) = apply


peel :: LogProg (LogProg a) -> LogProg a
peel (Fail ls) = Fail ls
peel (OK inner ls') = case inner of
  OK res ls -> OK res (ls ++ ls')
  Fail ls   -> Fail ls

autoPeel :: (a -> LogProg b) -> LogProg a -> LogProg b
autoPeel f x = peel (fmap f x)


instance Monad LogProg where

  (>>=) (Fail ls) _ = Fail ls
  (>>=) (OK x ls) f =
    let
      my = f x
    in
      case my of
        Fail ls' -> Fail (ls ++ ls')
        OK y ls' -> OK y (ls ++ ls')

  (>>) prev (OK x ls) = OK x (logsOf prev ++ ls)
  (>>) prev (Fail ls) = Fail (logsOf prev ++ ls)

  return x = OK x []


loggedSucc :: LogProg (Int -> Int)
loggedSucc = logged succ "Applied succ to value"

applyLoggedSucc :: Int -> LogProg Int
applyLoggedSucc x = (apply loggedSucc) (pure x)

applyPureFun :: (a -> b) -> a -> LogProg b
applyPureFun f x = (apply (pure f)) (pure x)

applyLoggedFun :: String -> (a -> b) -> a -> LogProg b
applyLoggedFun msg f x = (apply (logged f msg)) (pure x)

-- Imperative Programs

applySuccThreeTimes :: Int -> LogProg Int
applySuccThreeTimes initial
  = pure initial    >>=
    applyLoggedSucc >>=
    applyLoggedSucc >>=
    applyLoggedSucc

sexyDoApplySuccThreeTimes :: Int -> LogProg Int
sexyDoApplySuccThreeTimes x = do
  y <- applyLoggedSucc x
  z <- applyLoggedSucc y
  w <- applyLoggedSucc z
  return w


getFizzBuzz :: Int -> Int -> Int -> String
getFizzBuzz x f b
  | x `mod` f == 0 && x `mod` b == 0 = "Fizz Buzz"
  | x `mod` f == 0                   = "Fizz"
  | x `mod` b == 0                   = "Buzz"
  | otherwise                        = show x

fizzBuzz :: (Int, Int) -> [Int] -> LogProg [Int]
fizzBuzz _ [] = return []
fizzBuzz (f, b) (x : xs) = do
  let fb = getFizzBuzz x f b
  x' <- applyLoggedFun fb id x
  xs' <- fizzBuzz (f, b) xs
  return (x':xs')
