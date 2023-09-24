module Challenge1 where

-- TODO -> decrypt the substitute-cipher message and eigher provide mapping or the original text

-- No need to proide end-to-end high quality scalable program. You may use GHCI
-- function calls  as "queries" and get partial information and then hard coding
-- the partial sollution. Sacrificing code quality to get performance or sollution
-- some times is an option ;)

-- GLHF!

alphabet = "abcdefghijklmnopqrstuvwxyz"

ciphertext = concat [ "\nhrv hgvsvm vmt fnhxsofmtvm\n"
                    , "\nvrm uovrhxstvnrhxs hl ivrxs zm gztvm\n"
                    , "\ndl wzh nvvi wzh ozmw yvifsig\n"
                    , "\ndroo hrv rsn wrv dzsisvrg hztvm\n"
                    , "\nwlxs rsiv dligv uirhhg wvi drmw\n"
                    , "\ndl wzh nvvi af vmwv rhg\n"
                    , "\nszog hrv arggvimw hvrmv szmw\n"
                    , "\nfmw szg rsm zfu wrv hgrim tvkfhhg\n"
                    , "\nhrv giztg wvm zyvmw rm wvi yifhg\n"
                    , "\nfmw dvrhh wzhh hrv eviovyvm nfhh\n"
                    , "\nhrv ovtg wvm klqu rm hvrmvm hxslhh\n"
                    , "\nfmw yrggvg vrmvm ovgagvm kfhh\n"
                    , "\nfmw wzmm szg vi hrv tvkfhhg\n"
                    , "\ndl wzh nvvi af vmwv rhg\n"
                    , "\nrsiv orqqvm hxsdzxs fmw yoz\n"
                    , "\nfmw hvrmv zftvm dviwvm mz\n"
                    , "\nwvi ovgagv kfhh rhg hl ozmt svi\n"
                    , "\nwvi ovgagv kfhh\n"
                    , "\nvi virmmvig hrxs mrxsg nvsi\n"
                    ]

popularGermanWords :: [String]
popularGermanWords
  = [ "aber", "all", "als", "also", "an", "andere,", "auch", "auf", "aus", "bei"
    , "beispiel,", "bis", "da", "damit", "dann", "das", "dass", "denn", "der"
    , "die", "dies-", "doch", "du", "durch", "eigentlich", "ein", "er", "erste,"
    , "es", "fur", "ganz", "geben", "gehen", "gut", "haben", "hier", "ich"
    , "ihm", "ihn", "ihr", "immer", "in", "ja", "jahr", "jed-", "jetzt", "kein", "kommen"
    , "konnen", "lang", "lassen", "machen", "mal", "man", "mehr", "mein", "mich", "mir"
    , "mit", "mussen", "nach", "neu", "nicht", "noch", "nur", "oben", "oder", "sagen"
    , "schon", "sehen", "sehr", "sein", "sein", "selbst,", "sich", "sie", "so", "sollen"
    , "stehen", "um", "und", "uns", "unser", "unter", "viel", "von", "vor", "was"
    , "weil", "wenn", "werden", "wie", "wieder", "wir", "wissen", "wo", "wollen"
    , "zeit,", "zu", "zwei", "uber"]


-- You may want to use this. Delete if don't.

-- data BST = Tip | Node String BST BST
--
-- bstFromList :: [String] -> BST
-- bstFromList = undefined
--
-- bstContains :: BST -> String -> Bool
-- bstContains = undefined



-- and/or this

-- type Mapping = [(Char, Maybe Char)]
--
-- emptyMapping :: Mapping
-- emptyMapping = map (\c -> (c, Nothing)) alphabet
--
-- updateMapping :: Mapping -> Char -> Char -> Mapping
-- updateMapping = undefined
--
-- mappingFind :: Mapping -> Char -> Maybe Char
-- mappingFind = undefined
