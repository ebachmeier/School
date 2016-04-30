-- ** read an email archive from standard in, extract Peer Evaluations,
-- ** and produce appropriate report(s)

import System.IO

main = do emailArchive <- hGetContents stdin
          let myReport = produceReport $ extractPeerEvaluations emailArchive
          outputReport $ formatEvaluations myReport


outputReport myReport = mapM_ (hPutStr stdout) myReport

data Evaluations = Evaluations
          { evals    :: [Evaluation]
          } deriving (Eq, Show)

data Evaluation = Evaluation
          { values    :: [EvaluationEntry]
          } deriving (Eq, Show)

data EvaluationEntry = EvaluationEntry
          { tag       :: String
          , value     :: String
          } deriving (Eq, Show)

updateEvaluation :: Evaluation -> String -> String -> Evaluation
updateEvaluation oldEvaluation tagValue valueValue =
      Evaluation
      { values = (EvaluationEntry 
                 { tag = tagValue
                 , value = valueValue
                 }) : (values oldEvaluation)
      }


formatEvaluations :: Evaluations -> [String]
formatEvaluations evaluations = formatEvaluations' (evals evaluations)
  where
    formatEvaluations' [] = []
    formatEvaluations' (anEval:restEvals) = 
                    (formatEvaluation anEval) ++ (formatEvaluations' restEvals)

formatEvaluation :: Evaluation -> [String]
formatEvaluation evaluation = formatEvaluation' (values evaluation)
   where 
     formatEvaluation' :: [EvaluationEntry] -> [String]
     formatEvaluation' [] = []
     formatEvaluation' (entry:entries) = 
             (formatEntry entry) ++ (formatEvaluation' entries)

formatEntry :: EvaluationEntry -> [String]
formatEntry anEntry = [(tag anEntry), (value anEntry), "\n"]

extractPeerEvaluations emailArchive = extractEvaluations $ 
                                      extractMessages emailArchive

produceReport peerEvaluations = peerEvaluations

extractMessages []  = []
extractMessages archive = 
     let (theMessage, rest) = extractFirstMessage archive
     in theMessage : extractMessages rest 

extractFirstMessage = extractFirstMessage' []
 where
   extractFirstMessage' readSoFar [] = (reverse readSoFar, [])
   extractFirstMessage' readSoFar ('\n':'F':'r':'o':'m':' ':rest)  = 
                                            (reverse readSoFar, "From " ++ rest)
   extractFirstMessage' readSoFar (a:rest) = 
                                    extractFirstMessage' (a:readSoFar) rest

skipTo query target = skipTo' query target []
  where
    skipTo' [] target soFar = (target, True)
    skipTo' query [] soFar = (reverse soFar, False)
    skipTo' (a:restQuery) (b:restTarget) soFar | a == b =
                skipTo' restQuery restTarget (a:soFar)
    skipTo' _ target soFar = skipTo' query oneFurther []
      where
        oneFurther = restOf $ reverse soFar ++ target
        restOf [] = []
        restOf (a:rest) = rest


testCaseEE = EvaluationEntry 
             { tag = "Hi:"
             , value = "there"
             }

testCaseE = Evaluation
            { values = [testCaseEE]
            }

testCaseEs = Evaluations
             { evals = [testCaseE]
             }

data MessageReport  = MessageReport
            { message    :: String
            , report     :: Evaluation
            } deriving (Eq, Show)
      
extractEvaluations :: [String] -> Evaluations
extractEvaluations messages = 
     Evaluations { evals = (extractEvaluations' messages) }
 where
  extractEvaluations' :: [String] -> [Evaluation]
  extractEvaluations' [] = []
  extractEvaluations' (theMessage:messages) = 
          firstMessageResult :  extractEvaluations' messages 
    where 

-- Email to: webber@csd.uwo.ca with subject line: CS3342 Peer Evaluation.
-- Send it from your uwo email account.  Do not send it as an attachment.  
-- Send it as the actual text of the email.  Note that it will be processed 
-- by a program, so don't change the form itself.  

-- ** This means that the email message will be a file that begins with
-- ** From followed by a uwo.ca email address.  It will contain a subject
-- ** line that reads: CS3342 Peer Evaluation and the remainder of the
-- ** form will be the contents of the email (not an attachment).
-- ** 
-- ** This means the tags are not moved from their original location in
-- ** the form.

-- Group Peer Evaluation Form

-- ** Header marking start of form.

-- Time period evaluated
-- STARTING

       conditionalSkipTo :: String -> MessageReport -> MessageReport
       conditionalSkipTo query messageReport = 
             if flag then messageReport { message = rest }
                     else MessageReport { message = rest
                                        , report = (updateEvaluation
                                           (report messageReport)
                                           "error=could not find "
                                           query)
                                        }
         where 
           theMessage :: String
           theMessage = message messageReport
           theReport :: Evaluation
           theReport = report messageReport
           (rest, flag) = skipTo query theMessage

       reportPastStart = conditionalSkipTo "STARTING" 
                                            MessageReport 
                                            { message = theMessage
					    , report = Evaluation { values = [] }
                                            }

--  WEEK (1 - 13):


       skipSpaces [] = []
       skipSpaces (' ':rest) = rest
       skipSpaces noFirstSpace = noFirstSpace

       extractImmediateInteger :: MessageReport -> String -> MessageReport
       extractImmediateInteger aReport tag = newReport
         where
           myMessage = (message aReport)
           value = collectDigits $ skipSpaces myMessage
           collectDigits ('0':rest) = '0': (collectDigits rest)
           collectDigits ('1':rest) = '1': (collectDigits rest)
           collectDigits ('2':rest) = '2': (collectDigits rest)
           collectDigits ('3':rest) = '3': (collectDigits rest)
           collectDigits ('4':rest) = '4': (collectDigits rest)
           collectDigits ('5':rest) = '5': (collectDigits rest)
           collectDigits ('6':rest) = '6': (collectDigits rest)
           collectDigits ('7':rest) = '7': (collectDigits rest)
           collectDigits ('8':rest) = '8': (collectDigits rest)
           collectDigits ('9':rest) = '9': (collectDigits rest)
           collectDigits noMoreDigits = []
           oldReport = report aReport
           newReport = if value == [] then MessageReport 
                                           { message = myMessage
                                           , report = 
                                              updateEvaluation oldReport "error: could not find integer for " tag 
                                           }
                                      else MessageReport
                                           { message = myMessage
                                           , report =
                                               updateEvaluation oldReport tag value
                                           }


       reportPastStartingWeek = extractImmediateInteger (conditionalSkipTo "WEEK (1 - 13):" reportPastStart) "startingweek="


       firstMessageResult :: Evaluation
       firstMessageResult = report reportPastStartingWeek


--  DAY (TU or TH):
-- ** tag with data TU or TH
-- ENDING
--  WEEK (1 - 13):
-- ** tag with data a number from 1 to 13 (actually 2 to 13 see above)
--  DAY (TU or TH):
-- ** tag with data TU or TH
-- Team Member Names
--   SELF:
-- ** tag with name data 
--   OTHER #1:
-- ** tag with name data or empty
--   OTHER #2:
-- ** tag with name data or empty
--   OTHER #3:
-- ** tag with name data or empty
--   OTHER #4:
-- ** tag with name data or empty
--   OTHER #5:
-- ** tag with name data or empty
-- Rate 5--Strongly Agree; 4--Agree; 3--Neutral; 2-- Disagree; 1--Strongly Disagre
-- (you may use 1 digit fractional values, like 3.3 -- within range 1 to 5 and
-- not more than one decimal place).
-- 
-- Contributed a fair share to the overall work of the group. (averaged over 
-- time absent and time present).
--   SELF:
-- ** tag with rating value
--   OTHER #1:
-- ** tag with rating value if this tag was given a name above
--   OTHER #2:
-- ** tag with rating value if this tag was given a name above
--   OTHER #3:
-- ** tag with rating value if this tag was given a name above
--   OTHER #4:
-- ** tag with rating value if this tag was given a name above
--   OTHER #5:
-- ** tag with rating value if this tag was given a name above
--   WORST MARK:
--   <Explanation>
-- ** text on lines between these two tags to be collected for people
-- ** who got worst mark.
--   </Explanation>
--   BEST MARK:
--   <Explanation>
-- ** text on lines between these two tags to be collected for entire
-- ** group.
--   </Explanation>
-- 
-- Worked well with other group members.
--   SELF:
-- ** tag with rating value
--   OTHER #1:
-- ** tag with rating value if this tag was given a name above
-- ...
