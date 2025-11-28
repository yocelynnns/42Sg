# Born2beRoot

**System Administration Exercise** - Setting up a secure Debian/Rocky Linux server with strict security policies and system monitoring.

## Project Information

| Field | Description |
|-------|-------------|
| **Project Name** | Born2beRoot |
| **Files to Submit** | `signature.txt` (virtual disk SHA1 signature) |
| **Virtualization** | VirtualBox or UTM required |
| **OS Choice** | Debian Stable (recommended) or Rocky Linux |
| **Submission** | Only `signature.txt` file required |

## 🎯 Project Overview

This project introduces you to system administration by creating a secure virtual machine with:
- **Encrypted LVM partitions**
- **Strict password policies** 
- **Firewall configuration** (UFW/Firewalld)
- **SSH service on port 4242**
- **Sudo security hardening**
- **System monitoring script**

## 📋 Mandatory Requirements Checklist

### ✅ Virtual Machine Setup
- [ ] **OS**: Latest stable Debian or Rocky Linux
- [ ] **No graphical interface** (X.org forbidden)
- [ ] **Encrypted LVM** with at least 2 partitions
- [ ] **Hostname**: `yourlogin42` (e.g., `john42`)

### ✅ Security Configuration
- [ ] **SSH** running on port **4242** only
- [ ] **Root SSH login disabled**
- [ ] **Firewall active** (UFW for Debian, Firewalld for Rocky)
- [ ] Only port **4242** open

### ✅ User & Password Policies
- [ ] **Strong password policy**:
  - Expires every 30 days
  - Minimum 2 days between changes
  - 7-day warning before expiration
  - Minimum 10 characters
  - Upper + lower case + number
  - Max 3 consecutive identical characters
  - No username in password
  - 7+ characters different from old password
- [ ] **User account** with your login name
- [ ] User belongs to `user42` and `sudo` groups

### ✅ Sudo Configuration
- [ ] **3 attempts max** for sudo authentication
- [ ] **Custom error message** for failed attempts
- [ ] **Sudo logging** in `/var/log/sudo/`
- [ ] **TTY mode enabled**
- [ ] **Restricted PATH** for sudo commands

### ✅ Monitoring Script
- [ ] **monitoring.sh** bash script
- [ ] **Runs every 10 minutes** at startup
- [ ] **Displays system info** on all terminals
- [ ] **No errors** visible during execution

## 🛠️ Step-by-Step Implementation Guide

### 1. Virtual Machine Creation
```bash
# Download Debian/Rocky ISO
# Create VM with:
# - 20GB+ disk space
# - 2GB+ RAM  
# - Network: NAT
```

### 2. Partitioning with Encrypted LVM
**During OS installation:**
- Choose "Manual partitioning"
- Create encrypted LVM with:
  - `/boot` partition (500MB)
  - LVM physical volume on encrypted partition
  - Logical volumes: `root`, `swap`, `home`

### 3. Post-Installation Configuration

#### Update System
```bash
sudo apt update && sudo apt upgrade -y  # Debian
sudo dnf update -y                     # Rocky
```

#### Configure Hostname
```bash
sudo hostnamectl set-hostname yourlogin42
```

#### Install Required Packages
```bash
# Debian
sudo apt install -y ufw sudo

# Rocky  
sudo dnf install -y firewalld sudo policycoreutils-python-utils
```

### 4. Security Hardening

#### SSH Configuration
```bash
sudo nano /etc/ssh/sshd_config
```
```conf
Port 4242
PermitRootLogin no
PasswordAuthentication yes
```

#### Firewall Setup
```bash
# Debian (UFW)
sudo ufw allow 4242
sudo ufw enable

# Rocky (Firewalld)
sudo firewall-cmd --permanent --add-port=4242/tcp
sudo firewall-cmd --reload
```

### 5. Password Policy

#### Edit Password Policies
```bash
sudo nano /etc/login.defs
```
```conf
PASS_MAX_DAYS 30
PASS_MIN_DAYS 2
PASS_WARN_AGE 7
```

#### Install Password Quality Module
```bash
# Debian
sudo apt install -y libpam-pwquality

# Rocky
sudo dnf install -y libpwquality
```

#### Configure PAM
```bash
sudo nano /etc/pam.d/common-password  # Debian
sudo nano /etc/pam.d/system-auth     # Rocky
```
Add:
```
password requisite pam_pwquality.so retry=3 minlen=10 ucredit=-1 lcredit=-1 dcredit=-1 maxrepeat=3 reject_username difok=7 enforce_for_root
```

