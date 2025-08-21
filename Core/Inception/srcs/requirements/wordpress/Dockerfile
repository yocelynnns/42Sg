FROM debian:bookworm

RUN apt-get update && apt-get install -y \
    php-fpm php-mysql php-cli php-curl php-gd php-mbstring php-xml php-zip \
    wget unzip \
    && rm -rf /var/lib/apt/lists/*

# Create the target directory
RUN mkdir -p /var/www

# Download WordPress and extract
RUN wget https://wordpress.org/latest.tar.gz -O /tmp/wordpress.tar.gz \
    && tar -xzf /tmp/wordpress.tar.gz -C /var/www/ \
    && rm /tmp/wordpress.tar.gz

# Set permissions
RUN chown -R www-data:www-data /var/www/wordpress

WORKDIR /var/www/wordpress
EXPOSE 9000

CMD ["php-fpm7.4", "-F"]
