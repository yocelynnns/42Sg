#!/bin/bash
set -e

if [ ! -d "/var/lib/mysql/mysql" ]; then
    mariadbd --initialize-insecure --user=mysql
fi

mariadbd --skip-networking &
sleep 5

mysql -u root <<EOF
CREATE DATABASE IF NOT EXISTS ${MYSQL_DATABASE};
CREATE USER IF NOT EXISTS '${MYSQL_USER}'@'%' IDENTIFIED BY '${MYSQL_PASSWORD}';
GRANT ALL PRIVILEGES ON ${MYSQL_DATABASE}.* TO '${MYSQL_USER}'@'%';
FLUSH PRIVILEGES;
EOF

mysqladmin -u root shutdown
exec mariadbd
