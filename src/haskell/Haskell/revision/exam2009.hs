import Data.List
import Data.Maybe

type Index = Int

data BExp = Prim Bool | IdRef Index | Not BExp | And BExp BExp | Or BExp BExp
            deriving (Eq, Ord, Show)

type Env = [(Index, Bool)]

type NodeId = Int

type BDDNode =  (NodeId, (Index, NodeId, NodeId))

type BDD = (NodeId, [BDDNode])

------------------------------------------------------
-- PART I

-- Pre: The item is in the given table
lookUp :: Eq a => a -> [(a, b)] -> b
lookUp x xs
  = fromJust (lookup x xs)

checkSat :: BDD -> Env -> Bool
checkSat (0, _) _ = False
checkSat (1, _) _ = True
checkSat (bid, ns) env =
  let
    (i, l, r) = lookUp bid ns
  in
    if lookUp i env
      then
        checkSat (r, ns) env
      else
        checkSat (l, ns) env


sat :: BDD -> [[(Index, Bool)]]
sat bdd = satAux bdd []
  where
    satAux (0, _) _      = []
    satAux (1, _) env    = [env]
    satAux (bid, ns) env =
      let
        (i, l, r) = lookUp bid ns
        leftSats  = satAux (l, ns) ((i, False) : env)
        rightSats = satAux (r, ns) ((i, True) : env)
      in
        leftSats ++ rightSats

------------------------------------------------------
-- PART II

simplify :: BExp -> BExp
simplify (Not (Prim x))
  = Prim (not x)
simplify (Or (Prim x) (Prim y))
  = Prim (x || y)
simplify (And (Prim x) (Prim y))
  = Prim (x && y)
simplify exp
  = exp

restrict :: BExp -> Index -> Bool -> BExp
restrict (Prim b) _ _ = (Prim b)
restrict (IdRef var) identifier b
  | var == identifier = Prim b
  | otherwise         = IdRef var
restrict bexp i b = simplify (restrict' bexp)
  where
    restrict' (And b1 b2) = And (restrict b1 i b) (restrict b2 i b)
    restrict' (Or b1 b2)  = Or (restrict b1 i b) (restrict b2 i b)
    restrict' (Not bexp)  = Not (restrict bexp i b)

------------------------------------------------------
-- PART III

-- Pre: Each variable index in the BExp appears exactly once
--     in the Index list; there are no other elements
-- The question suggests the following definition (in terms of buildBDD')
-- but you are free to implement the function differently if you wish.
buildBDD :: BExp -> [Index] -> BDD
buildBDD e xs
  = buildBDD' e 2 xs

buildBDD' :: BExp -> NodeId -> [Index] -> BDD
buildBDD' (Prim b) _ [] =
    let
      boolInt = if b then 1 else 0
    in
      (boolInt, [])
buildBDD' e rid (i:is) =
  let
    rexp = restrict e rid True
    lexp = restrict e rid False
    (_, rns) = buildBDD' rexp i is
    (_, lns) = buildBDD' lexp i is
  in
    (rid, rns ++ lns)

------------------------------------------------------
-- PART IV

-- Pre: Each variable index in the BExp appears exactly once
--      in the Index list; there are no other elements
buildROBDD :: BExp -> [Index] -> BDD
buildROBDD
  = undefined


-- This function removes some extra nodes that are unreachable (don't ask me
-- how they are in there, but sometimes they are)
curate :: [BDDNode] -> [BDDNode]
curate = undefined

root :: (Int, Int, Int) -> Int
root (x, _, _) = x
------------------------------------------------------
-- Examples for testing...

b1, b2, b3, b4, b5, b6, b7, b8 :: BExp
b1 = Prim False
b2 = Not (And (IdRef 1) (Or (Prim False) (IdRef 2)))
b3 = And (IdRef 1) (Prim True)
b4 = And (IdRef 7) (Or (IdRef 2) (Not (IdRef 3)))
b5 = Not (And (IdRef 7) (Or (IdRef 2) (Not (IdRef 3))))
b6 = Or (And (IdRef 1) (IdRef 2)) (And (IdRef 3) (IdRef 4))
b7 = Or (Not (IdRef 3)) (Or (IdRef 2) (Not (IdRef 9)))
b8 = Or (IdRef 1) (Not (IdRef 1))

bdd1, bdd2, bdd3, bdd4, bdd5, bdd6, bdd7, bdd8 :: BDD
bdd1 = (0,[])
bdd2 = (2,[(4,(2,1,1)),(5,(2,1,0)),(2,(1,4,5))])
bdd3 = (5,[(5,(1,0,1))])
bdd4 = (2,[(2,(2,4,5)),(4,(3,8,9)),(8,(7,0,1)),(9,(7,0,0)),
           (5,(3,10,11)),(10,(7,0,1)),(11,(7,0,1))])
bdd5 = (3,[(4,(3,8,9)),(3,(2,4,5)),(8,(7,1,0)),(9,(7,1,1)),
           (5,(3,10,11)),(10,(7,1,0)),(11,(7,1,0))])
bdd6 = (2,[(2,(1,4,5)),(4,(2,8,9)),(8,(3,16,17)),(16,(4,0,0)),
           (17,(4,0,1)),(9,(3,18,19)),(18,(4,0,0)),(19,(4,0,1)),
           (5,(2,10,11)),(10,(3,20,21)),(20,(4,0,0)),(21,(4,0,1)),
           (11,(3,22,23)),(22,(4,1,1)),(23,(4,1,1))])
bdd7 = (6,[(6,(2,4,5)),(4,(3,8,9)),(8,(9,1,1)),(9,(9,1,0)),
           (5,(3,10,11)),(10,(9,1,1)),(11,(9,1,1))])
bdd8 = (2,[(2,(1,1,1))])
