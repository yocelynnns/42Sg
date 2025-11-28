# NetPractice - Network Configuration Exercise

## 📋 Project Overview

NetPractice is a practical networking exercise that helps you understand TCP/IP addressing and network configuration through 10 progressively challenging levels. You'll configure small-scale networks in a simulated environment via a web interface.

## 🎯 Learning Objectives

- Understand TCP/IP addressing fundamentals
- Learn subnetting and CIDR notation
- Configure routers, switches, and hosts
- Troubleshoot network connectivity issues
- Master IP addressing and routing concepts

## 🚀 Getting Started

### Step 1: Download and Extract Files
```bash
# Download the NetPractice files from the project page
# Extract to your preferred directory
tar -xf netpractice_files.tar.gz
cd netpractice
```

### Step 2: Launch the Interface
```bash
# Open the web interface in your browser
open index.html
# Or use:
xdg-open index.html    # Linux
start index.html       # Windows
```

### Step 3: Initial Setup
1. Open `index.html` in your web browser
2. **Enter your intranet login** in the field provided
3. Click "Start" to begin the exercises

**Important**: Always enter your login to ensure your configurations are saved correctly.

## 🎮 How to Use the Interface

### Interface Components
- **Network Diagram**: Visual representation of the network topology
- **Goal Section**: Describes what needs to be configured
- **Configuration Fields**: Editable fields for IP addresses, masks, and routes
- **Buttons**:
  - `[Check again]` - Validate your configuration
  - `[Get my config]` - Download configuration file
  - `[Next level]` - Proceed to next level (appears after success)

### Workflow for Each Level
1. **Analyze the network diagram** and read the goal
2. **Configure devices** by filling in the blank fields
3. **Click `[Check again]`** to validate your configuration
4. **If successful**, click `[Get my config]` to save your solution
5. **Click `[Next level]`** to proceed

## 📁 Project Structure

After completion, your repository should contain:
```
NetPractice/
├── level1.txt
├── level2.txt
├── level3.txt
├── level4.txt
├── level5.txt
├── level6.txt
├── level7.txt
├── level8.txt
├── level9.txt
├── level10.txt
└── README.md
```

## 🛠️ Step-by-Step Guide

### Level 1-3: Basic IP Addressing
**Concepts to Master:**
- IP address classes (A, B, C)
- Subnet masks
- Default gateways
- Basic connectivity

**Common Tasks:**
- Assign IP addresses to hosts
- Set appropriate subnet masks
- Configure default gateways

**Example Solution Approach:**
```
Host A: 192.168.1.10/24
Gateway: 192.168.1.1
```

### Level 4-6: Subnetting and Routing
**Concepts to Master:**
- CIDR notation
- Subnet calculation
- Router configuration
- Static routes

**Common Tasks:**
- Create subnets from larger networks
- Configure router interfaces
- Set up routing between subnets

**Example Solution Approach:**
```
Network: 192.168.0.0/16
Subnet 1: 192.168.1.0/24
Subnet 2: 192.168.2.0/24
Router interface 1: 192.168.1.1/24
Router interface 2: 192.168.2.1/24
```

### Level 7-10: Complex Network Topologies
**Concepts to Master:**
- Multiple router configurations
- Complex routing tables
- Network address translation (NAT)
- Advanced subnetting

**Common Tasks:**
- Configure multiple routers
- Set up complex routing tables
- Handle overlapping networks
- Implement NAT where needed

## 🔧 Essential Networking Concepts

### IP Addressing Basics
- **IP Address**: Unique identifier for devices (e.g., 192.168.1.10)
- **Subnet Mask**: Defines network portion (e.g., 255.255.255.0 or /24)
- **CIDR Notation**: Compact representation (e.g., 192.168.1.0/24)

### Key Rules to Remember
1. **Same Network**: Devices can communicate directly if they're on the same subnet
2. **Different Networks**: Require a router/gateway to communicate
3. **Gateway**: Usually the first usable IP in a subnet (e.g., .1)
4. **Broadcast**: Last IP in the subnet (e.g., .255 in /24)

### Subnet Calculation Cheat Sheet
```
/24: 255.255.255.0     (256 addresses)
/25: 255.255.255.128   (128 addresses)
/26: 255.255.255.192   (64 addresses)
/30: 255.255.255.252   (4 addresses, 2 usable)
```

## 💡 Problem-Solving Strategy

### Step 1: Analyze the Topology
- Identify all devices and their connections
- Note which devices need internet access
- Understand the existing configurations

### Step 2: Plan Your IP Scheme
- Choose appropriate IP ranges
- Calculate subnet sizes needed
- Assign IP addresses systematically

### Step 3: Configure Devices
1. **Hosts**: IP address, subnet mask, default gateway
2. **Routers**: Interface IPs, routing tables
3. **Switches**: Usually no IP configuration needed

### Step 4: Test and Validate
- Use `[Check again]` frequently
- Read error messages in the log section
- Adjust configurations based on feedback

## 🎯 Evaluation Preparation

### Defense Scenario
- **3 random levels** from levels 6-10
- **15-minute time limit**
- **No external tools allowed** (basic calculator permitted)

### Practice Strategy
1. **Master levels 1-5** thoroughly
2. **Focus on levels 6-10** for defense preparation
3. **Time yourself** to ensure you can complete levels quickly
4. **Practice without notes** to simulate exam conditions

### Common Pitfalls to Avoid
- **Incorrect subnet masks**
- **Missing default gateways**
- **Wrong routing table entries**
- **IP address conflicts**
- **Forgetting to save configurations**

## 📝 Submission Requirements

### File Naming
Save each level configuration with the exact names:
- `level1.txt`
- `level2.txt`
- `level10.txt`

### Submission Process
1. Complete all 10 levels
2. Use `[Get my config]` for each level
3. Save files to your repository root
4. Ensure all 10 files are present
5. Submit to Git repository

## 🆘 Troubleshooting Common Issues

### Configuration Not Working?
- Check if IP addresses are in the same subnet
- Verify subnet masks are correct
- Ensure default gateways point to router interfaces
- Confirm routing tables have correct routes

### Can't Reach the Internet?
- Check if internet gateway is configured
- Verify NAT configuration if required
- Ensure DNS settings are correct (if applicable)

### Routing Issues?
- Confirm router interfaces have correct IPs
- Check routing tables for missing routes
- Verify that routes point to the correct next hop

## 🎓 Pro Tips

### Efficiency Tips
1. **Use consistent IP schemes** (e.g., .1 for routers, .10-.100 for hosts)
2. **Document your plan** before configuring
3. **Test incrementally** after each major change
4. **Use the log messages** to guide troubleshooting

### Conceptual Understanding
- Understand the difference between switches and routers
- Know when to use /30 subnets for point-to-point links
- Master binary to decimal conversion for subnet calculations
- Practice CIDR notation until it becomes second nature

## 🔗 Additional Resources

- **Subnet Calculator**: Useful for practice (but not during defense)
- **TCP/IP Guide**: Comprehensive networking reference
- **Practice Networks**: Create your own scenarios for extra practice

---

**Remember**: The key to success in NetPractice is understanding the fundamental concepts rather than memorizing specific solutions. Practice until you can confidently configure any network topology presented to you!
