SHELL := /bin/sh
TARGET = test

SOURCES = test.c

CC = clang

# LLVM verbose option
#CFLAGS += -v
#LDFLAGS += -v

# LLVM debugging options
#CFLAGS += -g

CFLAGS += -Xclang -load -Xclang ../../obfuscator/build/sub/libSubPass.so


all: $(TARGET) $(TARGET)_sub $(TARGET)_subloop

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) -emit-llvm -S -c $< -o $@.ll
	$(CC) $(CFLAGS) $< -o $@

$(TARGET)_sub: $(SOURCES)
	$(CC) $(CFLAGS) -mllvm -sub -emit-llvm -S -c $< -o $@.ll
	$(CC) $(CFLAGS) -mllvm -sub $< -o $@

$(TARGET)_subloop: $(SOURCES)
	$(CC) $(CFLAGS) -mllvm -sub -mllvm -sub_loop=3 -emit-llvm -S -c $< -o $@.ll
	$(CC) $(CFLAGS) -mllvm -sub -mllvm -sub_loop=3 $< -o $@

.PHONY: clean distclean

clean:
	$(RM) *.ll $(TARGET) $(TARGET)_sub $(TARGET)_subloop

distclean: clean
	$(RM) peda-session-*.txt .gdb_history

