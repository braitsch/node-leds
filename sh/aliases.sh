alias ls='ls -al'
alias gl='git log --pretty=oneline'
alias nd='cd /var/node'

# start / stop node server in background #
alias nstart='sudo /etc/init.d/node-server.sh start'
alias nstop='sudo /etc/init.d/node-server.sh stop'
alias ntail='tail -n100 /var/log/node-server.log'