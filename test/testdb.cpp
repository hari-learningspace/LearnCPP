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
                cout << "DB Failure\n"; return -1;
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

    EXPECT_CALL(mdb, login("Hari","Simplepass"))
    .Times(1)
    .WillOnce(Return(false));

    //ACT
    int retvalue = db.Init("Hari", "SimplePass");

    //Assert
    EXPECT_EQ(retvalue,1);
}