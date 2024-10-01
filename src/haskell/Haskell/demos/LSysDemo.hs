module LSysDemo where

  -- 78

type Rule
  = (Char, String)

type Rules
  = [Rule]

type Angle
  = Float

type Axiom
  = String

type LSystem
  = (Angle, Axiom, Rules)

type Vertex
  = (Float, Float)

type TurtleState
  = (Vertex, Float)

type Command
  = Char

type Commands
  = [Command]

type Stack
  = [TurtleState]

type Colour
  = (Float, Float, Float)

type ColouredLine
  = (Vertex, Vertex, Colour)


-- Return the binding for the given character in the list of rules
lookupChar :: Char -> Rules -> String
-- Pre: the character has a binding in the Rules list
lookupChar _ [] = ""
lookupChar c ((rchar, rstring) : rules)
  | rchar == c = rstring
  | otherwise = lookupChar c rules

-- Expand command string s once using rule table r
expandOne :: String -> Rules -> String
expandOne [] _ = ""
expandOne (c:cs) r
  = lookupChar c r ++ expandOne cs r

-- Expand command string s once using rule table r
expandOne' :: String -> Rules -> String
expandOne' cs r = concat $ map (`lookupChar` r) cs
-- concatMap




-- FLOATS IN COMPUTERS DO NOT FOLLOW SOME MATHEMATICAL PROPERTIES OF REAL NUMBERS!


degToRadProperty :: Int -> Bool
degToRadProperty deg =
  let
    fideg = fromIntegral deg
    e1    = fideg / 180 * pi
    e2    = fideg * pi / 180
    e3    = fideg * (pi / 180)
  in
    e1 == e2 && e2 == e3


sumLimit :: Float
sumLimit = 1000000

sumReciprocalIntegersLeftToRight :: Float
sumReciprocalIntegersLeftToRight = foldl1 (+) [1 / n | n <- [1..sumLimit]]

sumReciprocalIntegersRightToLeft :: Float
sumReciprocalIntegersRightToLeft = foldr1 (+) [1 / n | n <- [1..sumLimit]]


reciprocalProperty :: Float -> Float -> Bool
-- Ignoring zero-division
reciprocalProperty _ 0 = True
reciprocalProperty 0 _ = True
reciprocalProperty x y = (x / y) == 1 / (y / x)


inverseTermsCanceOutProperty :: Float -> Bool
inverseTermsCanceOutProperty 0 = True
inverseTermsCanceOutProperty x
  = x == x * x / x * x / x * x / x * x / x



-- SOME DEPENDENCIES
-- Expand command string s n times using rule table r
expand :: String -> Int -> Rules -> String
expand s 0 _ = s
expand s n r
  = expand (expandOne s r) (n-1) r

-- Move a turtle
move :: Command -> Angle -> TurtleState -> TurtleState
move 'L' a ((x,y),r) = ((x,y),r+a)
move 'R' a ((x,y),r) = ((x,y),r-a)
move 'F' _ ((x,y),r) = ((x + cos r',y + sin r'),r)
  where
    r' = degToRad r

degToRad :: Float -> Float
degToRad x = pi * (x / 180)




trace2 :: Commands -> Angle -> Colour -> [ColouredLine]
trace2 cs a l
  = runTurtle2 cs a l [((0,0),90)]

trace2' :: Commands -> Angle -> Colour -> [ColouredLine]
trace2' cs a l
  = runTurtle2' cs a l [((0,0),90)]



-- Original
runTurtle2 :: Commands -> Angle -> Colour -> [TurtleState] -> [ColouredLine]
runTurtle2 [] _ _ _ = []

runTurtle2 (']':cs) a l (t:ts)
  = runTurtle2 cs a l ts

runTurtle2 ('[':cs) a l (t:ts)
  = runTurtle2 cs a l (t:t:ts)

runTurtle2 ('F':cs) a l (t@((x,y),_):ts)
  = ((x,y),(x',y'),l) : runTurtle2 cs a l (t':ts)
  where
    t'@((x',y'),_) = move 'F' 0 t

runTurtle2 (c:cs) a l (t:ts)
  = runTurtle2 cs a l (move c a t :ts)




runTurtle2' :: Commands -> Angle -> Colour -> [TurtleState] -> [ColouredLine]
runTurtle2' [] _ _ _ = []
runTurtle2' (c:cs) a l (t@((x,y),_):ts)
  = extraLine ++ (runTurtle2' cs a l updatedStack)
    where
      t'@((x',y'),_)= move 'F' 0 t
      (extraLine, updatedStack) = case c of
          'F' -> ([((x, y),(x',y'),l)], t':ts)
          ']' -> ([], ts)
          '[' -> ([], t:t:ts)
          c   -> ([], move c a t :ts)



-- quickCheck (withMaxSuccess 100000 runTurtleVariantsSame)
runTurtleVariantsSame :: Commands -> Angle -> Colour -> Bool
runTurtleVariantsSame a b c
  = not (all (`elem` "FLR[]") a) || trace2 a b c == trace2' a b c





-- Define isPalindrome function, which returns True if a given string
-- reads the same backwards and forwards.
-- isPalindrome :: String -> Bool
-- or
-- isPalindrome :: (Eq a) => [a] -> Bool



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



coolerIsPalindrome :: (Eq a) => [a] -> Bool
coolerIsPalindrome xs = xs == reverse xs


isPalindromeFuncsAreEquivalent xs = isPalindrome xs == coolerIsPalindrome xs




-- Given a data of nested list write a function flatten :: NestedList a -> [a]
-- which return a list of all elements of a nested list without nesting
data NestedList a = Elem a | List [NestedList a]



flatten :: NestedList a -> [a]
flatten (Elem x)        = [x]
flatten (List [])       = []
flatten (List (e : es)) = (flatten e) ++ (flatten (List es))