### 6. User & Sudo Configuration

#### Create User and Groups
```bash
sudo adduser yourlogin
sudo usermod -aG sudo yourlogin
sudo groupadd user42
sudo usermod -aG user42 yourlogin
```

#### Configure Sudo
```bash
sudo visudo
```
```conf
# Error message
Defaults    badpass_message="Custom error message: incorrect password"

# Logging
Defaults    logfile="/var/log/sudo/sudo.log"
Defaults    log_input, log_output

# Security
Defaults    requiretty
Defaults    secure_path="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/snap/bin"

# Password attempts
Defaults    passwd_tries=3
```

### 7. Monitoring Script

Create `/usr/local/bin/monitoring.sh`:
```bash
#!/bin/bash

# Architecture and Kernel
ARCH=$(uname -a)

# CPU Information
CPU_PHYSICAL=$(grep "physical id" /proc/cpuinfo | sort | uniq | wc -l)
CPU_VIRTUAL=$(grep "^processor" /proc/cpuinfo | wc -l)

# Memory Usage
MEM_USED=$(free -m | awk 'NR==2{printf "%s/%sMB (%.2f%%)", $3,$2,$3*100/$2 }')

# Disk Usage
DISK_USED=$(df -h | awk '$NF=="/"{printf "%d/%dGB (%s)", $3,$2,$5}')

# CPU Load
CPU_LOAD=$(top -bn1 | grep load | awk '{printf "%.2f%%", $(NF-2)}')

# Last Boot
LAST_BOOT=$(who -b | awk '{print $3 " " $4}')

# LVM Status
LVM_STATUS=$(if [ $(lsblk | grep "lvm" | wc -l) -gt 0 ]; then echo yes; else echo no; fi)

# Connections
TCP_CONNECTIONS=$(ss -ta | grep ESTAB | wc -l)

# Users
USER_LOG=$(users | wc -w)

# Network
IP=$(hostname -I)
MAC=$(ip link show | awk '/link\/ether/ {print $2}')

# Sudo Commands
SUDO_CMDS=$(journalctl _COMM=sudo | grep "COMMAND" | wc -l)

# Display message
wall " 
#Architecture: $ARCH
#CPU physical: $CPU_PHYSICAL
#vCPU: $CPU_VIRTUAL
#Memory Usage: $MEM_USED
#Disk Usage: $DISK_USED
#CPU load: $CPU_LOAD
#Last boot: $LAST_BOOT
#LVM use: $LVM_STATUS
#Connections TCP: $TCP_CONNECTIONS ESTABLISHED
#User log: $USER_LOG
#Network: IP $IP ($MAC)
#Sudo: $SUDO_CMDS cmd
"
```

Make executable and schedule:
```bash
sudo chmod +x /usr/local/bin/monitoring.sh
sudo crontab -e
```
Add:
```cron
*/10 * * * * /usr/local/bin/monitoring.sh
```

## 🔧 Verification Commands

### Check System Configuration
```bash
# Check partitions
lsblk

# Check SSH status
ss -tunlp | grep 4242

# Check firewall
sudo ufw status          # Debian
sudo firewall-cmd --list-all  # Rocky

# Check password policy
chage -l yourlogin

# Check SELinux/AppArmor
sestatus                 # Rocky
aa-status               # Debian
```

### Get Virtual Disk Signature
```bash
# Navigate to VM folder, then:
shasum your_vm_name.vdi    # VirtualBox
shasum disk-0.qcow2        # UTM (Mac M1)

# Save output to signature.txt in your Git repo
```

## 🎯 Demonstration Guide

During evaluation, be prepared to:

1. **Show running services**: SSH, firewall, monitoring script
2. **Create new user** and assign to groups
3. **Explain password policy** and sudo configuration
4. **Modify hostname** on the fly
5. **Stop monitoring script** without editing it
6. **Answer questions** about your OS choice and configuration

## 📝 Common Evaluation Questions

- **Difference between apt and aptitude?**
- **What is SELinux/AppArmor?**
- **Why use LVM with encryption?**
- **How does the password policy work?**
- **Explain the sudo security measures**

## ⚠️ Important Notes

- **NO snapshots** allowed - will result in grade 0
- **NO graphical interface** - terminal only
- **Submit only signature.txt** - not the entire VM
- **Test thoroughly** before evaluation
- **Document your process** for future reference

---

**Remember**: This VM will be the foundation for your future system administration knowledge. Take the time to understand each step thoroughly!
