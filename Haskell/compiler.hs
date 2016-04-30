import System.IO

-- compiler for language with the following syntax:
-- note: all variables must be defined at first usage, i.e., they must
--       appear on the rhs of a statement before appearing on the lhs.
--       there are no continuations, but recursion is allowed.

-- PROGRAM = { STMT }
-- STMT = ID '=' EXPR
-- STMT = ID '=' LAMBDA
-- LAMBDA = \ { ID } '(' EXPR ')'
-- EXPR = ? EXPR : EXPR : EXPR
-- EXPR = + EXPR EXPR
-- EXPR = - EXPR EXPR
-- EXPR = * EXPR EXPR
-- EXPR = ID '(' {EXPR} ')'
-- EXPR = ID
-- EXPR = DIGITS
-- DIGITS = DIGIT { DIGIT }
-- DIGIT = 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
-- ID = NONDIGIT { NONDIGIT | DIGIT }
-- spaces terminate DIGITS or ID as do punctuation \ = + - * ( ) ? :

main = do inputString <- hGetContents stdin
          let tokens = tokenize inputString
          writeTokenize stdout tokens
          let parseTree = parse tokens
          let theRTL = compile parseTree
          writeRTL stdout theRTL

data ParseTree = ParseTree { root :: String
                           , children :: [ParseTree]
                           } deriving (Eq, Show)

type RTL = [RT]
data RT = RT { operation :: String
             , target :: Int
             , source ::  Int
             } deriving (Eq, Show)
-- op t s
-- MOV, M[t] <- M[s]
-- LOAD, M[t] <- M[M[s]]
-- STORE, M[M[t]] <= M[s]
-- CONST, M[t] <- s
-- JMPZ, if M[s] == 0 then PC <- t
-- JMPNZ, if M[s] != 0 then PC <- t
-- JMP, PC <- t
-- ADD, M[t] <- M[t] + M[s]
-- ADDC, M[t] <- M[t] + s
-- SUB, M[t] <- M[t] - M[s]
-- SUBC, M[t] <- M[t] - s
-- MULT, M[t] <- M[t] * M[s]
-- MULTC, M[t] <- M[t] * s
-- DIV, M[t] <- M[t] / M[s]
-- DIVC, M[t] <- M[t] / s
-- CALL, M[t] <- PC, PC <- M[s]
-- HALT

tokenize :: String -> [String]
tokenize inputString = tokenize' inputString []
--       tokenize' charsToProcess wordSoFar
   where tokenize' [] [] = []
         tokenize' [] wordSoFar = [wordSoFar]
         tokenize' (' ':rest) [] = tokenize' rest []
         tokenize' (' ':rest) wordSoFar = [wordSoFar] ++  (tokenize' rest [])
         tokenize' (ch:rest) wordSoFar = tokenize' rest (wordSoFar ++ [ch])
parse :: [String] -> ParseTree
parse tokens = ParseTree { root = "test parsing"
                         , children = []
                         } 

compile :: ParseTree -> RTL 
compile parseTree = [ RT { operation = "Test some more"
                         , source = 0
                         , target = 1
                         }
                    ]

writeRTL :: Handle -> RTL -> IO ()
writeRTL handle rtl = do if rtl == [] then return ()
                                      else do writeRT handle $ head rtl
                                              writeRTL handle $ tail rtl

writeRT :: Handle -> RT -> IO ()
writeRT handle rt = do hPutStr handle $ (operation rt) ++ " "
                       hPutStr handle $ (show $ target rt) ++ " "
                       hPutStr handle $ (show $ source rt) ++ "\n"

writeTokenize :: Handle -> [String] -> IO ()
writeTokenize handle tokens = do if tokens == [] then return ()
                                 else do hPutStr handle $ (head tokens) ++ "\n"
                                         writeTokenize handle $ tail tokens
