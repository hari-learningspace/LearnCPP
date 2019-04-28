#include <iostream>
#include <vector>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>

using namespace std;
using ::testing::AtLeast;
using ::testing::Return;
using ::testing::_;
using ::testing::Invoke;
using ::testing::InvokeWithoutArgs;
using ::testing::DoDefault;
using ::testing::DoAll;

class DataBaseConnect {
    public:
        virtual bool login(string username, string password){cout<< "Original Login\n" ; return true;}
        virtual bool logout(string username) {return true;}
        virtual int fetchRecord() {return -1;}
};

class MockDB : public DataBaseConnect {
    public:
        MOCK_METHOD0(fetchRecord, int());
        MOCK_METHOD1(logout, bool(string username));
        MOCK_METHOD2(login, bool(string username, string password));
};

class MockDataBaseConnect {
    public:
        MOCK_METHOD0(fetchRecord, int());
        MOCK_METHOD1(logout, bool(string username));
        MOCK_METHOD2(login, bool(string username, string password));
};


class MyDatabase {
    DataBaseConnect & dbC;
    public:
        MyDatabase(DataBaseConnect & _dbC) : dbC(_dbC) {}

        int Init(string username, string password){
            if(dbC.login(username,password) != true) {
              if(dbC.login(username,password) != true) {  
                cout << "DB Failure 2nd Time\n"; return -1;
                } 
            } else {
                cout << "DB Success\n"; return 1;
            }
        }
};


class MyDatabase2 {
    MockDataBaseConnect & mdbC;
    public:
        MyDatabase2(MockDataBaseConnect & _mdbC) : mdbC(_mdbC) {}

        int Init(string username, string password){
            if(mdbC.login(username,password) != true) {
              if(mdbC.login(username,password) != true) {  
                cout << "DB Failure 2nd Time\n"; return -1;
                } 
            } else {
                cout << "DB Success\n"; return 1;
            }
        }
};

TEST(MyDBTest, LoginTest)
{
    //Arrange
    MockDB mdb;
    MyDatabase db(mdb);

    EXPECT_CALL(mdb, login("Hari", "SimplePass"))
    .Times(1)
    .WillOnce(Return(true));

    //ACT
    int retvalue = db.Init("Hari", "SimplePass");

    //Assert
    EXPECT_EQ(retvalue,1);
}

TEST(MyDBTest, LoginFailure)
{
    //Arrange
    MockDB mdb;
    MyDatabase db(mdb);

    EXPECT_CALL(mdb, login(_,_))
    .Times(2)
    .WillRepeatedly(Return(false));

    //ACT
    int retvalue = db.Init("Hari", "SimplePass");

    //Assert
    EXPECT_EQ(retvalue,-1);
}

TEST(MyDBTest, LoginOnCall)
{
    //Arrange
    MockDB mdb;
    MyDatabase db(mdb);

    ON_CALL(mdb, login(_,_)).WillByDefault(Return(true));

    //ACT
    int retvalue = db.Init("Hari", "SimplePass");

    //Assert
    EXPECT_EQ(retvalue,1);
}

TEST(MyDBTest, InvokeWithClass)
{
    MockDataBaseConnect mdbc;
    MyDatabase2 db2(mdbc);

    EXPECT_CALL(mdbc, login("Hari", "SimplePass"))
    .Times(1)
    .WillOnce(Return(true));

    //ACT
    int retvalue = db2.Init("Hari", "SimplePass");

    //Assert
    EXPECT_EQ(retvalue,1);
}

TEST(MyDBTest, InvokeClass)
{
    //Arrange
    MockDB mdb;
    MyDatabase db(mdb);
    DataBaseConnect dbtest;

    EXPECT_CALL(mdb, login("Hari", "SimplePass"))
    .Times(AtLeast(1))
    .WillOnce(Invoke(&dbtest, &DataBaseConnect::login));

    //ACT
    int retvalue = db.Init("Hari", "SimplePass");

    //Assert
    EXPECT_EQ(retvalue,1);
}

struct testABC {
    bool DummyLogin(string username, string password){
        cout << "Dummy Function Called\n";
        return true;
    }

    void DummyLogin2(string username, string password){
        cout << "Dummy Function Called\n";
    }

};

TEST(MyDBTest, InvokeStruct)
{
    //Arrange
    MockDB mdb;
    MyDatabase db(mdb);
    testABC dbtest;

    EXPECT_CALL(mdb, login("Hari", "SimplePass"))
    .Times(AtLeast(1))
    .WillOnce(Invoke(&dbtest, &testABC::DummyLogin));

    //ACT
    int retvalue = db.Init("Hari", "SimplePass");

    //Assert
    EXPECT_EQ(retvalue,1);
}

bool DummyFn()
{
    cout << "Global Function Called\n";
    return true;
}

TEST(MyDBTest, InvokeGlobalFn)
{
    //Arrange
    MockDB mdb;
    MyDatabase db(mdb);


    EXPECT_CALL(mdb, login("Hari", "SimplePass"))
    .Times(AtLeast(1))
    .WillOnce(InvokeWithoutArgs(DummyFn));

    //ACT
    int retvalue = db.Init("Hari", "SimplePass");

    //Assert
    EXPECT_EQ(retvalue,1);
}

TEST(MyDBTest, DefaultAction)
{
    //Arrange
    MockDB mdb;
    MyDatabase db(mdb);
    testABC dbtest;

    ON_CALL(mdb, login(_,_)).WillByDefault(Invoke(&dbtest, &testABC::DummyLogin));
    EXPECT_CALL(mdb, login(_,_))
    .Times(AtLeast(1))
    .WillOnce(DoDefault());

    //ACT
    int retvalue = db.Init("Hari", "SimplePass");

    //Assert
    EXPECT_EQ(retvalue,1);
}



TEST(MyDBTest, MultipleAction)
{
    //Arrange
    MockDB mdb;
    MyDatabase db(mdb);
    testABC dbtest;

    EXPECT_CALL(mdb, login("Hari", "SimplePass"))
    .Times(AtLeast(1))
    .WillOnce(DoAll(Invoke(&dbtest, &testABC::DummyLogin2), 
                    Invoke(&dbtest, &testABC::DummyLogin2),Return(true)));

    //ACT
    int retvalue = db.Init("Hari", "SimplePass");

    //Assert
    EXPECT_EQ(retvalue,1);
}