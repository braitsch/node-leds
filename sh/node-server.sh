#! /bin/sh
# /etc/init.d/node-server

### BEGIN INIT INFO
# Provides:          node-server
# Required-Start:    $remote_fs $syslog
# Required-Stop:     $remote_fs $syslog
# Default-Start:     2 3 4 5
# Default-Stop:      0 1 6
# Short-Description: Simple script to start a program at boot
### END INIT INFO

# If you want a command to always run, put it here

# Carry out specific functions when asked to by the system
case "$1" in
  start)
    echo "* starting node-server * "
    echo "* starting node-server * [`date`]" >> /var/log/node-server.log
	# the trailing ampersand forces the program to run in the background #
    /usr/local/bin/node /var/node/app.js >> /var/log/node-server.log 2>&1&
    ;;
  stop)
    echo "* stopping node-server * "
    echo "* stopping node-server * [`date`]" >> /var/log/node-server.log
    # kill application you want to stop
    killall /usr/local/bin/node
    ;;
  *)
    echo "Usage: /etc/init.d/node-server {start|stop}"
    exit 1
    ;;
esac

exit 0