#include "DB_Connector.h"

#include <iostream>
#include <mysql/jdbc.h>

using namespace std;

DB_Connector::DB_Connector()
{
    Connect();
}

void DB_Connector::Connect()
{
    try
    {
        //sql::mysql::MySQL_Driver* Driver = sql::mysql::get_mysql_driver_instance();

        sql::Driver* driver = sql::mysql::get_driver_instance();

        if (driver == nullptr)
        {
            //cerr << "driver를 가져오지 못했습니다." << endl;
        }
        else
        {
            //cout << "driver 획득 성공" << endl;
        }

        con.reset(driver->connect(Url,User,Password));  

        if (!con)
        {
            //cerr << "connect는 호출됐지만 Connection 객체가 nullptr 입니다." << endl;
        }

        con->setSchema(Schema);

        //cout << "DB 연결 성공" << endl;
    }
    catch (sql::SQLException& e)
    {
        //cout << "DB 연결 실패" << endl;
        //cout << "Error Code : " << e.getErrorCode() << endl;
        //cout << "SQL State  : " << e.getSQLState() << endl;
        //cout << "What       : " << e.what() << endl;
    }
}