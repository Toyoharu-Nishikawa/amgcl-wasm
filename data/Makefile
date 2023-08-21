all: install

install:
	
	$(CC) $(CFLAGS)  main.cpp  $(INC) $(INC2)  $(EFLAG) $(AFLAG) $(EXP) $(EMO)

CC = emcc
CFLAGS = -O2 
INC   = -I /amgcl

INC2  = -I ./boost

#INC2  = -I /data/boost \
 
EFLAG = -sERROR_ON_UNDEFINED_SYMBOLS=0 
AFLAG = -sASSERTIONS 
EXP   = -s "EXPORTED_FUNCTIONS=['_malloc','_free']" 
EMO   = -s WASM=1 -s MODULARIZE=1 -s ALLOW_MEMORY_GROWTH -s INITIAL_MEMORY=1000MB -s MAXIMUM_MEMORY=4GB -s EXPORT_ES6=1 -o amgcl.js


