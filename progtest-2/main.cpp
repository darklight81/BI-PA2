#ifndef __PROGTEST__

#include <cstdio>
#include <cstdlib>
#include <cmath>
#include <cassert>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <string>
#include <utility>
#include <vector>
#include <memory>
#include <functional>
#include <stdexcept>
#include <algorithm>

using namespace std;
#endif /* __PROGTEST__ */


class CCitizen {
public:
    CCitizen(string name, string address, string account);

    const string &getName() const;

    const string &getAddress() const;

    const string &getAccount() const;

    unsigned int getIncome() const;

    void setIncome(unsigned int income);

    unsigned int getExpense() const;

    void setExpense(unsigned int expense);
private:
    string name;
    string address;
    string account;
    unsigned income;
    unsigned expense;
};

CCitizen::CCitizen(string name, string address, string account) {
    this->name = std::move(name);
    this->address = std::move(address);
    this->account = std::move(account);
    income = 0;
    expense = 0;
}

const string &CCitizen::getName() const {
    return name;
}

const string &CCitizen::getAddress() const {
    return address;
}

const string &CCitizen::getAccount() const {
    return account;
}

unsigned int CCitizen::getIncome() const {
    return income;
}

void CCitizen::setIncome(const unsigned int income) {
    CCitizen::income += income;
}

unsigned int CCitizen::getExpense() const {
    return expense;
}

void CCitizen::setExpense(const unsigned int expense) {
    CCitizen::expense += expense;
}


class CIterator {
public:
    bool AtEnd(void) const;

    void Next(void);

    string Name(void) const;

    string Addr(void) const;

    string Account(void) const;

    explicit CIterator(vector<CCitizen *> vec);

    ~CIterator() {
        vec.clear();
    }

private:
    unsigned iterator;
    vector<CCitizen *> vec;
};

CIterator::CIterator(vector<CCitizen *> vec) {
    this->vec = std::move(vec);
    iterator = 0;
}

bool CIterator::AtEnd() const {
    return iterator == vec.size();
}

void CIterator::Next() {
    iterator++;
}

string CIterator::Name(void) const {
    return vec.at(iterator)->getName();
}

string CIterator::Addr(void) const {
    return vec.at(iterator)->getAddress();
}

string CIterator::Account(void) const {
    return vec.at(iterator)->getAccount();
}

//database of Citizens, sorted by name AND also by account number
class CTaxRegister {
public:
    bool Birth(const string &name,
               const string &addr,
               const string &account);

    bool Death(const string &name,
               const string &addr);

    bool Income(const string &account,
                int amount);

    bool Income(const string &name,
                const string &addr,
                int amount);

    bool Expense(const string &account,
                 int amount);

    bool Expense(const string &name,
                 const string &addr,
                 int amount);

    bool Audit(const string &name,
               const string &addr,
               string &account,
               int &sumIncome,
               int &sumExpense) const;

    CIterator ListByName(void) const;

    vector<CCitizen *> getNameVec() const;

