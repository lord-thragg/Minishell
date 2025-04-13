#-----------------------------------------------------------------------------------#
#																					#
#		███╗   ███╗██╗███╗   ██╗██╗███████╗██╗  ██╗███████╗██╗     ██╗				#
#		████╗ ████║██║████╗  ██║██║██╔════╝██║  ██║██╔════╝██║     ██║				#
#		██╔████╔██║██║██╔██╗ ██║██║███████╗███████║█████╗  ██║     ██║				#
#		██║╚██╔╝██║██║██║╚██╗██║██║╚════██║██╔══██║██╔══╝  ██║     ██║				#
#		██║ ╚═╝ ██║██║██║ ╚████║██║███████║██║  ██║███████╗███████╗███████╗			#
#		╚═╝     ╚═╝╚═╝╚═╝  ╚═══╝╚═╝╚══════╝╚═╝  ╚═╝╚══════╝╚══════╝╚══════╝			#
#																					#
#-----------------------------------------------------------------------------------#

NAME = minishell

SRCDIR = src
OBJDIR = obj
INCDIR = includes

# Source Files
SRC_DEBUG		=	debug/debug.c

SRC_MAIN 		=	main.c minishell.c
SRC_ENV 		=	builtins/env/ft_getenv.c

SRC_BULTIN		=	builtins/echo/echo.c builtins/env/env.c \
					builtins/export/export.c builtins/export/export_utils.c builtins/cd.c \
					builtins/unset.c builtins/pwd.c builtins/exit.c

SRC_FREE		=	free/free.c

SRC_SIGNALS		=	signals/signal_handling.c

SRC_COMMANDS	:=	parsing/commands/command.c parsing/commands/utils.c parsing/commands/utils2.c
SRC_EXPAND		:=	parsing/expand/expand.c parsing/expand/utils.c \
					parsing/expand/utils2.c parsing/expand/utils3.c parsing/expand/utils4.c
SRC_TOKEN		:=	parsing/tokenize/tokenize.c parsing/tokenize/utils.c parsing/tokenize/utils2.c
SRC_PARSING		:=	parsing/parsing.c parsing/utils/ft_splitspaces.c parsing/utils/utils.c \
					parsing/utils/utils_split.c $(SRC_COMMANDS) $(SRC_TOKEN) $(SRC_EXPAND)

SRC_EXEC		=	execution/executions_utils/execution.c execution/executions_utils/loop_execution.c \
					execution/redirect/files_manager.c execution/redirect/infile_order.c \
					execution/here_docs/here_doc_handle.c execution/here_docs/here_docs_utils.c

SRC = $(SRC_DEBUG) $(SRC_MAIN) $(SRC_FREE) $(SRC_PARSING) $(SRC_SIGNALS) $(SRC_ENV) $(SRC_BULTIN) $(SRC_EXEC)
OBJ = $(SRC:.c=.o)
SRC := $(addprefix $(SRCDIR)/, $(SRC))
OBJ := $(patsubst $(SRCDIR)/%, $(OBJDIR)/%, $(OBJ))

# Libft
LIBFT_DIR := libft
LIBFT := $(LIBFT_DIR)/libft.a
LIBFT_INCLUDE := $(LIBFT_DIR)
# Libraries and Linker Flags
LDFLAGS =  -L$(LIBFT_DIR) -lreadline
LIBS =  $(LIBFT)

# Archiver
AR = ar
ARFLAGS = rcs

# Compiler and Flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INCDIR) -g3 -I$(LIBFT_INCLUDE) 

# Compilation mode
VERBOSE ?= 0
ifeq ($(VERBOSE),1)
  V := 
else
  V := @
endif

# Colors
RED     := "\033[1;31m"
GREEN   := "\033[1;32m"
RESET   := "\033[0m"

# Default Rule
all: $(OBJDIR) $(LIBFT) $(NAME)

# Object Directory Rule
$(OBJDIR):
	$(V)mkdir -p $(OBJDIR) || true

# Dependency Files
DEP = $(OBJ:.o=.d)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	@mkdir -p $(dir $@)
	$(V)$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

-include $(DEP)

# Linking Rule
$(NAME): $(OBJ) $(LIBFT)
	$(V)$(CC) $(CFLAGS) $(OBJ) $(BONUS_OBJ) $(LIBS) $(LDFLAGS) $(MLXFLAGS) -o $(NAME)
	$(V)echo $(GREEN)"[$(NAME)] Executable created ✅"$(RESET)

# Libft
$(LIBFT):
	$(V)$(MAKE) --silent -C $(LIBFT_DIR)
	$(V)echo '[$(NAME)] Libft build successfully'

# Clean Rules
clean:
	$(V)echo $(RED)'[$(NAME)] Cleaning objects'd$(RESET)
	$(V)rm -rf $(OBJDIR)

fclean: clean
	$(V)echo $(RED)'[$(NAME)] Cleaning all files'$(RESET)
	$(V)rm -f $(NAME)
	$(V)$(MAKE) --silent -C $(LIBFT_DIR) fclean

re: fclean all

# Makefile Reconfiguration 
regen:
	makemyfile

.PHONY: all clean fclean re bonus regen
.DEFAULT_GOAL := all