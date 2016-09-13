/**
 *  Файл: tcp_connection.h
 *
 *  Описание: класс для работы с сетевым соединением, передающий
 *            данные на транспортном уровене по протоколу tcp
 */

#include "connection.h"

class tcp_connection : public connection
{
 public:
    tcp_connection();
    ~tcp_connection();
};