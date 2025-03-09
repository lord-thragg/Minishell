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
SRC_MAIN 		=	main.c minishell.c
SRC_ENV 		=	env/ft_getenv.c
SRC_BULTIN		=	builtin/echo.c builtin/env.c builtin/export.c builtin/cd.c builtin/unset.c
SRC_FREE		=	free/free.c
SRC_SIGNALS		=	signals/signal_handling.c
SRC_PARSING		=	parsing/parsing.c parsing/command.c parsing/token.c		\
					parsing/advance_split.c		parsing/ft_splitspace.c		\
					parsing/utils_commands.c	parsing/utils_commands2.c	
SRC_EXEC		=	execution/execution.c execution/loop_execution.c		\
					execution/files_manager.c execution/here_docs_utils.c	\
					execution/here_doc_handle.c

SRC = $(SRC_MAIN) $(SRC_FREE) $(SRC_PARSING) $(SRC_SIGNALS) $(SRC_ENV) $(SRC_BULTIN) $(SRC_EXEC)
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