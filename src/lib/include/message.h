#pragma once

enum MSGID
{
    MSGID_LOGIN = 1,
    MSGID_LOGIN_ACK,
};

struct MSGHEAD
{
    MSGHEAD()
    {
        m_cmd = m_dataLen = 0;
    }
    int    m_cmd;
    int    m_dataLen;
};

struct LOGIN_MSG : public MSGHEAD
{
    LOGIN_MSG()
    {
        m_cmd = MSGID_LOGIN;
        m_dataLen = sizeof(LOGIN_MSG) - sizeof(MSGHEAD);
    }
    int     age;
    char    name[256];
};


struct LOGIN_MSG_ACK : public MSGHEAD
{
    LOGIN_MSG_ACK()
    {
        m_cmd = MSGID_LOGIN_ACK;
        m_dataLen = sizeof(LOGIN_MSG_ACK) - sizeof(MSGHEAD);
    }
    int     ret;
};

