#include "stdafx.h"

bool DataBase::Initialize()
{
    bool bReturn = false;

    if (this->Connect(gSettings.SQLHost, gSettings.SQLDatabase, gSettings.SQLUser, gSettings.SQLPassword) == true)
    {
        LogAddC(eConnect, "[MSSQL] Connected to %s", gSettings.SQLDatabase);
        bReturn = true;
    }
    else
    {
        LogAddC(eError, "[MSSQL] Failed connect to SQL");
        this->Diagnostic();
    }

    return bReturn;
}


DataBase::DataBase(void)
{
    m_SQLErrorCount = 1;
    m_AfftedRowCount = 0;
    m_Return = SQL_ERROR;

    memset(m_szTemp, 0, sizeof(m_szTemp));
    memset(m_szMsg, 0, sizeof(m_szMsg));
    memset(m_SqlState, 0, sizeof(m_SqlState));
    memset(m_Col, 0, sizeof(m_Col));
    memset(gSettings.SQLUser, 0, sizeof(gSettings.SQLUser));

    m_Return = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_hEnv);
    if(m_Return != SQL_SUCCESS && m_Return != SQL_SUCCESS_WITH_INFO)
        this->Diagnostic();

    m_Return = SQLSetEnvAttr(m_hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, SQL_IS_INTEGER);
    if(m_Return != SQL_SUCCESS && m_Return != SQL_SUCCESS_WITH_INFO)
        this->Diagnostic();
}


DataBase::~DataBase(void)
{
    if (m_hStmt)
        SQLFreeHandle(SQL_HANDLE_STMT, m_hStmt);
    if (m_hDbc)
    {
        SQLDisconnect(m_hDbc);
        SQLFreeHandle(SQL_HANDLE_DBC, m_hDbc);
    }
    if (m_hEnv)
        SQLFreeHandle(SQL_HANDLE_ENV, m_hEnv);
}


bool DataBase::Connect(const char * szHost, const char * szDataBase, const char * szUser, const char * szPassword)
{
    bool bReturn = false;
    SQLSMALLINT cbOutCon = 0;
    SQLCHAR		InCon[255] = "";
    SQLCHAR		OutCon[255] = "";

    m_Return = SQLAllocHandle(SQL_HANDLE_DBC, m_hEnv, &m_hDbc);

    if(m_Return != SQL_SUCCESS && m_Return != SQL_SUCCESS_WITH_INFO)
        this->Diagnostic();

    wsprintf(reinterpret_cast<char *>(InCon), "DRIVER=SQL Server;Server=%s;DATABASE=%s;UID=%s;PWD=%s;", szHost,szDataBase, szUser, szPassword);
    OnMessage(reinterpret_cast<char *>(InCon));

    SQLSetConnectAttr(m_hDbc, SQL_LOGIN_TIMEOUT, (SQLPOINTER)15, 0);
    m_Return = SQLDriverConnect(m_hDbc, NULL, InCon, sizeof(InCon), OutCon, sizeof(OutCon), &cbOutCon, SQL_DRIVER_NOPROMPT);

    if (m_Return == SQL_SUCCESS || m_Return == SQL_SUCCESS_WITH_INFO)
    {
        m_Return = SQLAllocHandle(SQL_HANDLE_STMT, m_hDbc, &m_hStmt);

        if (m_Return == SQL_SUCCESS || m_Return == SQL_SUCCESS_WITH_INFO)
        {
            m_strHost = szHost;
            m_strDataBase = szDataBase;
            m_strUser = szUser;
            m_strPassword = szPassword;
            bReturn = true;
            return bReturn;
        }
        else
        {
            m_hStmt = 0;
            this->Diagnostic();
        }
    }
    this->Diagnostic();

    return bReturn;
}


