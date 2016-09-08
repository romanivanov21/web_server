/**
 *  Файл: types.h
 *
 *  Описание: Файл для объявления общих типов и структур
 */

#ifndef _TYPES_H_
#define _TYPES_H_

#include <string>

static int default_error_code = -1;

enum state_process { CHILD_PROCESS = 0, ERROR_PROCESS = -1 };

struct CONFIG_TYPES
{
    std::string SERVER_NAME_; //доменное имя сервера
    std::string IP_ADDRESS_;  //ip аддрес сервера
    unsigned int PORT_;       //порт на котором принимает вохдящие соедннеия сервер
    std::string DOCUMENT_ROOT_; //основное директория сервера
    std::string ERROR_LOG_;     //директрия для лог файла ошибок
    std::string ACCESS_LOG_;    //директрия для лог файла для записи успешных опреаций
};

#endif //_TYPES_H_