    ~CTaxRegister();

private:
    vector<CCitizen *> nameVec;
    vector<CCitizen *> accVec;
};
//compare function needed for binary_search in nameVec
bool compareName(const CCitizen *first, const CCitizen *second) {
    if (first->getName() == second->getName())
        return first->getAddress() < second->getAddress();
    return (first->getName() < second->getName());
}
//compare function needed for binary_search in accVec
bool compareAccount(const CCitizen *first, const CCitizen *second) {
    return first->getAccount() < second->getAccount();
}
//adds citizen to the database, if there's already one with the same name and same address OR anyone with the same acc num, returns false
bool CTaxRegister::Birth(const string &name, const string &addr, const string &account) {
    auto *citizen = new CCitizen(name, addr, account);

    if (binary_search(nameVec.begin(), nameVec.end(), citizen, compareName) ||
        binary_search(accVec.begin(), accVec.end(), citizen, compareAccount)) {
        delete citizen;
        return false;
    }

    nameVec.insert(lower_bound(nameVec.begin(), nameVec.end(), citizen, compareName), citizen);
    accVec.insert(lower_bound(accVec.begin(), accVec.end(), citizen, compareAccount), citizen);

    return true;
}
//removes the citizen from database, if there's no corresponding name && address, returns false
bool CTaxRegister::Death(const string &name, const string &addr) {
    auto *citizen = new CCitizen(name, addr, "0");

    if (!binary_search(nameVec.begin(), nameVec.end(), citizen, compareName)) {
        delete citizen;
        return false;
    }

    CCitizen *citizen1 = nameVec.at(lower_bound(nameVec.begin(), nameVec.end(), citizen, compareName) - nameVec.begin());
    nameVec.erase(lower_bound(nameVec.begin(), nameVec.end(), citizen1, compareName));
    accVec.erase(lower_bound(accVec.begin(), accVec.end(), citizen1, compareAccount));

    delete citizen;
    delete citizen1;

    return true;
}
//adds given amount to the income of citizen of the given account, returns false if the account doesn't exist
bool CTaxRegister::Income(const string &account, int amount) {
    auto *citizen = new CCitizen("Place", "Holder", account);

    if (!binary_search(accVec.begin(), accVec.end(), citizen, compareAccount)) {
        delete citizen;
        return false;
    }

    accVec.at(lower_bound(accVec.begin(), accVec.end(), citizen, compareAccount) - accVec.begin())->setIncome(amount);

    delete citizen;
    return true;
}
//adds given amount to the income of citizen of the given name and address, returns false if the citizen is not in the database
bool CTaxRegister::Income(const string &name, const string &addr, int amount) {
    auto *citizen = new CCitizen(name, addr, "0");

    if (!binary_search(nameVec.begin(), nameVec.end(), citizen, compareName)) {
        delete citizen;
        return false;
    }

    nameVec.at(lower_bound(nameVec.begin(), nameVec.end(), citizen, compareName) - nameVec.begin())->setIncome(amount);

    delete citizen;
    return true;
}
//adds given expense to the income of citizen of the given account, returns false if the account doesn't exist
bool CTaxRegister::Expense(const string &account, int amount) {
    auto *citizen = new CCitizen("Place", "Holder", account);

    if (!binary_search(accVec.begin(), accVec.end(), citizen, compareAccount)) {
        delete citizen;
        return false;
    }

    accVec.at(lower_bound(accVec.begin(), accVec.end(), citizen, compareAccount) - accVec.begin())->setExpense(amount);

    delete citizen;
    return true;
}
//adds given amount to the expense of citizen of the given name and address, returns false if the citizen is not in the database
bool CTaxRegister::Expense(const string &name, const string &addr, int amount) {
    auto *citizen = new CCitizen(name, addr, "0");

    if (!binary_search(nameVec.begin(), nameVec.end(), citizen, compareName)) {
        delete citizen;
        return false;
    }

    nameVec.at(lower_bound(nameVec.begin(), nameVec.end(), citizen, compareName) - nameVec.begin())->setExpense(amount);

    delete citizen;
    return true;
}
//returns account number, income and expense of the given citizen, if there's no citizen with given name and address, returns false
bool CTaxRegister::Audit(const string &name, const string &addr, string &account, int &sumIncome, int &sumExpense) const {
    auto *citizen = new CCitizen(name, addr, "0");

    if (!binary_search(nameVec.begin(), nameVec.end(), citizen, compareName)) {
        delete citizen;
        return false;
    }

    account = nameVec.at(
            lower_bound(nameVec.begin(), nameVec.end(), citizen, compareName) - nameVec.begin())->getAccount();
    sumIncome = (int) nameVec.at(
            lower_bound(nameVec.begin(), nameVec.end(), citizen, compareName) - nameVec.begin())->getIncome();
    sumExpense = (int) nameVec.at(
            lower_bound(nameVec.begin(), nameVec.end(), citizen, compareName) - nameVec.begin())->getExpense();

    delete citizen;
    return true;
}

vector<CCitizen *> CTaxRegister::getNameVec() const {
    return nameVec;
}

CIterator CTaxRegister::ListByName(void) const {
    CIterator it = *new CIterator(getNameVec());
    return it;
}

CTaxRegister::~CTaxRegister() {
        for (auto & i : nameVec) {
            delete i;
        }

        nameVec.clear();
        accVec.clear();
}

