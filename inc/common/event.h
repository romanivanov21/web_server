/**
 *  Файл: event.h
 *
 *  Описание: обявление перечисления событий
 */

#ifndef _EVENT_H_
#define _EVENT_H_

enum event
{
    TEST = 0,
    END_EVENTS   //должен быть последним элементом перечисления,
                 //для проверки в коде валидности события
};

#endif //_EVENT_H_