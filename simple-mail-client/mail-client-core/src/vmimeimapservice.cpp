#include "vmimeimapservice.h"

vmime::utility::url VmimeImapService::getStoreUrl() const
{
    QString imapAddress;

    if (m_userName != m_emailAddress)
    {
        imapAddress += "imaps://";
        imapAddress += m_userName.c_str();
        imapAddress += ":";
        imapAddress += QString(m_password.c_str());
        imapAddress += "@";
        imapAddress += QString(m_serverUrl.c_str());
        imapAddress += ":";
        imapAddress += QString::number(m_port);
    }
    else
    {
        imapAddress += "imaps://";
        imapAddress += m_emailAddress.c_str();
        imapAddress += ":";
        imapAddress += QString(m_password.c_str());
        imapAddress += "@";
        imapAddress += QString(m_serverUrl.c_str());
        imapAddress += ":";
        imapAddress += QString::number(m_port);
    }

    return vmime::utility::url(imapAddress.toStdString());
}
