/**
 * Файл: server_config.h
 *
 * Описание: класс server_config реализует функционал
 *           для работы с конфигуарационным файлом сервера,
 *           класс использует паттерн singleton
 */

#ifndef _SERVER_CONFIG_H_
#define _SERVER_CONFIG_H_

#include "embedding_pyhton_api.h"
#include "singleton_destroyer.h"
#include "config_struct.h"

#include <string>
#include <memory>

class server_config
{
 public:
    /**
     * @brief инстанцирование класса singleton
     *
     * @return ссылка на единственный экземпля класса
     */
    static server_config* get_instance() noexcept;

    /**
     * @brief загрузка и чтение конфиг файла, для разбора используется python модуль,
     *        где реализовано читение и разбор файла
     *
     * @param путь до конфиг файла
     *
     * @throw server_config_exception
     */
    void load_config_file( const std::string& file_name );

    /**
     * @brief полчение указателя на структуру c конфигом
     *
     * @return ссылку на структуру
     */
    static const config_struct* get_config() noexcept;

    server_config( const server_config& copy ) = delete;
    server_config& operator=( const server_config& copy ) = delete;

protected:
    server_config() noexcept;
    ~server_config() noexcept;

    /**
     *  @brief проверка структуры конфигурационного файла
     *
     *  @param ссылка на объект класса для встраивания программного модуля python
     *
     *  @throw server_config_exception
     */
    void check_config_struct( const std::unique_ptr<embedding_python_api>& python );

    /**
     *  @brief проверка секции 'Server' в конфигурационном файле сервера
     *
     *  @param ссылка на объект класса для встраивания программного модуля python
     *
     *  @throw server_config_exception
     */
    void check_server_struct( const std::unique_ptr<embedding_python_api>& python );

    /**
     *  @brief проверка секции 'Connection' в конфигурационном файле сервера
     *
     *  @param ссылка на объект класса для встраивания программного модуля python
     *
     *  @throw server_config_exception
     */
    void check_connection_struct( const std::unique_ptr<embedding_python_api>& python );

    /**
     *  @brief проверка секции 'Directories' в конфигурационном файле сервера
     *
     *  @param ссылка на объект класса для встраивания программного модуля python
     *
     *  @throw server_config_exception
     */
    void check_directories_struct( const std::unique_ptr<embedding_python_api>& python );

    /**
     *  @brief проверка секции 'Logs' в конфигурационном файле сервера
     *
     *  @param ссылка на объект класса для встраивания программного модуля python
     *
     *  @throw server_config_exception
     */
    void check_logs_struct( const std::unique_ptr<embedding_python_api>& python );

    /**
     *  @brief доменное имя сервера из файла конфигурации сервера
     *
     *  @param ссылка на объект класс для встраивания программного модуля python
     *
     *  @throw server_config_exception
     */
    void get_server_name( const std::unique_ptr<embedding_python_api>& python );

    /**
     *  @brief версия ip адрреса (ip_v4 или ip_v6) из файла конфигурации сервера
     *
     *  @param ссылка на объект класс для встраивания программного модуля python
     *
     *  @throw server_config_exception
     */
    void get_ip_version( const std::unique_ptr<embedding_python_api>& python );

    /**
     * @brief ip адррес из файла конфигурации сервера
     *
     * @param ссылка на объект класс для встраивания программного модуля python
     *
     * @throw server_config_exception
     */
    void get_ip_address( const std::unique_ptr<embedding_python_api>& python );

    /**
     * @brief порт сетевого создениения из файла конфигурации сервера
     *
     * @param ссылка на объект класс для встраивания программного модуля python
     *
     * @throw server_config_exception
     */
    void get_listen( const std::unique_ptr<embedding_python_api>& python );

    /**
     * @brief корневая директория сервера из файла конфигурации сервера
     *
     * @param ссылка на объект класс для встраивания программного модуля python
     *
     * @throw server_config_exception
     */
    void get_document_root( const std::unique_ptr<embedding_python_api>& python );

    /**
     * @brief директория файла лога ошибок из файла конфигурации сервера
     *
     * @param ссылка на объект класс для встраивания программного модуля python
     *
     * @throw server_config_exception
     */
    void get_error_log( const std::unique_ptr<embedding_python_api>& python );

    /**
     * @brief директория фалйа лога выполненых действий из файла конфигурации сервера
     *
     * @param ссылка на объект класс для встраивания программного модуля python
     *
     * @throw server_config_exception
     */
    void get_access_log( const std::unique_ptr<embedding_python_api>& python );

    /**
     * @brief файл конфигурации модуля CGI из файла конфигурации сервера
     *
     * @param ссылка на объект класс для встраивания программного модуля python
     *
     * @throw server_config_exception
     */
    void get_mod_CGI( const std::unique_ptr<embedding_python_api>& python );

protected:
    friend class singleton_destroyer<server_config>;

    /**
     * @brief встраиваемого python модуля директория
     *
     * @return строка с директорией
     */
    static const std::string get_py_module_path() noexcept;

protected:
    const std::string py_module_path_ = get_py_module_path(); // директория до модуля python, который реализует разбор конфиг файла
    const std::string py_module_name_ = "config_parser";      // имя python модуля
    const std::string py_class_name_ = "ConfigParser";        // название класса из python модуля

    static config_struct *cfg_;

    static server_config* instance_;
    static singleton_destroyer<server_config> destroyer_;
};

#endif //_SERVER_CONFIG_H_