#ifndef __PROGTEST__

int main(void) {
    string acct;
    int sumIncome, sumExpense;
    CTaxRegister b1;
    assert (b1.Birth("John Smith", "Oak Road 23", "123/456/789"));
    assert (b1.Birth("Jane Hacker", "Main Street 17", "Xuj5#94"));
    assert (b1.Birth("Peter Hacker", "Main Street 17", "634oddT"));
    assert (b1.Birth("John Smith", "Main Street 17", "Z343rwZ"));
    assert (b1.Income("Xuj5#94", 1000));
    assert (b1.Income("634oddT", 2000));
    assert (b1.Income("123/456/789", 3000));
    assert (b1.Income("634oddT", 4000));
    assert (b1.Income("Peter Hacker", "Main Street 17", 2000));
    assert (b1.Expense("Jane Hacker", "Main Street 17", 2000));
    assert (b1.Expense("John Smith", "Main Street 17", 500));
    assert (b1.Expense("Jane Hacker", "Main Street 17", 1000));
    assert (b1.Expense("Xuj5#94", 1300));
    assert (b1.Audit("John Smith", "Oak Road 23", acct, sumIncome, sumExpense));
    assert (acct == "123/456/789");
    assert (sumIncome == 3000);
    assert (sumExpense == 0);
    assert (b1.Audit("Jane Hacker", "Main Street 17", acct, sumIncome, sumExpense));
    assert (acct == "Xuj5#94");
    assert (sumIncome == 1000);
    assert (sumExpense == 4300);
    assert (b1.Audit("Peter Hacker", "Main Street 17", acct, sumIncome, sumExpense));
    assert (acct == "634oddT");
    assert (sumIncome == 8000);
    assert (sumExpense == 0);
    assert (b1.Audit("John Smith", "Main Street 17", acct, sumIncome, sumExpense));
    assert (acct == "Z343rwZ");
    assert (sumIncome == 0);
    assert (sumExpense == 500);
    CIterator it = b1.ListByName();
    assert (!it.AtEnd()
            && it.Name() == "Jane Hacker"
            && it.Addr() == "Main Street 17"
            && it.Account() == "Xuj5#94");
    it.Next();
    assert (!it.AtEnd()
            && it.Name() == "John Smith"
            && it.Addr() == "Main Street 17"
            && it.Account() == "Z343rwZ");
    it.Next();
    assert (!it.AtEnd()
            && it.Name() == "John Smith"
            && it.Addr() == "Oak Road 23"
            && it.Account() == "123/456/789");
    it.Next();
    assert (!it.AtEnd()
            && it.Name() == "Peter Hacker"
            && it.Addr() == "Main Street 17"
            && it.Account() == "634oddT");
    it.Next();
    assert (it.AtEnd());

    assert (b1.Death("John Smith", "Main Street 17"));

    CTaxRegister b2;
    assert (b2.Birth("John Smith", "Oak Road 23", "123/456/789"));
    assert (b2.Birth("Jane Hacker", "Main Street 17", "Xuj5#94"));
    assert (!b2.Income("634oddT", 4000));
    assert (!b2.Expense("John Smith", "Main Street 18", 500));
    assert (!b2.Audit("John Nowak", "Second Street 23", acct, sumIncome, sumExpense));
    assert (!b2.Death("Peter Nowak", "5-th Avenue"));
    assert (!b2.Birth("Jane Hacker", "Main Street 17", "4et689A"));
    assert (!b2.Birth("Joe Hacker", "Elm Street 23", "Xuj5#94"));
    assert (b2.Death("Jane Hacker", "Main Street 17"));
    assert (b2.Birth("Joe Hacker", "Elm Street 23", "Xuj5#94"));
    assert (b2.Audit("Joe Hacker", "Elm Street 23", acct, sumIncome, sumExpense));
    assert (acct == "Xuj5#94");
    assert (sumIncome == 0);
    assert (sumExpense == 0);
    assert (!b2.Birth("Joe Hacker", "Elm Street 23", "AAj5#94"));

    return 0;
}

#endif /* __PROGTEST__ */
