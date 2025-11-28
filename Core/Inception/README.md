# Inception Project

A Docker-based infrastructure project that sets up a WordPress website with MariaDB database and NGINX web server using Docker containers.

## 📋 Project Overview

This project implements a small infrastructure with three main services:
- **NGINX** as the reverse proxy with TLS encryption
- **WordPress** with PHP-FPM for dynamic content
- **MariaDB** as the database backend

All services run in separate Docker containers connected through a custom Docker network.

## 🏗️ Project Structure

```
Inception/
├── Makefile
├── en.subject.pdf
├── secrets/                 
│   ├── db_password.txt
│   ├── db_root_password.txt
│   ├── wp_admin_password.txt
│   └── wp_user_password.txt
└── srcs/
    ├── docker-compose.yml
    ├── .env
    └── requirements/
        ├── mariadb/
        │   ├── Dockerfile
        │   └── tools/
        │       └── init-db.sh
        ├── nginx/
        │   ├── Dockerfile
        │   └── conf/
        │       └── nginx.conf
        └── wordpress/
            ├── Dockerfile
            └── tools/
                └── setup_wp.sh
```

## 🚀 Setup Instructions

### Prerequisites
- Virtual Machine (required by project guidelines)
- Docker installed on the VM
- Docker Compose installed
- Proper domain configuration in `/etc/hosts`

### Step-by-Step Setup

#### 1. Virtual Machine Preparation
```bash
# Ensure you're working in a VM as required
# Install Docker and Docker Compose if not already installed
sudo apt update
sudo apt install docker.io docker-compose
sudo usermod -aG docker $USER
# Log out and log back in for group changes to take effect
```

#### 2. Domain Configuration
```bash
# Edit hosts file to point your login.42.fr to localhost
sudo nano /etc/hosts
# Add line: 127.0.0.1 ysetiawa.42.fr
```

#### 3. SSL Certificate Setup
```bash
# Create SSL directory and generate certificates
mkdir -p ~/ssl
cd ~/ssl
# Generate self-signed SSL certificate (for development)
openssl req -x509 -nodes -days 365 -newkey rsa:2048 \
    -keyout ysetiawa.42.fr.key \
    -out ysetiawa.42.fr.crt \
    -subj "/C=US/ST=State/L=City/O=Organization/OU=Unit/CN=ysetiawa.42.fr"
```

#### 4. Secrets Setup
```bash
# Create secrets directory at project root (same level as srcs)
mkdir -p ../secrets
cd ../secrets

# Generate password files (replace with secure passwords)
echo "your_secure_db_password" > db_password.txt
echo "your_secure_root_password" > db_root_password.txt
echo "your_secure_admin_password" > wp_admin_password.txt
echo "your_secure_user_password" > wp_user_password.txt

# Set proper permissions
chmod 600 *.txt
```

#### 5. Environment Configuration
Create a `.env` file in the `srcs/` directory:
```bash
cd srcs
nano .env
```

Add the following content:
```env
DOMAIN_NAME=ysetiawa.42.fr
MYSQL_DATABASE=wordpress
MYSQL_USER=wordpress_user
WP_ADMIN_USER=site_manager
WORDPRESS_USER=contributor
```

#### 6. Data Directory Setup
The Makefile automatically creates the required data directories:
- `/home/ysetiawa/data/wordpress` - WordPress files
- `/home/ysetiawa/data/mariadb` - Database files

## 🛠️ Usage

### Available Make Commands

```bash
make all      # Build images and start containers (default)
make build    # Build Docker images only
make up       # Start containers in detached mode
make down     # Stop running containers
make clean    # Stop containers and clean up
make fclean   # Full clean: remove volumes, images, networks
make re       # Full rebuild from scratch
```

### Starting the Application
```bash
# From the project root directory
make
# or
make all
```

### Stopping the Application
```bash
make down
```

### Complete Cleanup
```bash
make fclean
```

## 🌐 Accessing the Application

After starting the containers:
1. Open your web browser
2. Navigate to: `https://ysetiawa.42.fr`
3. Accept the self-signed certificate warning (development only)
4. You should see the WordPress installation/setup page

## 🔧 Service Details

### Container Architecture
- **nginx**: TLS termination, reverse proxy (port 443)
- **wordpress**: PHP-FPM application (port 9000)
- **mariadb**: Database server (port 3306)

### Network Configuration
- Custom bridge network: `inception`
- Internal communication between containers
- Only NGINX exposed externally on port 443

### Volume Management
- Bind mounts for persistent data
- WordPress files: `/home/ysetiawa/data/wordpress`
- Database files: `/home/ysetiawa/data/mariadb`

## 🔒 Security Features

- TLS 1.2/1.3 encryption
- Docker secrets for sensitive data
- Environment variables for configuration
- Non-privileged container operations
- No 'admin' usernames in database
- Automatic container restart on failure

## 🧪 Evaluation Checks

