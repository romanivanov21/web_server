#!/bin/sh

#The project name
PROJECT="web_server"

#The pid file name
PIDFILE="$PROJECT.pid"

#pid file directory 
PIDFILE_DIR="/var/run/"

#run file directory
PROJECT_DIR="/usr/local/bin/"

#user signal for stopped programm
SIGUSR1="-10"

case "$1" in 

    start) 
        cd $PROJECT_DIR
        if [ -x $PROJECT ]; then
            $PROJECT
        else
            echo "run file $PROJECT not found"
        fi
        ;;

    status)
        printf "%-50s" "Checking $PROJECT..."
        cd $PIDFILE_DIR
        if [ -f $PIDFILE ]; then
            PID=$(cat $PIDFILE)
            if [ -z "`ps axf | grep ${PID} | grep -v grep`" ]; then
                printf "%s\n" "Process dead but pidfile exists"
            else
                echo "Running"
            fi
        else
            printf "%s\n" "Service not running"
        fi
        ;;

    stop) 
        cd $PIDFILE_DIR
        if [ -f $PIDFILE ]; then
            kill $SIGUSR1 $(cat $PIDFILE)
            rm -f $PIDFILE
        else 
            echo "$PIDFILE: No such file"
        fi
        ;;

    restart)
        sh $0 stop
        sh $0 start
        ;;

    *)
        echo "Usage: $0 {status|start|stop|restart}"
        exit 1

esac

exit 0