NAME = libft.a

SRCDIR = .
OBJDIR = obj
INCDIR = .

# Source Files
SRC = ft_strtrim.c ft_memset.c ft_strcmp.c ft_strncmp.c ft_putdenl_fd.c ft_lstdelone.c ft_isascii.c ft_substr.c ft_putstr_fd.c ft_lstlast.c ft_lstiter.c ft_toupper.c ft_strjoin.c ft_bzero.c ft_atoi.c ft_calloc.c ft_lstadd_back.c ft_putchar_fd.c ft_tolower.c ft_split.c ft_strmapi.c ft_striteri.c ft_putnbr_fd.c ft_itoa.c ft_isprint.c ft_strdup.c ft_memchr.c ft_lstadd_front.c ft_memmove.c ft_strlcpy.c ft_strlen.c ft_isdigit.c ft_lstsize.c ft_isalpha.c ft_strrchr.c ft_lstmap.c ft_strlcat.c ft_memcmp.c ft_strnstr.c ft_isalnum.c ft_memcpy.c ft_lstnew.c ft_lstclear.c ft_strchr.c 
OBJ = $(SRC:.c=.o)
SRC := $(addprefix $(SRCDIR)/, $(SRC))
OBJ := $(patsubst $(SRCDIR)/%, $(OBJDIR)/%, $(OBJ))

# Libraries and Linker Flags
LDFLAGS = 
LIBS = 

# Archiver
AR = ar
ARFLAGS = rcs

# Compiler and Flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INCDIR) -g3

# Compilation mode (silent by default, set VERBOSE=1 to show commands)
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
all: $(OBJDIR) $(NAME)

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
$(NAME): $(OBJ)
	$(V)$(AR) $(ARFLAGS) $@ $^
	$(V)echo $(GREEN)"[$(NAME)] Library created ✅"$(RESET)

# Clean Rules
clean:
	$(V)echo $(RED)'[$(NAME)] Cleaning objects'd$(RESET)
	$(V)rm -rf $(OBJDIR)

fclean: clean
	$(V)echo $(RED)'[$(NAME)] Cleaning all files'$(RESET)
	$(V)rm -f $(NAME)

re: fclean all

# Makefile Reconfiguration 
regen:
	makemyfile

.PHONY: all clean fclean re bonus regen
.DEFAULT_GOAL := all
