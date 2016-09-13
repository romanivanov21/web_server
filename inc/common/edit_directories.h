#ifndef _EDIT_DIRECTORIES_H_
#define _EDIT_DIRECTORIES_H_

#include <string>
#include <cassert>

class edit_directories
{
public:
    edit_directories() = default;
    ~edit_directories() = default;

    /**
    *  @brief удаляет из директории один уроветь ( один '/' из конца /.../ )
    *
    *  @param path ссылка на переменную с директорией
    */
    static void rm_last_folder( std::string &path );

    /**
     * @brief добавление в директорю один уроветь
     *
     * @param dir директория
     *
     * @param value добаляемое значение
     */
    static void add_new_folder( std::string &dir,const std::string &value );
};
#endif //_CHANGE_DIRECTORIES_H_