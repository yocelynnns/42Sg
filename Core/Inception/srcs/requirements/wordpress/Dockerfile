FROM debian:bookworm

RUN apt-get update && apt-get install -y \
    php-fpm php-mysql php-cli php-curl php-gd php-mbstring php-xml php-zip wget unzip \
    && rm -rf /var/lib/apt/lists/*

# Create directory & download WordPress
RUN mkdir -p /var/www && \
    wget https://wordpress.org/latest.tar.gz -O /tmp/wordpress.tar.gz && \
    tar -xzf /tmp/wordpress.tar.gz -C /var/www/ && \
    rm /tmp/wordpress.tar.gz


# Set ownership
RUN chown -R www-data:www-data /var/www/wordpress

RUN sed -i 's|^listen = .*|listen = 9000|' /etc/php/8.2/fpm/pool.d/www.conf

WORKDIR /var/www/wordpress

EXPOSE 9000

CMD ["/usr/sbin/php-fpm8.2", "-F"]
