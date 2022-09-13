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
#include <set>
#include <list>
#include <map>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <memory>
#include <functional>
#include <stdexcept>
#endif /* __PROGTEST */
using namespace std;

#ifndef __PROGTEST__
class CTimeStamp
{
public:
    CTimeStamp                              ( int               year,
                                              int               month,
                                              int               day,
                                              int               hour,
                                              int               minute,
                                              int               sec );
    int            Compare                                 ( const CTimeStamp & x ) const;
    friend ostream & operator <<                           ( ostream          & os,
                                                             const CTimeStamp & x );
    unsigned c_Year;
    unsigned c_Month;
    unsigned c_Day;
    unsigned c_Hour;
    unsigned c_Minute;
    unsigned c_Sec;
};

CTimeStamp::CTimeStamp(int year, int month, int day, int hour, int minute, int sec) {
    c_Year = year;
    c_Month = month;
    c_Day = day;
    c_Hour = hour;
    c_Minute = minute;
    c_Sec = sec;
}

int CTimeStamp::Compare(const CTimeStamp &x) const {
    if ( c_Year > x.c_Year)
        return 1;
    else if (c_Year < x.c_Year)
        return -1;

    if ( c_Month > x.c_Month)
        return 1;
    else if (c_Month < x.c_Month)
        return -1;

    if ( c_Day > x.c_Day)
        return 1;
    else if (c_Day < x.c_Day)
        return -1;

    if ( c_Hour > x.c_Hour)
        return 1;
    else if (c_Hour < x.c_Hour)
        return -1;

    if ( c_Minute > x.c_Minute)
        return 1;
    else if (c_Minute < c_Minute)
        return -1;

    if ( c_Sec > x.c_Sec)
        return 1;
    else if (c_Sec < x.c_Sec)
        return -1;

    return 0;
}

ostream &operator<<(ostream &os, const CTimeStamp &x) {
    os << x.c_Year << "-";
    if ( x.c_Month < 10)
        os << "0" << x.c_Month << "-";
    else
        os << x.c_Month << "-";

    if (x.c_Day < 10)
        os << "0" << x.c_Day << " ";
    else
        os << x.c_Day << " ";

    if (x.c_Hour < 10)
        os << "0" << x.c_Hour << ":";
    else
        os << x.c_Hour << ":";

    if (x.c_Minute < 10)
        os << "0" << x.c_Minute << ":";
    else
        os << x.c_Minute << ":";

    if (x.c_Sec < 10)
        os << "0" << x.c_Sec << "";
    else
        os << x.c_Sec << "";
    return os;
}

//=================================================================================================
class CMailBody
{
public:
    CMailBody                               ( int               size,
                                              const char      * data );
    CMailBody                               (CMailBody const &x);
    ~CMailBody                              () {delete m_Data;}
    CMailBody& operator =(const CMailBody& x);
    // copy cons/op=/destructor is correctly implemented in the testing environment
    friend ostream & operator <<                           ( ostream         & os,
                                                             const CMailBody & x )
    {
        return os << "mail body: " << x . m_Size << " B";
    }
private:
    int            m_Size;
    char         * m_Data;
};
// not sure if the copying of pointer is legit;
CMailBody::CMailBody(int size, const char *data) {
    m_Size = size;
    m_Data = new char(*data);
}

CMailBody::CMailBody(CMailBody const &x) {
    m_Size = x.m_Size;
    m_Data = new char(*x.m_Data);
}

CMailBody &CMailBody::operator=(const CMailBody &x) {
    if (this == &x)
        return *this;

    m_Size = x.m_Size;
    delete m_Data;
    m_Data = new char(*x.m_Data);
    return *this;
}

//=================================================================================================
class CAttach
{
public:
    CAttach                                 ( int               x )
            : m_X (x),
              m_RefCnt ( 1 )
    {
    }
    void           AddRef                                  ( void ) const
    {
        m_RefCnt ++;
    }
    void           Release                                 ( void ) const
    {
        if ( !--m_RefCnt )
            delete this;
    }
private:
    int            m_X;
    mutable int    m_RefCnt;
    CAttach                                 ( const CAttach   & x );
    CAttach      & operator =                              ( const CAttach   & x );
    ~CAttach                                 ( void ) = default;
    friend ostream & operator <<                           ( ostream         & os,
                                                             const CAttach   & x )
    {
        return os << "attachment: " << x . m_X << " B";
    }
};
//=================================================================================================
#endif /* __PROGTEST__, DO NOT remove */

