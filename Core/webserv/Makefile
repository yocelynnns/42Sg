# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsechen <tsechen@student.42singapore.sg    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/29 16:17:01 by tsechen           #+#    #+#              #
#    Updated: 2025/11/19 16:26:35 by tsechen          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME            := webserv

# Compiler flags
CXX             := c++
RM              := rm -f
CXXFLAGS        := -std=c++98 -Wall -Wextra -Werror -pedantic -g
DEPFLAGS        := -MMD -MP

# Project root
PROJECTDIR      := .

# Other Directories  
OBJ_DIR         := ./obj
BIN_DIR         := .
DEP_DIR         := .deps

# Main source
MAIN_SRC        := main
MAIN_DIR        := $(PROJECTDIR)
MAIN_FILES      := $(addprefix $(MAIN_DIR)/, $(addsuffix .cpp, $(MAIN_SRC)))
MAIN_OBJS       := $(MAIN_FILES:$(MAIN_DIR)/%.cpp=$(OBJ_DIR)/%.o)
MAIN_DEPS       := $(MAIN_OBJS:$(OBJ_DIR)/%.o=$(DEP_DIR)/%.d)

# Project files by module - Updated to match revised file structure
M00_SRC         := Server EventLoop Connection Socket ConnectionPool NonBlockingIO
M00_DIR         := $(PROJECTDIR)/00_core
M00_FILES       := $(addprefix $(M00_DIR)/, $(addsuffix .cpp, $(M00_SRC)))
M00_OBJS        := $(M00_FILES:$(M00_DIR)/%.cpp=$(OBJ_DIR)/$(M00_DIR)/%.o)
M00_DEPS        := $(M00_OBJS:$(OBJ_DIR)/%.o=$(DEP_DIR)/%.d)

M01_SRC         := Config ConfigParser
M01_DIR         := $(PROJECTDIR)/01_config
M01_FILES       := $(addprefix $(M01_DIR)/, $(addsuffix .cpp, $(M01_SRC)))
M01_OBJS        := $(M01_FILES:$(M01_DIR)/%.cpp=$(OBJ_DIR)/$(M01_DIR)/%.o)
M01_DEPS        := $(M01_OBJS:$(OBJ_DIR)/%.o=$(DEP_DIR)/%.d)

M02_SRC         := Request Response RequestParser HttpUtils
M02_DIR         := $(PROJECTDIR)/02_http
M02_FILES       := $(addprefix $(M02_DIR)/, $(addsuffix .cpp, $(M02_SRC)))
M02_OBJS        := $(M02_FILES:$(M02_DIR)/%.cpp=$(OBJ_DIR)/$(M02_DIR)/%.o)
M02_DEPS        := $(M02_OBJS:$(OBJ_DIR)/%.o=$(DEP_DIR)/%.d)

M03_SRC         := AutoIndexHandler DeleteHandler ErrorHandler Handler StaticFileHandler UploadHandler  
M03_DIR         := $(PROJECTDIR)/03_handlers
M03_FILES       := $(addprefix $(M03_DIR)/, $(addsuffix .cpp, $(M03_SRC)))
M03_OBJS        := $(M03_FILES:$(M03_DIR)/%.cpp=$(OBJ_DIR)/$(M03_DIR)/%.o)
M03_DEPS        := $(M03_OBJS:$(OBJ_DIR)/%.o=$(DEP_DIR)/%.d)

M04_SRC         := CGI CGIHandler
M04_DIR         := $(PROJECTDIR)/04_cgi
M04_FILES       := $(addprefix $(M04_DIR)/, $(addsuffix .cpp, $(M04_SRC)))
M04_OBJS        := $(M04_FILES:$(M04_DIR)/%.cpp=$(OBJ_DIR)/$(M04_DIR)/%.o)
M04_DEPS        := $(M04_OBJS:$(OBJ_DIR)/%.o=$(DEP_DIR)/%.d)

M05_SRC         := Session Cookie SessionManager SessionDemoHandler
M05_DIR         := $(PROJECTDIR)/05_session
M05_FILES       := $(addprefix $(M05_DIR)/, $(addsuffix .cpp, $(M05_SRC)))
M05_OBJS        := $(M05_FILES:$(M05_DIR)/%.cpp=$(OBJ_DIR)/$(M05_DIR)/%.o)
M05_DEPS        := $(M05_OBJS:$(OBJ_DIR)/%.o=$(DEP_DIR)/%.d)

