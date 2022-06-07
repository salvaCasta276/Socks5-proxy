CC= gcc #TODO: deshardcodear el compilador
CFLAGS= -std=gnu11 -g -Wall -pedantic -D_POSIX_SOURCE=1 -D_GNU_SOURCE 
#--std=c99 -pedantic -pedantic-errors -Wall -Wextra -Werror -Wno-unused-parameter -Wno-implicit-fallthrough -D_POSIX_C_SOURCE=200112L 
LDFLAGS= -pthread

#Si se agrega un directorio bajo src agregar una variable _DIR al final de estas siguiendo el patron
SRC_DIR= src
STATE_DIR= $(SRC_DIR)/state
PARSE_DIR= $(SRC_DIR)/parsing

EXEC= server

#Si se agrega un directorio para compilar agregar un SRC+= al final de estas siguiendo el patron
SRC= $(wildcard $(SRC_DIR)/*.c)
SRC+= $(wildcard $(PARSE_DIR)/*.c)
SRC+= $(wildcard $(STATE_DIR)/*.c)

OBJ= $(patsubst %.c, %.o, $(SRC))

.PHONY: all
all: $(OBJ)
	@$(CC) $(CFLAGS) $(LDFLAGS) -o $(EXEC) $(OBJ)

%.o : %.c %.h
	@$(CC) -c $(CFLAGS) $(LDFLAGS) $< -o $@

.PHONY: clean
clean:
	@rm -f $(OBJ) server
#	find . -name '*.o' -type f -delete
