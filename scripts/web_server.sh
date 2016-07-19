#!/usr/bin/env bash

PID_FILE=""
CONFIG_FILE=""
ERROR_LOG_FILE=""
ACCESS_LOG_FILE=""

server_start()
{
    echo "start"
}

server_stop()
{
    #if [ -e ${PID_FILE} ]
    #   then
    #           _pid=$(cat ${PID_FILE})
    #           kill $_pid
    #           rt=$?
    #           if [ "$rt" == "0" ]
    #           then
    #                    echo "Daemon stop"
    #            else
    #                    echo "Error stop daemon"
    #            fi
    #    else
    #            echo "Daemon is't running"
    #    fi
    echo "stop"
}

server_restart()
{
    server_stop
    server_start
}

usage()
{
    echo "$0(start|stop|restart)"
}

#проверка переменных окружений и нужных файлов
init()
{
    PID_FILE="/etc/init.d/web_server/pid"
}

get_config()
{
    echo "get config"
}

#инициализация
if ! [ init ]; then
    echo "install error"

    exit
    fi

case $1 in
    "start" )
            server_start
            ;;
    "stop" )
            server_stop
            ;;
    "restart" )
            server_restart
            ;;
    *)
            usage
            ;;
esac
