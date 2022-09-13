#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <cctype>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;
#endif /* __PROGTEST__ */
class CTransaction{
public:
    CTransaction() { from = nullptr; to = nullptr; sign = nullptr; sum = 0;}
    char* from;
    char* to;
    unsigned sum;
    char* sign;
};

class CAccount{
public:
    CAccount();
    friend ostream& operator<<(ostream& os, const CAccount& a);
    int Balance() { return balance; }

//private:
    char* accID;
    int init;
    int balance;
    CTransaction* tran;
    unsigned trCap;
    unsigned trNum;
};
void myTrRealloc(CAccount &x);

CAccount::CAccount() {
    tran = new CTransaction[10];
    accID = nullptr;
    init = 0;
    balance = 0;
    trCap = 10;
    trNum = 0;
}

ostream &operator<<(ostream &os, const CAccount &a) {
    os << a.accID << ":" << endl << "   " << a.init << endl;

    // Check if the transaction is incoming or departing
    for (unsigned i = 0; i < a.trNum; ++i) {
        if (a.tran[i].from == nullptr)
            os << " - " << a.tran[i].sum << ", to: " << a.tran[i].to << ", sign: " << a.tran[i].sign << endl;

        else if (a.tran[i].to == nullptr)
            os << " + " << a.tran[i].sum << ", from: " << a.tran[i].from << ", sign: " << a.tran[i].sign << endl;
    }

    os << " = " << a.balance << endl;
    return os;
}

class CBank
{
public:
    CBank() { acc = new CAccount[10]; accCap = 10; accNum = 0;}
    CBank( const CBank &x);
    ~CBank();
    CBank&operator=(const CBank &x);

    bool   NewAccount    ( const char * accID,
                           int          initialBalance );
    bool   Transaction   ( const char * debAccID,
                           const char * credAccID,
                           unsigned int amount,
                           const char * signature );
    bool   TrimAccount   ( const char * accID );
    CAccount Account ( const char* accID );
private:
    CAccount* acc;
    unsigned accCap; // number of allocated accounts;
    unsigned accNum; //number of used accounts;
};

bool CBank::NewAccount(const char *accID, int initialBalance) {
    //Reallocation of accounts
    if (accCap == accNum) {

        CAccount* tmp = new CAccount[accCap*2];

        for (unsigned i = 0; i < accCap; ++i) {
            tmp[i].balance = acc[i].balance;
            tmp[i].init  = acc[i].init;
            delete[] tmp[i].tran;
            tmp[i].tran  = acc[i].tran;
            tmp[i].trCap = acc[i].trCap;
            tmp[i].trNum = acc[i].trNum;

            tmp[i].accID = new char[strlen(acc[i].accID)+1];
            strcpy(tmp[i].accID, acc[i].accID);
            delete[] acc[i].accID;
        }

        delete[] acc;
        acc = tmp;
        accCap *= 2;
    }
    //Check for the account with same accID
    for (unsigned i = 0; i < accNum; ++i)
        if ( strcmp(accID, acc[i].accID) == 0)
            return false;

    //Set up new account
    acc[accNum].init = initialBalance;
    acc[accNum].balance = initialBalance;
    acc[accNum].accID = new char[strlen(accID)+1];
    strcpy(acc[accNum].accID, accID);

    accNum++;
    return true;
}

bool CBank::Transaction(const char *debAccID, const char *credAccID, unsigned int amount, const char *signature) {
    //same name of the account
    if (strcmp(debAccID, credAccID) == 0)
        return false;
    //Check if debAcc && credAcc exists
    int acc1 = -1, acc2 = -1;

    for (unsigned i = 0; i < accNum; ++i) {
        if(strcmp(debAccID, acc[i].accID) == 0)
            acc1 = (int)i;
        else if(strcmp(credAccID, acc[i].accID) == 0)
            acc2 = (int)i;
    }
    // if one or both does not exist, return false
    if (acc1 == -1 || acc2 == -1)
        return false;

    //Check if  needs realloc of transactions
    if (acc[acc1].trCap == acc[acc1].trNum)
        myTrRealloc(acc[acc1]);
    //Add tr to Debtor acc
    unsigned trNum = acc[acc1].trNum;

    acc[acc1].tran[trNum].sum = amount;
    acc[acc1].balance -= (int)amount; // update of account's balance

    acc[acc1].tran[trNum].sign = new char[strlen(signature)+1];
    strcpy(acc[acc1].tran[trNum].sign, signature);

    acc[acc1].tran[trNum].to = new char[strlen(credAccID)+1];
    strcpy(acc[acc1].tran[trNum].to, credAccID);

    acc[acc1].trNum++;

    //Check if Creditor needs realloc of transactions
    if (acc[acc2].trCap == acc[acc2].trNum)
        myTrRealloc(acc[acc2]);
    //Add tr to Creditor acc
    trNum = acc[acc2].trNum;

    acc[acc2].tran[trNum].sum = amount;
    acc[acc2].balance += (int)amount; // update of account's balance

    acc[acc2].tran[trNum].sign = new char[strlen(signature)+1];
    strcpy(acc[acc2].tran[trNum].sign, signature);

    acc[acc2].tran[trNum].from = new char[strlen(debAccID)+1];
    strcpy(acc[acc2].tran[trNum].from, debAccID);

    acc[acc2].trNum++;

    return true;
}

bool CBank::TrimAccount(const char *accID) {
    for (unsigned i = 0; i < accNum; ++i) {
        if(strcmp(accID, acc[i].accID) == 0)
        {
            for (unsigned j = 0; j < acc[i].trNum; ++j) {
                delete[] acc[i].tran[j].sign;
                delete[] acc[i].tran[j].from;
                delete[] acc[i].tran[j].to;
            }
            delete[] acc[i].tran;
            acc[i].tran = new CTransaction[10];
            acc[i].trNum = 0;
            acc[i].trCap = 10;
            acc[i].init = acc[i].balance;
            return true;
        }
    }
    return false;
}

