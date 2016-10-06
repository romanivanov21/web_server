#!/bin/sh
# web-server daemon

NAME=web-server
PATH_DAEMON=/usr/local/bin/
DAEMON=$NAME
PATH_PIDFILE=/var/run/
PIDFILE=$NAME.pid

case "$1" in 

    start) 
        cd $PATH_DAEMON
        if [ ! -f $DAEMON ]; then
            echo "run file $DAEMON not found"
        else
            $DAEMON
        fi
        ;;

    status)
        printf "%-50s" "Checking $DAEMON..."
        cd $PATH_PIDFILE
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
        cd $PATH_PIDFILE
        kill $(cat $PIDFILE)
        printf "%-50s\n" "[ ok ] PID=$(cat $PIDFILE) kill"
        rm -f $PIDFILE
        printf "%-50s\n" "Stopping $DAEMON..."
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