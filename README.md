# PA2-FIT
My solutions to the home works in Programming and algorithms 2 course at FIT CTU. The course focused on objected oriented programming and abstract data types with the use of C++.

## Progtest 1 - Huffman code
The task was to create a set of functions that can (de)compress Huffman code as an input.

## Progtest 2 - Tax Register
The task was to create the `CTaxRegister` class, that has this interface:
- constructor/destructor
- `Birth(Name, Addr, Acc)` method - adds new record to the database
- `Death (Name, Addr)` method - removes record from database
- `Income` method - adds a record of income to the account of citizen
- `Expense` method - adds a record of expense to the account of citizen
- `Audit` method - finds all information about the citizen
- `ListByName` method - returds an instance of `CIterator` class

## Progtest 3 - Big Integers
The task was to create the `CBigInt` class that can represent integers in a (very) big range. The task was focused on implementing overloaded operators

## Progtest 4 - e-Banking
The task was to create `CBank` class which implements internet banking. It has the following interface:
- implicit constructor/copying constructor/destructor
- = operator - makes a deep copy of an instance
- `NewAccount(accId,initBalance)` - adds a new account
- `Transaction(debitAcc,creditAcc,amount,sign)` - creates a transaction between 2 accounts
## Progtest 5 - Mail box
The task was to create `CMailBox` and `CMail` classes to simulate a mailbox on a mail server.
## Semestral work - Utility for quiz making
The program allows for creation and filling of the created quizes in a terminal environment. It implements 3 different types of questions:
- Exact word: the answer has to be the same as when creating the quiz
- Multiple choice: user chooses between 3 different possible answers
- Sequence: User needs to put the answer in correct sequence
