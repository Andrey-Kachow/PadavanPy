import Control.Applicative
import Data.Maybe
import Control.Monad

data MMaybe a = MJust a | MNothing
    deriving Show


-- f s = length s
-- f (MJust "hello") = MJust 5
-- f MNothing -> MNothing

instance Functor MMaybe where
    fmap :: (a -> b) -> MMaybe a -> MMaybe b
    fmap f (MJust x) = MJust (f x)
    fmap _ MNothing  = MNothing

-- fun = MJust length
-- fun1 = MNothing

-- apply fun  on MJust "hello" = MJust 5
-- apply fun1 on MJust "hello" = Nothing
-- apply fun  on MNothing      = MNothing
-- apply fun1 on MNothing      = MNothing

apply :: MMaybe (a -> b) -> MMaybe a -> MMaybe b
apply (MJust f) x = fmap f x
apply MNothing _  = MNothing


li :: MList String
li = MCons "hi" (MCons "world" (MCons "Goodbye" MEmpty))

data MList a = MEmpty | MCons a (MList a)
    deriving Show

instance Functor MList where
  fmap :: (a -> b) -> MList a -> MList b
  fmap _ MEmpty       = MEmpty
  fmap f (MCons a xs) = MCons (f a) (fmap f xs)

-- apply []     []  = []
-- apply []     [1] = []
-- apply [(+2)] []  = []

-- apply [(+2)] [1] = [3]
-- apply [(+2)] [1, 3] = [3, 5]

-- apply [(+2), (*10)] [1] = [3, 10]

-- apply [(+2), (*10)] [1, 3] = [3, 5, 10, 30]

applyL :: [a -> b] -> [a] -> [b]
applyL (f:fs) xs = map f xs ++ applyL fs xs
applyL _ _       = []

instance Applicative MMaybe where
  pure :: a -> MMaybe a
  pure x = MJust x
  (<*>) :: MMaybe (a -> b) -> MMaybe a -> MMaybe b
  (<*>) = apply


maybeLength :: String -> MMaybe Int
maybeLength ('h':_) = MNothing
maybeLength xs      = MJust (length xs)

divTwo :: Int -> MMaybe Int
divTwo x
    | even x    = MJust (x `div` 2)
    | otherwise = MNothing

-- MNothing (MJust a)
-- MNothing (Mnothing)
-- Mjust (Mnothing)
-- Mjust (Mjust a) = Mjust a
peel :: MMaybe (MMaybe a) -> MMaybe a
peel (MJust (MJust x)) = MJust x
peel _                 = MNothing

-- peel (fmap divTwo (divTwo 7))

-- autoPeel maybeLength divTwo x = peel (fmap divTwo (maybeLength x))

autoPeel :: (a -> MMaybe b) -> MMaybe a -> MMaybe b
autoPeel f x = peel (fmap f x)

-- FUNCTOR:             (a -> b) -> MMaybe a -> MMaybe b
-- APPLICATIVE:  MMaybe (a -> b) -> MMaybe a -> MMaybe b
-- MONAD         (a -> MMaybe b) -> MMaybe a -> MMaybe b

maybeLength' :: String -> Maybe Int
maybeLength' ('h':_) = Nothing
maybeLength' xs      = Just (length xs)

divTwo' :: Int -> Maybe Int
divTwo' x
    | even x    = Just (x `div` 2)
    | otherwise = Nothing

demo :: String -> Maybe Int
demo x = do
    length <- maybeLength' x
    half <- divTwo' length
    return half
