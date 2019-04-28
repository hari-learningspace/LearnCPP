#include <iostream>
#include <vector>
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using namespace std;
using ::testing::Atleast;
using ::testing::Return;
using ::testing::_;

class DataBaseConnect {
    public:
        virtual bool login(string username, string password)
        {return ture;}
        virtual bool logout(string username) {return true;}
        virtual int fetchRecord() {return -1;}
};

class MyDatabase {
    DataBaseConnect &dbC;
    public:
        MyDatabase(DataBaseConnect & _dbC) : dbC(_dbC) {}

        int Init(string username, string password){
            if(dbC.login(username,password) != true) {
                cout << "DB Failure\n"; return -1;
            } else {
                cout << "DB Success\n"; return 1;
            }
        }
}