FROM debian:bookworm

RUN apt-get update && apt-get install -y \
    php-fpm php-mysql php-cli curl mariadb-client less unzip \
    && rm -rf /var/lib/apt/lists/*

# Install WP-CLI
RUN curl -O https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar \
    && chmod +x wp-cli.phar \
    && mv wp-cli.phar /usr/local/bin/wp

WORKDIR /var/www/wordpress

COPY tools/setup_wp.sh /usr/local/bin/setup_wp.sh
RUN chmod +x /usr/local/bin/setup_wp.sh

RUN sed -i 's|^listen = .*|listen = 9000|' /etc/php/8.2/fpm/pool.d/www.conf

EXPOSE 9000
CMD ["php-fpm8.2", "-F"]
