#include "DB_Connector.h"

#include <iostream>
#include <mysql/jdbc.h>

using namespace std;

DB_Connector::DB_Connector()
{
}

DB_Connector::~DB_Connector()
{
    Disconnect();
}

bool DB_Connector::Connect()
{
    try
    {
        sql::mysql::MySQL_Driver* Driver = sql::mysql::get_mysql_driver_instance();

        Conn = Driver->connect(Url, User, Password);
        Conn->setSchema(Schema);

        cout << "DB 연결 성공" << endl;
        return true;
    }
    catch (sql::SQLException& e)
    {
        cout << "DB 연결 실패" << endl;
        cout << "Error Code : " << e.getErrorCode() << endl;
        cout << "SQL State  : " << e.getSQLState() << endl;
        cout << "What       : " << e.what() << endl;
        return false;
    }
}

void DB_Connector::Disconnect()
{
    if (Conn != nullptr)
    {
        delete Conn;
        Conn = nullptr;
        cout << "DB 연결 종료 완료" << endl;
    }
}

bool DB_Connector::EnsureMemberExists(int member_id)
{
    if (Conn == nullptr)
    {
        cout << "DB가 연결되지 않았습니다." << endl;
        return false;
    }

    try
    {
        unique_ptr<sql::PreparedStatement> pstmt(
            Conn->prepareStatement("INSERT IGNORE INTO Member(member_id) VALUES(?)")
        );

        pstmt->setInt(1, member_id);
        pstmt->execute();

        return true;
    }
    catch (sql::SQLException& e)
    {
        cout << "Member 저장/확인 실패" << endl;
        cout << "Error Code : " << e.getErrorCode() << endl;
        cout << "SQL State  : " << e.getSQLState() << endl;
        cout << "What       : " << e.what() << endl;
        return false;
    }
}

bool DB_Connector::SaveRunningRecord(
    int member_id,
    double run_time,
    double avg_speed,
    double distance,
    double calorie
)
{
    if (Conn == nullptr)
    {
        cout << "DB가 연결되지 않았습니다." << endl;
        return false;
    }

    try
    {
        if (!EnsureMemberExists(member_id))
        {
            return false;
        }

        unique_ptr<sql::PreparedStatement> pstmt(
            Conn->prepareStatement(
                "INSERT INTO RunningRecord "
                "(member_id, run_time, avg_speed, distance, calorie) "
                "VALUES (?, ?, ?, ?, ?)"
            )
        );

        pstmt->setInt(1, member_id);
        pstmt->setDouble(2, run_time);
        pstmt->setDouble(3, avg_speed);
        pstmt->setDouble(4, distance);
        pstmt->setDouble(5, calorie);

        pstmt->execute();

        cout << "러닝 기록 저장 성공" << endl;
        return true;
    }
    catch (sql::SQLException& e)
    {
        cout << "러닝 기록 저장 실패" << endl;
        cout << "Error Code : " << e.getErrorCode() << endl;
        cout << "SQL State  : " << e.getSQLState() << endl;
        cout << "What       : " << e.what() << endl;
        return false;
    }
}