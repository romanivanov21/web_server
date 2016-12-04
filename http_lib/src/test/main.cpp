/**
 *  Файл: main.cpp
 *
 *  Описание: точка входа в приложение http_test
 */

#include "unit_tests.h"

int main(int argc, char *argv[])
{
    //инициализация framework GTest
    ::testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS(); //запуск всех тестов
}