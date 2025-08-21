NAME = inception
COMPOSE = docker-compose -f srcs/docker-compose.yml

all: up

up:
	$(COMPOSE) up -d --build

down:
	$(COMPOSE) down

clean: down
	docker system prune -af --volumes

fclean: clean
	docker volume rm $$(docker volume ls -q) || true
	docker network rm $$(docker network ls -q) || true

re: fclean all
