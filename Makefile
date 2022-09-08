TARGET = main

SOURCE_DIR = ./src
LEXICAL_ANALYZER_DIR = $(SOURCE_DIR)/analyzer/lexical
BNF_DIR = $(SOURCE_DIR)/bnf
OUTDIR = ./dist
CC = g++

objects = rubyc.o lexical-analyzer.o

$(TARGET): $(objects)
	$(CC) -o $(OUTDIR)/$(TARGET).out $(objects)

rubyc.o: $(SOURCE_DIR)/rubyc.cpp $(LEXICAL_ANALYZER_DIR)/lexical-analyzer.h
	$(CC) -c $(SOURCE_DIR)/rubyc.cpp

lexical-analyzer.o: $(LEXICAL_ANALYZER_DIR)/lexical-analyzer.cpp $(LEXICAL_ANALYZER_DIR)/lexical-analyzer.h
	$(CC) -c $(LEXICAL_ANALYZER_DIR)/lexical-analyzer.cpp

# keywords.o: $(BNF_DIR)/keywords.cpp $(BNF_DIR)/keywords.h
# 	$(CC) -c $(BNF_DIR)/keywords.cpp

clean:
	rm *.o $(OUTDIR)/*