M06_SRC         := Utils Logger
M06_DIR         := $(PROJECTDIR)/06_utils
M06_FILES       := $(addprefix $(M06_DIR)/, $(addsuffix .cpp, $(M06_SRC)))
M06_OBJS        := $(M06_FILES:$(M06_DIR)/%.cpp=$(OBJ_DIR)/$(M06_DIR)/%.o)
M06_DEPS        := $(M06_OBJS:$(OBJ_DIR)/%.o=$(DEP_DIR)/%.d)

# All object files and dependencies combined
OBJS            := $(MAIN_OBJS) $(M00_OBJS) $(M01_OBJS) $(M02_OBJS) $(M03_OBJS) \
                   $(M04_OBJS) $(M05_OBJS) $(M06_OBJS)
DEPS            := $(MAIN_DEPS) $(M00_DEPS) $(M01_DEPS) $(M02_DEPS) $(M03_DEPS) \
                   $(M04_DEPS) $(M05_DEPS) $(M06_DEPS)

# Directory creation - Updated to match new structure
MDIRS           := $(OBJ_DIR) \
                   $(OBJ_DIR)/$(M00_DIR) $(OBJ_DIR)/$(M01_DIR) \
                   $(OBJ_DIR)/$(M02_DIR) $(OBJ_DIR)/$(M03_DIR) \
                   $(OBJ_DIR)/$(M04_DIR) $(OBJ_DIR)/$(M05_DIR) \
                   $(OBJ_DIR)/$(M06_DIR) $(BIN_DIR) \
                   $(addprefix $(DEP_DIR)/,$(M00_DIR) $(M01_DIR) $(M02_DIR) \
                   $(M03_DIR) $(M04_DIR) $(M05_DIR) $(M06_DIR))

# Include flags (allows for direct sub-directory includes)
INCLUDES        := -I.

# Default rule
all: $(NAME)

# Rule for creating the final executable
$(NAME): $(MDIRS) $(OBJS)
	@echo "$(BOLD)$(BLINK)$(WHITE)$(ICON_LINK) Linking $(NAME)...$(RESET)"
	@$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)
	@echo "$(BOLD)$(BRIGHT_WHITE)$(STAR) $(UNDERLINE)$@ created$(RESET)"
	@chmod 000 assets/www/forbidden.html
	@chmod 000 assets/www/files/forbiddendir
	@echo "Folder for upload tests" > assets/upload/filedump/README.txt

# Create directories
$(MDIRS):
	@mkdir -p $@
	@echo "$(CYAN)$(FOLDER) Directory $@ created$(RESET)"

# Compile rule with dependency generation
$(OBJ_DIR)/%.o: %.cpp | $(MDIRS)
	@$(CXX) $(CXXFLAGS) $(INCLUDES) $(DEPFLAGS) -MF $(DEP_DIR)/$(<:.cpp=.d) -c $< -o $@
	@echo "$(BRIGHT_YELLOW)$(ICON_COMPILE) Compiled: $< -> $@$(RESET)"

# Update existing clean rules
clean: 
	@$(RM) $(OBJS) $(DEPS) webserv.log webservchild.log
	@echo "$(CYAN)$(BROOM_MARK) Object files and dependencies for $(NAME) cleared$(RESET)"
	@chmod 755 assets/www/forbidden.html
	@chmod 755 assets/www/files/forbiddendir
	@touch assets/upload/filedump/dummy
	@rm assets/upload/filedump/*

fclean: clean
	@$(RM) -r $(OBJ_DIR) $(DEP_DIR)
	@$(RM) $(NAME)
	@echo "$(CYAN)$(ICON_FCLEAN)  $(NAME) fully cleaned$(RESET)"

re: fclean all
	@echo "$(CYAN)$(ICON_REBUILD) Rebuilding...$(RESET)"

# Track header dependencies
-include $(DEPS)

# =============================================================================
# PHONY TARGETS
# =============================================================================
.PHONY: all clean fclean re

# =============================================================================
# COLOR AND ICON DEFINITIONS
# =============================================================================
CYAN            := \033[36m
WHITE           := \033[37m
RESET           := \033[0m
BRIGHT_RED      := \033[91m
BRIGHT_YELLOW   := \033[93m
BRIGHT_BLUE     := \033[94m
BRIGHT_WHITE    := \033[97m
BOLD            := \033[1m
UNDERLINE       := \033[4m
BLINK           := \033[5m

# Icons
STAR            := ⭐
GREEN_TICK      := ✅
GREEN_XCROSS    := ❎
BROOM_MARK      := 🧹
FOLDER          := 📁
FILE            := 📄
ICON_COMPILE    := 🔧
ICON_LINK       := 🔗
ICON_FCLEAN     := 🗑️
ICON_REBUILD    := 🔄
