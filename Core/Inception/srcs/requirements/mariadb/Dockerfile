FROM debian:bookworm

RUN apt-get update && DEBIAN_FRONTEND=noninteractive apt-get install -y \
    mariadb-server mariadb-client \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

# Clean up auto-initialized data to ensure runtime script does init
RUN rm -rf /var/lib/mysql/*

RUN mkdir -p /var/lib/mysql /run/mysqld && \
    chown -R mysql:mysql /var/lib/mysql /run/mysqld

COPY tools/init-db.sh /usr/local/bin/init-db.sh
RUN chmod +x /usr/local/bin/init-db.sh

RUN sed -i "s/127.0.0.1/0.0.0.0/" /etc/mysql/mariadb.conf.d/50-server.cnf

EXPOSE 3306
ENTRYPOINT ["/usr/local/bin/init-db.sh"]
