// Copyright 2015 Klimov Viktor, https://github.com/Vitek1425/

#ifndef REQUEST_H
#define REQUEST_H

#include <QString>

class Request
{
public:
    Request();
    QString info() const;
    void setInfo(const QString &info);
private:
    QString m_info;
};

#endif // REQUEST_H
