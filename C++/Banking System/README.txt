CS3307 Assignment 1 - Banking System

By: Eric Bachmeier ebachme@uwo.ca

To compile and run:
    $ make all
    $ ./bank

The format of the text file information is as follows:

clientDB.txt
    [ID] [Chequing Balance] [Savings Balance] [First] [Last] [PIN] [Account Status] [Credit Limit] [Payment Plan] [Debt Owing]

clientTransaction.txt
    [ID] [Purchase] [Purchase] ... [Purchase]

bankData.txt
    Maintenance [Maintenance ID]
    Manager [Manager ID]
    EndOfMonth [Days Remaining]

failedTransaction.txt
    [ID] [Failed Amount]

purchaseLog.txt
    [ID] [Purchase Amount]