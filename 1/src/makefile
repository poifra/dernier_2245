CC=cc
CFLAGS=-I. -g -std=c11 -pedantic-errors -D_POSIX_SOURCE

LEX=flex
LEXFLAGS=

YACC=bison
YACCFLAGS=--yacc --defines

DEPS=y.tab.c lex.yy.c vmm.c common.c physical_memory.c tlb.c 

BUILD_DIR=../build

.PHONY: default all clean format release

default: $(BUILD_DIR)/vm

all: default

lex.yy.c: y.tab.h command.l
	$(LEX) $(LEXFLAGS) command.l

y.tab.h: command.y
	$(YACC) $(YACCFLAGS) command.y

y.tab.c: command.y
	$(YACC) $(YACCFLAGS) command.y

format: $(DEPS)
	indent -l 80 $(DEPS)
	rm -f *~

OBJ = $(patsubst %.c,$(BUILD_DIR)/obj/%.o, $(DEPS))

$(BUILD_DIR)/obj/%.o: %.c $(DEPS)
	mkdir -p $(BUILD_DIR)/obj
	$(CC) -c $(CFLAGS) -o $@ $< 

$(BUILD_DIR)/vm: $(OBJ)
	mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) -o $@ $^ 

clean:
	rm -f $(BUILD_DIR)/obj/*.o $(BUILD_DIR)/vm y.tab.h y.tab.c lex.yy.c ../*.aux ../*.log
