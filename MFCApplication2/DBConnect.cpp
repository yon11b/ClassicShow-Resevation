#include "pch.h"
#include <Windows.h>
#include <sql.h>
#include <sqlext.h>
#include "DBConnect.h"

CDBConnect::CDBConnect() {
	hEnv = NULL;	// Environment Handle
	hDbc = NULL;	// Connection Handle

	dataSourceName = "DB_Server02";
	serverId = "CHOPIN";
	serverPw = "1234";
}

bool CDBConnect::db_connect()
{
	SQLRETURN Ret;
	
	// Allocate the Environment Handle (hEnv)
	if (SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &hEnv) != SQL_SUCCESS)
	{ 
		return false;
	}

	// Set attributes of the Environment Handle (hEnv)
	if (SQLSetEnvAttr(hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER) != SQL_SUCCESS)
	{
		return false;
	}

	// Allocate the Connection Handle (hDbc)
	if (SQLAllocHandle(SQL_HANDLE_DBC, hEnv, &hDbc) != SQL_SUCCESS)
	{
		return false;
	}

	// Connect to the SQL Sever with ODBC name, ID, and PW
	Ret = SQLConnect(hDbc, (SQLCHAR*)dataSourceName, SQL_NTS, (SQLCHAR*)serverId, SQL_NTS, (SQLCHAR*)serverPw, SQL_NTS);

	if ((Ret != SQL_SUCCESS) && (Ret != SQL_SUCCESS_WITH_INFO))
	{
		return false;
	}

	return true;
}

void CDBConnect::db_disconnect()
{
	SQLDisconnect(hDbc);					// Disconnect from the SQL Server
	SQLFreeHandle(SQL_HANDLE_DBC, hDbc);	// Free the Connection Handle
	SQLFreeHandle(SQL_HANDLE_ENV, hEnv);	// Free the Environment Handle
}