class CMail
{
public:
    CMail                                   ( const CTimeStamp & timeStamp,
                                              const string     & from,
                                              const CMailBody  & body,
                                              const CAttach    * att )
                                              : timeStamp(timeStamp), body(body), attach(att) {
        this->from = from;
        if(this->attach != nullptr)
            this->attach->AddRef();
    }
    const string     & From                                ( void ) const {return from;}
    const CMailBody  & Body                                ( void ) const {return body;}
    const CTimeStamp & TimeStamp                           ( void ) const {return timeStamp;}
    const CAttach* Attachment                              ( void ) const { return  attach;}

    friend ostream & operator <<                           ( ostream          & os,
                                                             const CMail      & x );
private:
    CTimeStamp timeStamp;
    string from;
    CMailBody body;
    const CAttach * attach;
};

ostream &operator<<(ostream &os, const CMail &x) {
    os << x.timeStamp << " " << x.from << " " << x.body;
    if (x.attach != nullptr)
        os << " + " << *x.attach;
    return os;
}

class CFolder{
public:
    string name;
    vector<CMail> folder;
};

bool compareName(const CFolder &first, const CFolder &second);
bool compareTimeStamp(const CMail &first, const CMail &second);

//=================================================================================================
class CMailBox
{
public:
    CMailBox                                ( void );
    bool           Delivery                                ( const CMail      & mail );
    bool           NewFolder                               ( const string     & folderName );
    bool           MoveMail                                ( const string     & fromFolder,
                                                             const string     & toFolder );
    list<CMail>    ListMail                                ( const string     & folderName,
                                                             const CTimeStamp & from,
                                                             const CTimeStamp & to ) const;
    set<string>    ListAddr                                ( const CTimeStamp & from,
                                                             const CTimeStamp & to ) const;
private:
    vector<CFolder> mails;
};

CMailBox::CMailBox(void) {
    CFolder x;
    x.name = "inbox";
    mails.push_back(x);
}

bool CMailBox::Delivery(const CMail &mail) {
    CFolder y;
    y.name = "inbox";
    unsigned x = lower_bound(mails.begin(), mails.end(), y, compareName) - mails.begin();

    mails[x].folder.insert(lower_bound(mails[x].folder.begin(), mails[x].folder.end(), mail, compareTimeStamp), mail);
    return true;
}

bool CMailBox::NewFolder(const string &folderName) {
    CFolder x;
    x.name = folderName;
    if (binary_search(mails.begin(), mails.end(), x, compareName))
        return false;
    mails.insert(lower_bound(mails.begin(), mails.end(), x, compareName), x);
    return true;
}

bool CMailBox::MoveMail(const string &fromFolder, const string &toFolder) {
    CFolder x, y;
    x.name = fromFolder;
    y.name = toFolder;
    if (!binary_search(mails.begin(), mails.end(), x, compareName) ||
        !binary_search(mails.begin(), mails.end(), y, compareName))
        return false;
    if(fromFolder == toFolder)
        return true;
    unsigned pos1 = lower_bound(mails.begin(), mails.end(), x, compareName) - mails.begin();
    unsigned pos2 = lower_bound(mails.begin(), mails.end(), y, compareName) - mails.begin();
    //inserting all mails into toFolder
    for (unsigned i = 0; i < mails[pos1].folder.size(); ++i) {
        mails[pos2].folder.insert(
                lower_bound(mails[pos2].folder.begin(),mails[pos2].folder.end(),mails[pos1].folder[i],compareTimeStamp),
                mails[pos1].folder[i]);
    }
    mails[pos1].folder.clear(); // clearing the fromFolder
    return true;
}

