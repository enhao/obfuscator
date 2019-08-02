SHELL := /bin/sh
TARGET = test

SOURCES = test.c

CC = clang
R2 = r2
DOT = dot

# LLVM verbose option
#CFLAGS += -v
#LDFLAGS += -v

# LLVM debugging options
#CFLAGS += -g

CFLAGS += -Xclang -load -Xclang ../../obfuscator/build/fla/libFlaPass.so


all: $(TARGET) $(TARGET)_fla $(TARGET)_split $(TARGET)_splitnum

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $< -o $@
	$(R2) -q -c 'aa;agfd main > $@.dot' $@
	$(DOT) -Tpng -o $@.png $@.dot

$(TARGET)_fla: $(SOURCES)
	$(CC) $(CFLAGS) -mllvm -fla $< -o $@
	$(R2) -q -c 'aa;agfd main > $@.dot' $@
	$(DOT) -Tpng -o $@.png $@.dot

$(TARGET)_split: $(SOURCES)
	$(CC) $(CFLAGS) -mllvm -fla -mllvm -split $< -o $@
	$(R2) -q -c 'aa;agfd main > $@.dot' $@
	$(DOT) -Tpng -o $@.png $@.dot

$(TARGET)_splitnum: $(SOURCES)
	$(CC) $(CFLAGS) -mllvm -fla -mllvm -split -mllvm -split_num=3 $< -o $@
	$(R2) -q -c 'aa;agfd main > $@.dot' $@
	$(DOT) -Tpng -o $@.png $@.dot

.PHONY: clean distclean

clean:
	$(RM) $(TARGET) $(TARGET)_fla $(TARGET)_split $(TARGET)_splitnum
	$(RM) *.dot *.png

distclean: clean
	$(RM) peda-session-*.txt .gdb_history

