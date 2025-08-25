NAME = inception
COMPOSE = docker compose -f srcs/docker-compose.yml

all: build up   ## Build images and start containers

build:          ## Build only
	mkdir -p /home/ysetiawa/data/wordpress /home/ysetiawa/data/mariadb
	$(COMPOSE) build

up:             ## Start containers
	$(COMPOSE) up -d

down:           ## Stop containers
	$(COMPOSE) down

clean: down     ## Stop containers and clean volumes
	$(COMPOSE) down

fclean: clean   ## Full clean: remove volumes, images, networks
	$(COMPOSE) down -v --rmi all --remove-orphans
	sudo rm -rf /home/ysetiawa/data/wordpress
	sudo rm -rf /home/ysetiawa/data/mariadb

re: fclean all  ## Full rebuild from scratch
