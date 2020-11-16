#CC = gcc
CC = afl-clang-fast
LEX = flex
SYN = bison
AR = ar rcs

SYS = $(shell uname -s)
CFLAGS = -I$(ENV_PATH) -g
# Should never use bison on Mac... Use a virtual machine instead.
ifeq ($(SYS), Linux)
	CSYNFLAGS = -lfl -ly
else ifeq ($(SYS), Darwin) 
	CSYNFLAGS = -ll -ly
endif
LIBFLAGS = -L$(LIB_PATH) -l$(lib_name)
LFLAGS = 
SFLAGS = -d

ENV_PATH = $(shell pwd)
SRC_PATH = $(ENV_PATH)/src
LIB_SRC_PATH = $(SRC_PATH)/lib
LIB_PATH = $(ENV_PATH)/lib
HEADER_PATH = $(ENV_PATH)/include
BLD_PATH = $(ENV_PATH)/build
BIN_PATH = $(ENV_PATH)/bin
DEB_SRC_PATH = $(ENV_PATH)/debug_src


STAGE_1 = lexical-syntactical
STAGE_1_SRC_PATH = $(SRC_PATH)/stage1
STAGE_1_BLD_PATH = $(BLD_PATH)/stage1
lex_src_file = lex.l
syn_src_file = syntax.y
lex_file_name = lex.yy
syn_file_name = syntax.tab

STAGE_2 = semantic
STAGE_2_SRC_PATH = $(SRC_PATH)/stage2
STAGE_2_BLD_PATH = $(BLD_PATH)/stage2
sem_src = $(notdir $(wildcard $(STAGE_2_SRC_PATH)/*.c))
sem_object = $(sem_src:%.c=%.o)


lib_src = $(notdir $(wildcard $(LIB_SRC_PATH)/*.c))
lib_object = $(lib_src:%.c=%.o)
lib_name = splc
lib = lib$(lib_name)

target = $(BIN_PATH)/splc
TAR_OBJS = $(STAGE_1_BLD_PATH)/$(STAGE_1).o $(STAGE_2_BLD_PATH)/$(sem_object)
LIB_OBJS = $(foreach obj, $(lib_object), $(LIB_PATH)/$(obj))
OBJS = $(TAR_OBJS) $(LIB_OBJS)
notUpToDate:=false


all: initial $(target) final

initial:
	@echo "[*] Building environment..."
	-@mkdir $(BLD_PATH) 2>/dev/null || true;
	-@mkdir $(BIN_PATH) 2>/dev/null || true;
	-@mkdir $(LIB_PATH) 2>/dev/null || true;

$(target): $(LIB_PATH)/$(lib).a $(TAR_OBJS)
	@echo "[*] Generating binary..."
	$(CC) $(CFLAGS) -o $@ $(TAR_OBJS) $(LIBFLAGS)
	$(eval notUpToDate:=true)

final:
	@if [ "$(notUpToDate)" = "false" ]; \
	then echo "[*] Already up-to-date!"; \
	else echo "[*] Build successfully! Binary file at: $(BIN_PATH)"; \
		 echo "[*] Cleaning up"; \
	fi
	
#debug mode
debug: debug_initial initial $(target) final cleanDebug

debug_initial:
	@echo "[!] Entering debug mode:"
	-@mkdir $(LIB_PATH) 2>/dev/null || true;
	-@cp -r $(SRC_PATH) $(DEB_SRC_PATH);
	$(eval SFLAGS+=-v -t)
	$(eval SRC_PATH=$(DEB_SRC_PATH))
	-@sed -i 's/yyparse();/yydebug=1;yyparse();/g' $(STAGE_1_SRC_PATH)/$(syn_src_file)

cleanDebug:
	@echo "[*] Cleaning debug source file..."
	-rm -rf $(DEB_SRC_PATH);

#Static Library
lib: $(LIB_PATH)/$(lib).a

$(LIB_PATH)/$(lib).a: $(LIB_OBJS)
	$(AR) $@ $^
	@echo "[*] Library libsplc generated: $(LIB_PATH)/$(lib)"

$(LIB_OBJS): $(LIB_PATH)/%.o: $(LIB_SRC_PATH)/%.c
	-@mkdir $(LIB_PATH) 2>/dev/null || true;
	$(CC) $(CFLAGS) -o $@ -c $<

#Stage 1
$(STAGE_1_BLD_PATH)/$(STAGE_1).o: $(STAGE_1_BLD_PATH)/$(syn_file_name).c $(STAGE_1_BLD_PATH)/$(syn_file_name).h $(LIB_PATH)/$(lib).a
	$(CC) $(CFLAGS) -c $(STAGE_1_BLD_PATH)/$(syn_file_name).c $(CSYNFLAGS) -o $(STAGE_1_BLD_PATH)/$(STAGE_1).o $(LIBFLAGS);
	@echo "[*] Stage 1 completed."

$(STAGE_1_BLD_PATH)/$(syn_file_name).c: $(STAGE_1_SRC_PATH)/$(syn_src_file) $(STAGE_1_SRC_PATH)/$(lex_src_file)
	-@mkdir $(STAGE_1_BLD_PATH) 2>/dev/null || true;
	$(LEX) $(LFLAGS) -o $(STAGE_1_BLD_PATH)/$(lex_file_name).c $(STAGE_1_SRC_PATH)/$(lex_src_file);
	$(SYN) $(SFLAGS) $(STAGE_1_SRC_PATH)/$(syn_src_file) -o $(STAGE_1_BLD_PATH)/$(syn_file_name).c;

#Stage 2
$(STAGE_2_BLD_PATH)/$(sem_object): $(STAGE_2_BLD_PATH)/%.o : $(STAGE_2_SRC_PATH)/%.c $(LIB_PATH)/$(lib).a
	-@mkdir $(STAGE_2_BLD_PATH) 2>/dev/null || true;
	$(CC) $(CFLAGS) -o $@ -c $<
	@echo "[*] Stage 2 completed."

clean:
	@echo "[*] Cleaning up..."
	-rm -rf $(BLD_PATH) $(BIN_PATH) $(LIB_PATH) $(DEB_SRC_PATH);

#Object files in $(OBJS) will be automatically removed.
.INTERMEDIATE: $(OBJS)
.PHONY: all initial final lib debug debug_initial clean cleanDebug