CAccount CBank::Account(const char* accID) {
    for (unsigned i = 0; i < accNum; ++i) {
        if (strcmp(accID, acc[i].accID) == 0)
            return acc[i];
    }
    throw "No such account";
}

CBank::~CBank() {
    for (unsigned i = 0; i < accCap; ++i) {
        for (unsigned j = 0; j < acc[i].trNum; ++j) {
            delete[] acc[i].tran[j].sign;
            delete[] acc[i].tran[j].to;
            delete[] acc[i].tran[j].from;
        }
        delete[] acc[i].tran;
        delete[] acc[i].accID;
    }
    delete[] acc;
}

CBank::CBank(const CBank &x) {
    accCap = x.accCap;
    accNum = x.accNum;
    acc = new CAccount[accCap];

    for (unsigned i = 0; i < accNum; ++i) { // copying each account
        acc[i].trCap = x.acc[i].trCap;
        acc[i].balance = x.acc[i].balance;
        acc[i].init = x.acc[i].init;
        acc[i].trNum = x.acc[i].trNum;

        acc[i].accID = new char[strlen(x.acc[i].accID)+1];
        strcpy(acc[i].accID, x.acc[i].accID);

        delete[] acc[i].tran;
        acc[i].tran = new CTransaction[acc[i].trCap];

        for (unsigned j = 0; j < acc[i].trNum; ++j) { // Copying all transactions of each account
            if(x.acc[i].tran[j].to != nullptr){
                acc[i].tran[j].to = new char[strlen(x.acc[i].tran[j].to)+1];
                strcpy(acc[i].tran[j].to, x.acc[i].tran[j].to);
            }
            else if(x.acc[i].tran[j].from != nullptr){
                acc[i].tran[j].from = new char[strlen(x.acc[i].tran[j].from)+1];
                strcpy(acc[i].tran[j].from, x.acc[i].tran[j].from);
            }
            if(x.acc[i].tran[j].sign != nullptr) {
                acc[i].tran[j].sign = new char[strlen(x.acc[i].tran[j].sign) + 1];
                strcpy(acc[i].tran[j].sign, x.acc[i].tran[j].sign);
            }
            acc[i].tran[j].sum = x.acc[i].tran[j].sum;
        }
    }
}

CBank &CBank::operator=(const CBank &x) {
    for (unsigned k = 0; k < accCap; ++k) {
        for (unsigned i = 0; i < acc[k].trNum; ++i) {
            delete[] acc[k].tran[i].sign;
            delete[] acc[k].tran[i].from;
            delete[] acc[k].tran[i].to;
        }
        delete[] acc[k].tran;
        delete[] acc[k].accID;
    }
    accCap = x.accCap;
    accNum = x.accNum;
    delete[] acc;
    acc = new CAccount[accCap];

    for (unsigned i = 0; i < accNum; ++i) { // copying each account
        acc[i].trCap = x.acc[i].trCap;
        acc[i].balance = x.acc[i].balance;
        acc[i].init = x.acc[i].init;
        acc[i].trNum = x.acc[i].trNum;
        if (x.acc[i].accID != nullptr) {
            acc[i].accID = new char[strlen(x.acc[i].accID) + 1];
            strcpy(acc[i].accID, x.acc[i].accID);
        }
        delete[] acc[i].tran;
        acc[i].tran = new CTransaction[acc[i].trCap];
        for (unsigned j = 0; j < acc[i].trNum; ++j) { // Copying all transactions of each account
            if(x.acc[i].tran[j].to != nullptr){
                acc[i].tran[j].to = new char[strlen(x.acc[i].tran[j].to)+1];
                strcpy(acc[i].tran[j].to, x.acc[i].tran[j].to);
            }
            else if(x.acc[i].tran[j].from != nullptr){
                acc[i].tran[j].from = new char[strlen(x.acc[i].tran[j].from)+1];
                strcpy(acc[i].tran[j].from, x.acc[i].tran[j].from);
            }
            acc[i].tran[j].sign = new char[strlen(x.acc[i].tran[j].sign)+1];
            strcpy(acc[i].tran[j].sign, x.acc[i].tran[j].sign);
            acc[i].tran[j].sum = x.acc[i].tran[j].sum;
        }
    }
    return *this;
}

void myTrRealloc(CAccount &x){
    unsigned trCap = x.trCap;

    CTransaction* tmp = new CTransaction[trCap*2];

    for (unsigned i = 0; i < x.trCap; ++i) {
        tmp[i].sum = x.tran[i].sum;

        if (x.tran[i].sign != nullptr) {
            tmp[i].sign = new char[strlen(x.tran[i].sign) + 1];
            strcpy(tmp[i].sign, x.tran[i].sign);
            delete[] x.tran[i].sign;
        }
        if (x.tran[i].to != nullptr){
            tmp[i].to = new char[strlen(x.tran[i].to)+1];
            strcpy(tmp[i].to, x.tran[i].to);
            delete[] x.tran[i].to;
        }
        else if(x.tran[i].from != nullptr){
            tmp[i].from = new char[strlen(x.tran[i].from)+1];
            strcpy(tmp[i].from, x.tran[i].from);
            delete[] x.tran[i].from;
        }
    }

    x.trCap *= 2;
    delete[] x.tran;
    x.tran = tmp;
}

#ifndef __PROGTEST__
int main ( void )
{
    
}
#endif /* __PROGTEST__ */
