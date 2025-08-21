NAME = inception
COMPOSE = docker compose -f srcs/docker-compose.yml

all: up

up:
	$(COMPOSE) up -d --build

down:
	$(COMPOSE) down

clean: down

fclean: clean
	docker volume rm $$(docker volume ls -q) || true
	docker network rm inception || true
	sudo rm -rf /home/ysetiawa/data/wordpress/*
	sudo rm -rf /home/ysetiawa/data/mariadb/*

re: fclean all