list<CMail> CMailBox::ListMail(const string &folderName, const CTimeStamp &from, const CTimeStamp &to) const {
    list <CMail> x;
    CFolder y;
    y.name = folderName;

    if (!binary_search(mails.begin(), mails.end(), y, compareName))
        return x;

    CMailBody body(0, "x");
    CMail beginMail(from, " ", body, nullptr);
    CMail endMail(to, " ", body, nullptr);

    unsigned index = lower_bound(mails.begin(), mails.end(), y, compareName) - mails.begin();
    //distance?
    int dis = distance(lower_bound(mails[index].folder.begin(), mails[index].folder.end(), beginMail, compareTimeStamp), upper_bound(mails[index].folder.begin(), mails[index].folder.end(), endMail, compareTimeStamp));
    dis = abs(dis);

    auto it = lower_bound(mails[index].folder.begin(), mails[index].folder.end(), beginMail, compareTimeStamp) - mails[index].folder.begin();
    for (int i = 0; i < dis; ++i) {
        x.push_back(mails[index].folder[it + i]);
    }

    return x;

}

set<string> CMailBox::ListAddr(const CTimeStamp &from, const CTimeStamp &to) const {
    set<string> x;
    CMailBody body(0, "x");
    CMail beginMail(from, " ", body, nullptr);
    CMail endMail(to, " ", body, nullptr);
    int dis;
    // v kazdom foldru najdu kolik je tam takovych emailu
    for (unsigned i = 0; i < mails.size(); ++i) {
        dis = distance(lower_bound(mails[i].folder.begin(), mails[i].folder.end(), beginMail, compareTimeStamp), upper_bound(mails[i].folder.begin(), mails[i].folder.end(), endMail, compareTimeStamp));
        dis = abs(dis);

        auto it = lower_bound(mails[i].folder.begin(), mails[i].folder.end(), beginMail, compareTimeStamp) - mails[i].folder.begin();
        for (int j = 0; j < dis; ++j) {
            x.insert(mails[i].folder[it + j].From());
        }
    }
    return x;
}


bool compareName(const CFolder &first, const CFolder &second) {
    return first.name < second.name;
}
bool compareTimeStamp(const CMail &first, const CMail &second) {
    int x = first.TimeStamp().Compare(second.TimeStamp());
    if ( x > 0 || x == 0)
        return false;
    return true;
}