### 1. Container Status Check
```bash
# Check if all containers are running
docker ps
# Expected output: mariadb, wordpress, nginx containers should be Up

# Check specific container status
docker inspect mariadb | grep Status
docker inspect wordpress | grep Status
docker inspect nginx | grep Status

# Check container restart policy
docker inspect mariadb | grep -A 5 RestartPolicy
```

### 2. Network Verification
```bash
# Check custom network exists
docker network ls
# Should show 'inception' network

# Inspect network details
docker network inspect inception

# Check containers are connected to the network
docker network inspect inception | grep -A 10 Containers

# Test connectivity between containers
docker exec nginx ping mariadb
docker exec wordpress ping mariadb
```

### 3. Volume Verification
```bash
# Check volumes are created and mounted
docker volume ls
# Should show mariadb_data and wordpress_data

# Inspect volume details
docker volume inspect srcs_mariadb_data
docker volume inspect srcs_wordpress_data

# Check bind mount locations
ls -la /home/ysetiawa/data/
# Should show mariadb and wordpress directories with content

# Verify data persistence
docker exec mariadb ls -la /var/lib/mysql
docker exec wordpress ls -la /var/www/wordpress
```

### 4. Image Verification
```bash
# Check custom images are built
docker images
# Should show: mariadb:1.0, wordpress:1.0, nginx:1.0

# Verify image details
docker image inspect mariadb:1.0
docker image inspect wordpress:1.0
docker image inspect nginx:1.0

# Check no 'latest' tags are used
docker images | grep latest
# Should not show your custom images with latest tag
```

### 5. Database Verification
```bash
# Connect to MariaDB container and check database
docker exec -it mariadb mysql -u root -p
# Enter root password from secrets/db_root_password.txt

# Inside MySQL, run these checks:
SHOW DATABASES;
# Should show your wordpress database

USE wordpress;
SHOW TABLES;
# Should show WordPress tables (wp_posts, wp_users, etc.)

SELECT user, host FROM mysql.user;
# Should show your custom users (no 'admin' in names)

SELECT user_login FROM wp_users;
# Verify no admin usernames exist
EXIT;
```

### 6. WordPress Verification
```bash
# Check WordPress files and configuration
docker exec wordpress ls -la /var/www/wordpress/
docker exec wordpress cat /var/www/wordpress/wp-config.php | grep DB_

# Check PHP-FPM is running
docker exec wordpress ps aux | grep php-fpm
```

### 7. NGINX Verification
```bash
# Check NGINX configuration
docker exec nginx nginx -t
# Should show syntax is ok

# Check NGINX is serving TLS
docker exec nginx cat /etc/nginx/conf.d/nginx.conf | grep ssl
docker exec nginx cat /etc/nginx/conf.d/nginx.conf | grep 443

# Verify TLS protocols
docker exec nginx cat /etc/nginx/conf.d/nginx.conf | grep TLS
# Should show TLSv1.2 or TLSv1.3 only
```

### 8. SSL/TLS Verification
```bash
# Test SSL connection
curl -I -k https://ysetiawa.42.fr
# Should return HTTP/1.1 200 OK or 302 redirect

# Check SSL certificate
openssl s_client -connect localhost:443 -servername ysetiawa.42.fr < /dev/null
```

### 9. Logs Inspection
```bash
# Check container logs for errors
docker logs mariadb
docker logs wordpress
docker logs nginx

# Follow logs in real-time
docker logs -f nginx
```

### 10. Restart and Resilience Test
```bash
# Test auto-restart on failure
docker stop mariadb
sleep 10
docker ps | grep mariadb
# Should show mariadb restarted automatically

# Test complete service recovery
make down && make up
# All services should start correctly
```

## 📝 Important Notes

- This project must run in a Virtual Machine
- All containers use custom-built images (no pre-built images except Alpine/Debian base)
- No infinite loop commands used in containers
- Network isolation with custom Docker network
- Proper process management (PID 1 best practices)
- No `network: host` or `--link` used
- Only NGINX exposed on port 443

## 🚨 Troubleshooting

### Common Issues

1. **SSL Certificate Errors**
   - Ensure certificates are in `~/ssl/` directory
   - Check file permissions

2. **Domain Not Resolving**
   - Verify `/etc/hosts` entry
   - Ensure domain matches your login

3. **Permission Denied**
   - Check Docker group membership
   - Verify secret file permissions (600)

4. **Container Conflicts**
   - Use `make fclean` to remove all containers and images
   - Restart Docker service if needed

### Quick Health Check Script
```bash
#!/bin/bash
echo "=== Container Status ==="
docker ps
echo -e "\n=== Network Check ==="
docker network inspect inception | grep -A 20 Containers
echo -e "\n=== Volume Check ==="
docker volume ls
```

This implementation follows all project requirements including proper Docker best practices, security measures, and the specified infrastructure architecture. The evaluation checks ensure all mandatory requirements are met.
