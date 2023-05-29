#pragma once
#include <stdio.h>
#include <sql.h>
#include <sqlext.h>
#include <afxdb.h>

class CDBConnect {

public:
	SQLHENV hEnv;    // Environment Handle
	SQLHDBC hDbc;    // Connection Handle
	SQLHSTMT hStmt;	// Statement Handle

	const char* dataSourceName;
	const char* serverId;
	const char* serverPw;
	
	CDBConnect();	
	bool db_connect();
	void db_disconnect();
};
