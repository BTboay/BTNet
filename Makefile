VPATH=./src/:./examples
EXEC=test
OBJDIR=./obj/

CC=gcc
LDFLAGS= -lm -pthread
COMMON= -Isrc/ -Iinclude/
CFLAGS=-Wall -Wno-unused-result -Wno-unknown-pragmas -Wfatal-errors -fPIC

OBJ=gemm.o im2col.o image.o parser.o pooling.o utils.o
EXECOBJA=test.o

EXECOBJ = $(addprefix $(OBJDIR), $(EXECOBJA))
OBJS = $(addprefix $(OBJDIR), $(OBJ))
DEPS = $(wildcard src/*.h) Makefile

all: obj $(EXEC)
#all: obj $(EXEC)

#$^所有的依赖文件 $@目标文件 $<第一个依赖文件
$(EXEC): $(EXECOBJ) $(OBJS)
	$(CC) $(COMMON) $(CFLAGS) $^ -o $@ $(LDFLAGS) $(ALIB)

$(OBJDIR)%.o: %.c $(DEPS)
	$(CC) $(COMMON) $(CFLAGS) -c $< -o $@

obj:
	mkdir -p obj

.PHONY: clean

clean:
	rm -rf $(OBJS) $(EXEC) $(EXECOBJ) $(OBJDIR)/*