#pragma once

#include <memory>
#include <string>
#include <mysql/jdbc.h>

class DB_Connector
{
private:
    //sql::Connection* Conn = nullptr;

    std::unique_ptr<sql::Connection> con;

    std::string Url = "tcp://127.0.0.1:3306";
    std::string User = "KYS";
    std::string Password = "KYS123456";
    std::string Schema = "RunRecordDB";

    void Connect();

public:

    DB_Connector();
};