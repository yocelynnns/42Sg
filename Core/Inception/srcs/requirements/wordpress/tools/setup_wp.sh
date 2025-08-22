#!/bin/bash
set -e

# Wait for MariaDB to be ready
until mysqladmin ping -h"$WORDPRESS_DB_HOST" --silent; do
    echo "Waiting for MariaDB..."
    sleep 2
done

cd /var/www/wordpress

# Download WordPress core if not present
if [ ! -f wp-config.php ]; then
    echo "Downloading WordPress..."
    wp core download --allow-root

    echo "Configuring wp-config.php..."
    wp config create \
        --allow-root \
        --dbname="$WORDPRESS_DB_NAME" \
        --dbuser="$WORDPRESS_DB_USER" \
        --dbpass="$(cat $WORDPRESS_DB_PASSWORD_FILE)" \
        --dbhost="$WORDPRESS_DB_HOST"

    echo "Installing WordPress..."
    wp core install \
        --allow-root \
        --url="https://${DOMAIN_NAME}" \
        --title="Inception Site" \
        --admin_user="$WORDPRESS_ADMIN_USER" \
        --admin_password="$(cat $WORDPRESS_ADMIN_PASSWORD_FILE)" \
        --admin_email="admin@${DOMAIN_NAME}"

    echo "Creating normal user..."
    wp user create \
        "$WORDPRESS_USER" "user@${DOMAIN_NAME}" \
        --user_pass="$(cat $WORDPRESS_USER_PASSWORD_FILE)" \
        --allow-root
else
    echo "WordPress already set up."
fi

exec php-fpm8.2 -F
