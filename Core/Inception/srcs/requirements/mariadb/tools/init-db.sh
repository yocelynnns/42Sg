#!/bin/bash
set -e

MYSQL_ROOT_PASSWORD=$(cat /run/secrets/db_root_password)
MYSQL_PASSWORD=$(cat /run/secrets/db_password)

# Initialize MariaDB data dir if empty
if [ ! -d "/var/lib/mysql/mysql" ]; then
    echo "Initializing database..."
    mysql_install_db --user=mysql --ldata=/var/lib/mysql > /dev/null
fi

# Start mysqld in background to run setup commands
mysqld_safe --datadir=/var/lib/mysql &

# Wait until MariaDB is ready
until mysqladmin ping --silent; do
    echo "Waiting for MariaDB to be ready..."
    sleep 2
done

echo "Creating database and user..."
mysql -u root <<EOF
CREATE DATABASE IF NOT EXISTS ${MYSQL_DATABASE};
CREATE USER IF NOT EXISTS '${MYSQL_USER}'@'%' IDENTIFIED BY '${MYSQL_PASSWORD}';
GRANT ALL PRIVILEGES ON ${MYSQL_DATABASE}.* TO '${MYSQL_USER}'@'%';
ALTER USER 'root'@'localhost' IDENTIFIED BY '${MYSQL_ROOT_PASSWORD}';
FLUSH PRIVILEGES;
EOF

# Bring MariaDB to foreground (PID 1)
wait
