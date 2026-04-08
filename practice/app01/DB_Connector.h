#pragma once

#include <memory>
#include <string>

namespace sql
{
    class Connection;
}

class DB_Connector
{
private:
    sql::Connection* Conn = nullptr;

    std::string Url = "tcp://127.0.0.1:3306";
    std::string User = "KYS";
    std::string Password = "KYS123456";
    std::string Schema = "RunRecordDB";

public:
    DB_Connector();
    ~DB_Connector();

    bool Connect();
    void Disconnect();

    bool EnsureMemberExists(int member_id);

    bool SaveRunningRecord(
        int member_id,
        double run_time,
        double avg_speed,
        double distance,
        double calorie
    );
};