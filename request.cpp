// Copyright 2015 Klimov Viktor, https://github.com/Vitek1425/

#include "request.h"

Request::Request()
{

}
QString Request::info() const
{
    return m_info;
}

void Request::setInfo(const QString &info)
{
    m_info = info;
}