bool DataBase::Connect(const char * szDnsName)
{
    bool bReturn = false;

    SQLSMALLINT cbOutCon = 0;
    SQLCHAR InCon[255] = { 0 };
    SQLCHAR OutCon[255] = { 0 };

    m_Return = SQLAllocHandle(SQL_HANDLE_DBC, m_hEnv, &m_hDbc);

    if(m_Return != SQL_SUCCESS && m_Return != SQL_SUCCESS_WITH_INFO)
        this->Diagnostic();

    wsprintf(reinterpret_cast<char *>(InCon), "DATABASE=%s;DRIVER=SQL Server;Server=(local);", szDnsName);
    OnMessage(reinterpret_cast<char *>(InCon));

    SQLSetConnectAttr(m_hDbc, SQL_LOGIN_TIMEOUT, (SQLPOINTER)15, 0);
    m_Return = SQLDriverConnect(m_hDbc, NULL, InCon, sizeof(InCon), OutCon,sizeof(OutCon), &cbOutCon, SQL_DRIVER_NOPROMPT);

    if (m_Return == SQL_SUCCESS || m_Return == SQL_SUCCESS_WITH_INFO)
    {
        m_Return = SQLAllocHandle(SQL_HANDLE_STMT, m_hDbc, &m_hStmt);

        if (m_Return == SQL_SUCCESS || m_Return == SQL_SUCCESS_WITH_INFO)
        {
            m_strDnsName = szDnsName;
            bReturn = true;
        }
        else
        {
            m_hStmt = 0;
            this->Diagnostic();
        }
    }
    if(bReturn == false)
        this->Diagnostic();

    return bReturn;
}


bool DataBase::Reconnect()
{
    if (m_strDnsName.length() <= 0)
        return Connect(m_strHost.c_str(), m_strDataBase.c_str(), m_strUser.c_str(), m_strPassword.c_str());
    else
        return Connect(m_strDnsName.c_str());
}


bool DataBase::Exec(const char * szQuery)
{
    bool bReturn = false;
    if(m_hStmt != 0)
    {
        Clear();

        LogAddC(eNormal, "[MSSQL] %s", szQuery);

        m_Return = SQLExecDirect(m_hStmt, (SQLCHAR*)szQuery, SQL_NTS);

        OnQuery(szQuery);

        if (m_Return == SQL_SUCCESS || m_Return == SQL_SUCCESS_WITH_INFO)
        {
            SQLRowCount(m_hStmt, &m_AfftedRowCount);
            SQLNumResultCols(m_hStmt, &m_nCol);

            if (m_nCol > MAXCOL)
                LogAddC(eError, "[MSSQL] Columns number exceeded the maximum number (%d)", m_nCol);
            else if (m_nCol <= 0)
            {
                Clear();
                bReturn = true;
            }
            else
            {
                for (SQLSMALLINT i = 0; i < m_nCol; ++i)
                {
                    SQLBindCol(m_hStmt, i + 1, SQL_C_CHAR, m_Col[i], 255, &m_lCol[i]);
                    SQLDescribeCol(m_hStmt, i + 1, m_ColName[i], 30, NULL, NULL, NULL, NULL, NULL);
                }

                bReturn = true;
            }
        }
        else
            Diagnostic(szQuery);
    }
    return bReturn;
}


bool DataBase::ExecFormat(const char * szQuery, ...)
{
    va_start(m_pArgs, szQuery);
    vsprintf(m_szTemp, szQuery, m_pArgs);
    va_end(m_pArgs);

    return Exec(m_szTemp);
}


int DataBase::FindCol(const char * szName)
{
    int iReturn = -1;

    if(szName == NULL)
        return iReturn;

    if (m_eReturn != SQL_SUCCESS && m_eReturn != SQL_SUCCESS_WITH_INFO)
        return iReturn;

    for (int i = 0; i < m_nCol; ++i)
    {
        if (!_stricmp(szName, (LPCTSTR)m_ColName[i]))
        {
            iReturn = i;
            break;
        }
    }

    return iReturn;
}


int DataBase::GetInt(int nCol)
{
    int iReturn = CQUERYNOCOL;

    if (nCol <= m_nCol)
    {
        if (m_lCol[nCol] != SQL_NULL_DATA)
            iReturn = atoi(m_Col[nCol]);
        else
            iReturn = CQUERYNULL;
    }

    return iReturn;
}


int DataBase::GetInt(const char *sCol)
{
    int iReturn = CQUERYNOCOL;
    int n = FindCol(sCol);

    if (n != -1)
        iReturn = GetInt(n);

    return iReturn;
}


__int64 DataBase::GetInt64(int nCol)
{
    __int64 iReturn = CQUERYNOCOL;

    if (nCol <= m_nCol)
    {
        if (m_lCol[nCol] != SQL_NULL_DATA)
            iReturn = _atoi64(m_Col[nCol]);
        else
            iReturn = CQUERYNULL;
    }

    return iReturn;
}


__int64 DataBase::GetInt64(const char *sCol)
{
    __int64 iReturn = CQUERYNOCOL;
    int n = FindCol(sCol);

    if (n != -1)
        iReturn = GetInt64(n);

    return iReturn;
}


