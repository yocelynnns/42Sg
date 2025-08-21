FROM debian:bookworm

RUN apt-get update && apt-get upgrade -y \
    && apt-get install -y mariadb-server \
    && rm -rf /var/lib/apt/lists/*

COPY tools/init-db.sh /usr/local/bin/
RUN chmod +x /usr/local/bin/init-db.sh

EXPOSE 3306

CMD ["bash", "/usr/local/bin/init-db.sh"]
