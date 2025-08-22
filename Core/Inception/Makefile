NAME = inception
COMPOSE = docker compose -f srcs/docker-compose.yml

all: up

up:
	$(COMPOSE) up -d --build

down:
	$(COMPOSE) down

clean: down

fclean: clean
# 	docker volume ls -q | xargs -r docker volume rm
# 	docker network ls | grep -q inception && docker network rm inception || true
	$(COMPOSE) down -v --rmi all --remove-orphans
	
	sudo rm -rf /home/ysetiawa/data/wordpress/*
	sudo rm -rf /home/ysetiawa/data/mariadb/*

re: fclean all
