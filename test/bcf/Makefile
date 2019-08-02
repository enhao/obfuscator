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

CFLAGS += -Xclang -load -Xclang ../../obfuscator/build/bcf/libBcfPass.so


all: $(TARGET) $(TARGET)_bcf $(TARGET)_bcfloop $(TARGET)_bcfprob

$(TARGET): $(SOURCES)
	$(CC) $(CFLAGS) $< -o $@
	$(R2) -q -c 'aa;agfd main > $@.dot' $@
	$(DOT) -Tpng -o $@.png $@.dot

$(TARGET)_bcf: $(SOURCES)
	$(CC) $(CFLAGS) -mllvm -bcf $< -o $@
	$(R2) -q -c 'aa;agfd main > $@.dot' $@
	$(DOT) -Tpng -o $@.png $@.dot

$(TARGET)_bcfloop: $(SOURCES)
	$(CC) $(CFLAGS) -mllvm -bcf -mllvm -bcf_loop=3 $< -o $@
	$(R2) -q -c 'aa;agfd main > $@.dot' $@
	$(DOT) -Tpng -o $@.png $@.dot

$(TARGET)_bcfprob: $(SOURCES)
	$(CC) $(CFLAGS) -mllvm -bcf -mllvm -bcf_loop=3 -mllvm -bcf_prob=40 $< -o $@
	$(R2) -q -c 'aa;agfd main > $@.dot' $@
	$(DOT) -Tpng -o $@.png $@.dot

.PHONY: clean distclean

clean:
	$(RM) $(TARGET) $(TARGET)_bcf $(TARGET)_bcfloop $(TARGET)_bcfprob
	$(RM) *.dot *.png

distclean: clean
	$(RM) peda-session-*.txt .gdb_history