//=================================================================================================
#ifndef __PROGTEST__
static string showMail ( const list<CMail> & l )
{
    ostringstream oss;
    for ( const auto & x : l )
        oss << x << endl;
    return oss . str ();
}
static string showUsers ( const set<string> & s )
{
    ostringstream oss;
    for ( const auto & x : s )
        oss << x << endl;
    return oss . str ();
}
int main ( void )
{
    list<CMail> mailList;
    set<string> users;
    CAttach   * att;

    CMailBox m0;
    assert ( m0 . Delivery ( CMail ( CTimeStamp ( 2014, 3, 31, 15, 24, 13 ), "user1@fit.cvut.cz", CMailBody ( 14, "mail content 1" ), nullptr ) ) );
    assert ( m0 . Delivery ( CMail ( CTimeStamp ( 2014, 3, 31, 15, 26, 23 ), "user2@fit.cvut.cz", CMailBody ( 22, "some different content" ), nullptr ) ) );
    att = new CAttach ( 200 );
    assert ( m0 . Delivery ( CMail ( CTimeStamp ( 2014, 3, 31, 11, 23, 43 ), "boss1@fit.cvut.cz", CMailBody ( 14, "urgent message" ), att ) ) );
    assert ( m0 . Delivery ( CMail ( CTimeStamp ( 2014, 3, 31, 18, 52, 27 ), "user1@fit.cvut.cz", CMailBody ( 14, "mail content 2" ), att ) ) );
    att -> Release ();
    att = new CAttach ( 97 );
    assert ( m0 . Delivery ( CMail ( CTimeStamp ( 2014, 3, 31, 16, 12, 48 ), "boss1@fit.cvut.cz", CMailBody ( 24, "even more urgent message" ), att ) ) );
    att -> Release ();
    assert ( showMail ( m0 . ListMail ( "inbox",
                                        CTimeStamp ( 2000, 1, 1, 0, 0, 0 ),
                                        CTimeStamp ( 2050, 12, 31, 23, 59, 59 ) ) ) == "2014-03-31 11:23:43 boss1@fit.cvut.cz mail body: 14 B + attachment: 200 B\n"
                                                                                       "2014-03-31 15:24:13 user1@fit.cvut.cz mail body: 14 B\n"
                                                                                       "2014-03-31 15:26:23 user2@fit.cvut.cz mail body: 22 B\n"
                                                                                       "2014-03-31 16:12:48 boss1@fit.cvut.cz mail body: 24 B + attachment: 97 B\n"
                                                                                       "2014-03-31 18:52:27 user1@fit.cvut.cz mail body: 14 B + attachment: 200 B\n" );
    assert ( showMail ( m0 . ListMail ( "inbox",
                                        CTimeStamp ( 2014, 3, 31, 15, 26, 23 ),
                                        CTimeStamp ( 2014, 3, 31, 16, 12, 48 ) ) ) == "2014-03-31 15:26:23 user2@fit.cvut.cz mail body: 22 B\n"
                                                                                      "2014-03-31 16:12:48 boss1@fit.cvut.cz mail body: 24 B + attachment: 97 B\n" );
    assert ( showUsers ( m0 . ListAddr ( CTimeStamp ( 2000, 1, 1, 0, 0, 0 ),
                                         CTimeStamp ( 2050, 12, 31, 23, 59, 59 ) ) ) == "boss1@fit.cvut.cz\n"
                                                                                        "user1@fit.cvut.cz\n"
                                                                                        "user2@fit.cvut.cz\n" );
    assert ( showUsers ( m0 . ListAddr ( CTimeStamp ( 2014, 3, 31, 15, 26, 23 ),
                                         CTimeStamp ( 2014, 3, 31, 16, 12, 48 ) ) ) == "boss1@fit.cvut.cz\n"
                                                                                       "user2@fit.cvut.cz\n" );

    CMailBox m1;
    assert ( m1 . NewFolder ( "work" ) );
    assert ( m1 . NewFolder ( "spam" ) );
    assert ( !m1 . NewFolder ( "spam" ) );
    assert ( m1 . Delivery ( CMail ( CTimeStamp ( 2014, 3, 31, 15, 24, 13 ), "user1@fit.cvut.cz", CMailBody ( 14, "mail content 1" ), nullptr ) ) );
    att = new CAttach ( 500 );
    assert ( m1 . Delivery ( CMail ( CTimeStamp ( 2014, 3, 31, 15, 26, 23 ), "user2@fit.cvut.cz", CMailBody ( 22, "some different content" ), att ) ) );
    att -> Release ();
    assert ( m1 . Delivery ( CMail ( CTimeStamp ( 2014, 3, 31, 11, 23, 43 ), "boss1@fit.cvut.cz", CMailBody ( 14, "urgent message" ), nullptr ) ) );
    att = new CAttach ( 468 );
    assert ( m1 . Delivery ( CMail ( CTimeStamp ( 2014, 3, 31, 18, 52, 27 ), "user1@fit.cvut.cz", CMailBody ( 14, "mail content 2" ), att ) ) );
    att -> Release ();
    assert ( m1 . Delivery ( CMail ( CTimeStamp ( 2014, 3, 31, 16, 12, 48 ), "boss1@fit.cvut.cz", CMailBody ( 24, "even more urgent message" ), nullptr ) ) );
    assert ( showMail ( m1 . ListMail ( "inbox",
                                        CTimeStamp ( 2000, 1, 1, 0, 0, 0 ),
                                        CTimeStamp ( 2050, 12, 31, 23, 59, 59 ) ) ) == "2014-03-31 11:23:43 boss1@fit.cvut.cz mail body: 14 B\n"
                                                                                       "2014-03-31 15:24:13 user1@fit.cvut.cz mail body: 14 B\n"
                                                                                       "2014-03-31 15:26:23 user2@fit.cvut.cz mail body: 22 B + attachment: 500 B\n"
                                                                                       "2014-03-31 16:12:48 boss1@fit.cvut.cz mail body: 24 B\n"
                                                                                       "2014-03-31 18:52:27 user1@fit.cvut.cz mail body: 14 B + attachment: 468 B\n" );
    assert ( showMail ( m1 . ListMail ( "work",
                                        CTimeStamp ( 2000, 1, 1, 0, 0, 0 ),
                                        CTimeStamp ( 2050, 12, 31, 23, 59, 59 ) ) ) == "" );
    assert ( m1 . MoveMail ( "inbox", "work" ) );
    assert ( showMail ( m1 . ListMail ( "inbox",
                                        CTimeStamp ( 2000, 1, 1, 0, 0, 0 ),
                                        CTimeStamp ( 2050, 12, 31, 23, 59, 59 ) ) ) == "" );
    assert ( showMail ( m1 . ListMail ( "work",
                                        CTimeStamp ( 2000, 1, 1, 0, 0, 0 ),
                                        CTimeStamp ( 2050, 12, 31, 23, 59, 59 ) ) ) == "2014-03-31 11:23:43 boss1@fit.cvut.cz mail body: 14 B\n"
                                                                                       "2014-03-31 15:24:13 user1@fit.cvut.cz mail body: 14 B\n"
                                                                                       "2014-03-31 15:26:23 user2@fit.cvut.cz mail body: 22 B + attachment: 500 B\n"
                                                                                       "2014-03-31 16:12:48 boss1@fit.cvut.cz mail body: 24 B\n"
                                                                                       "2014-03-31 18:52:27 user1@fit.cvut.cz mail body: 14 B + attachment: 468 B\n" );
    assert ( m1 . Delivery ( CMail ( CTimeStamp ( 2014, 3, 31, 19, 24, 13 ), "user2@fit.cvut.cz", CMailBody ( 14, "mail content 4" ), nullptr ) ) );
    att = new CAttach ( 234 );
    assert ( m1 . Delivery ( CMail ( CTimeStamp ( 2014, 3, 31, 13, 26, 23 ), "user3@fit.cvut.cz", CMailBody ( 9, "complains" ), att ) ) );
    att -> Release ();
    assert ( showMail ( m1 . ListMail ( "inbox",
                                        CTimeStamp ( 2000, 1, 1, 0, 0, 0 ),
                                        CTimeStamp ( 2050, 12, 31, 23, 59, 59 ) ) ) == "2014-03-31 13:26:23 user3@fit.cvut.cz mail body: 9 B + attachment: 234 B\n"
                                                                                       "2014-03-31 19:24:13 user2@fit.cvut.cz mail body: 14 B\n" );
    assert ( showMail ( m1 . ListMail ( "work",
                                        CTimeStamp ( 2000, 1, 1, 0, 0, 0 ),
                                        CTimeStamp ( 2050, 12, 31, 23, 59, 59 ) ) ) == "2014-03-31 11:23:43 boss1@fit.cvut.cz mail body: 14 B\n"
                                                                                       "2014-03-31 15:24:13 user1@fit.cvut.cz mail body: 14 B\n"
                                                                                       "2014-03-31 15:26:23 user2@fit.cvut.cz mail body: 22 B + attachment: 500 B\n"
                                                                                       "2014-03-31 16:12:48 boss1@fit.cvut.cz mail body: 24 B\n"
                                                                                       "2014-03-31 18:52:27 user1@fit.cvut.cz mail body: 14 B + attachment: 468 B\n" );
    assert ( m1 . MoveMail ( "inbox", "work" ) );
    assert ( showMail ( m1 . ListMail ( "inbox",
                                        CTimeStamp ( 2000, 1, 1, 0, 0, 0 ),
                                        CTimeStamp ( 2050, 12, 31, 23, 59, 59 ) ) ) == "" );
    assert ( showMail ( m1 . ListMail ( "work",
                                        CTimeStamp ( 2000, 1, 1, 0, 0, 0 ),
                                        CTimeStamp ( 2050, 12, 31, 23, 59, 59 ) ) ) == "2014-03-31 11:23:43 boss1@fit.cvut.cz mail body: 14 B\n"
                                                                                       "2014-03-31 13:26:23 user3@fit.cvut.cz mail body: 9 B + attachment: 234 B\n"
                                                                                       "2014-03-31 15:24:13 user1@fit.cvut.cz mail body: 14 B\n"
                                                                                       "2014-03-31 15:26:23 user2@fit.cvut.cz mail body: 22 B + attachment: 500 B\n"
                                                                                       "2014-03-31 16:12:48 boss1@fit.cvut.cz mail body: 24 B\n"
                                                                                       "2014-03-31 18:52:27 user1@fit.cvut.cz mail body: 14 B + attachment: 468 B\n"
                                                                                       "2014-03-31 19:24:13 user2@fit.cvut.cz mail body: 14 B\n" );

    return 0;
}
#endif /* __PROGTEST__ */