float DataBase::GetFloat(int nCol)
{
    float fReturn = CQUERYNOCOL;

    if (nCol <= m_nCol)
    {
        if (m_lCol[nCol] != SQL_NULL_DATA)
            fReturn = static_cast<float>(atof(m_Col[nCol]));
        else
            fReturn = CQUERYNULL;
    }

    return fReturn;
}


float DataBase::GetFloat(const char *sCol)
{
    float fReturn = CQUERYNOCOL;
    int n = FindCol(sCol);

    if (n != -1)
        fReturn = GetFloat(n);

    return fReturn;
}


void DataBase::GetStr(int nCol, char *buf)
{
    if (nCol > m_nCol)
    {
        buf[0] = '\0';
        return;
    }

    if (m_lCol[nCol] == SQL_NULL_DATA)
    {
        buf[0] = '\0';
    }
    else
    {
        strcpy(buf, m_Col[nCol]);
    }
}


void DataBase::GetStr(const char *sCol, char *buf)
{
    int n = FindCol(sCol);

    if (n == -1)
        buf[0] = '\0';
    else
        GetStr(n, buf);
}

int DataBase::GetAsBinary(LPTSTR lpszStatement, LPBYTE OUT lpszReturnBuffer)
{
    int bRet = -1;

    if(m_hStmt != 0)
    {
        SQLCHAR * pSQLBuf = NULL;
        SQLINTEGER BufLen = 0;
        SQLCHAR SQLBinary[10000] = "";
        SQLINTEGER lOfs = 0;
        SQLINTEGER SQLLen = -1;

        Clear();

        OnQuery(lpszStatement);
        m_Return = SQLExecDirect(m_hStmt, reinterpret_cast<SQLTCHAR *>(lpszStatement), SQL_NTS);

        if (m_Return != SQL_SUCCESS && m_Return != SQL_SUCCESS_WITH_INFO)
        {
            Diagnostic();
            return bRet;
        }

        while (true)
        {
            m_Return = SQLFetch(m_hStmt);

            if (m_Return == SQL_NO_DATA || m_Return == SQL_NULL_DATA)
                break;

            pSQLBuf = lpszReturnBuffer;

            while (true)
            {
                m_Return = SQLGetData(m_hStmt, 1, SQL_C_BINARY, SQLBinary, sizeof(SQLBinary), &SQLLen);

                if (m_Return == SQL_NO_DATA )
                    break;

                if (SQLLen == -1)
                {
                    Clear();
                    bRet = 0;
                    return bRet;
                }

                if (m_Return == SQL_SUCCESS || m_Return == SQL_SUCCESS_WITH_INFO)
                    BufLen = SQLLen;
                else
                    BufLen = sizeof(SQLBinary);

                lOfs += BufLen;
                memcpy(pSQLBuf, SQLBinary, BufLen);
                pSQLBuf = &pSQLBuf[lOfs];
            }
        }
        return BufLen;
    }

    return bRet;
}


void DataBase::SetAsBinary(LPTSTR lpszStatement, LPBYTE lpBinaryBuffer, SQLUINTEGER BinaryBufferSize)
{
    if(m_hStmt != 0)
    {
        Clear();

        SQLINTEGER cbValueSize = -0x64 - BinaryBufferSize;
        SQLPOINTER pToken = NULL;
        SQLCHAR cBUFFER[10000] = "";
        SQLRETURN Result = SQL_ERROR;

        SQLBindParameter(m_hStmt, 1, SQL_PARAM_INPUT,SQL_C_BINARY, SQL_LONGVARBINARY, BinaryBufferSize, 0, (SQLPOINTER)1, 0, &cbValueSize);

        OnQuery(lpszStatement);
        m_Return = SQLExecDirect(m_hStmt, reinterpret_cast<SQLTCHAR *>(lpszStatement), SQL_NTS);

        if(m_Return != SQL_SUCCESS && m_Return != SQL_SUCCESS_WITH_INFO)
            this->Diagnostic();

        Result = SQLParamData(m_hStmt, &pToken);

        while (Result == SQL_NEED_DATA)
        {
            memcpy(cBUFFER, lpBinaryBuffer, BinaryBufferSize);
            SQLPutData(m_hStmt, cBUFFER, BinaryBufferSize);
            Result = SQLParamData(m_hStmt, &pToken);
        }

        SQLParamData(m_hStmt, &pToken);
        Clear();
    }
}

