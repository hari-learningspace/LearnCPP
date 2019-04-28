#include <iostream>
#include <vector>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>

using namespace std;
using ::testing::AtLeast;
using ::testing::Return;
using ::testing::_;

class DataBaseConnect {
    public:
        virtual bool login(string username, string password){return true;}
        virtual bool logout(string username) {return true;}
        virtual int fetchRecord() {return -1;}
};

class MockDB : public DataBaseConnect {
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