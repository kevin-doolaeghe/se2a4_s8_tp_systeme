# Compiler
CC          = gcc

# Executable name
TARGET      = program

# Paths
SRCDIR      = .
OBJDIR      = build
PATHLIBH    = .
PATHLIBA    = .

# Libraries to link
LIBS        = $(addprefix -l, $(patsubst lib%, %, $(basename $(notdir $(wildcard $(PATHLIBA)/*.a))))) -lm

# Compiler and linker flags
INCLUDES    = -I$(PATHLIBH)
LDFLAGS     = -L$(PATHLIBA) $(LIBS)
CFLAGS      = -Wall -Wextra -g -O0 $(INCLUDES) -D MSG="\"message test\""

EXEC        = $(addprefix $(OBJDIR)/, $(TARGET))

CFILES      = $(notdir $(wildcard $(addprefix $(SRCDIR)/, *c)))
SRC         = $(addprefix $(SRCDIR)/, $(CFILES))

OBJ         = $(addprefix $(OBJDIR)/, $(CFILES:.c=.o))

#####################################################

all : build

build : prepare format $(EXEC)

rebuild : clean build

#####################################################

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	$(CC) -o $@ -c $< $(CFLAGS) $(INCLUDES)

$(EXEC) : $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

#####################################################

prepare :
	mkdir -p $(OBJDIR)

format :
	if hash clang-format 2> /dev/null; then clang-format -i $(SRCDIR)/*.c $(PATHLIBH)/*.h; fi
	if hash clang-format-7 2> /dev/null; then clang-format-7 -i $(SRCDIR)/*.c $(PATHLIBH)/*.h; fi

#####################################################

clean :
	rm -fr $(OBJDIR)/*.o

mrproper :
	rm -fr $(OBJDIR)

.PHONY : clean mrproper prepare
