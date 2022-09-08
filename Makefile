TARGET = main

SOURCE_DIR = ./src
LEXICAL_ANALYZER_DIR = $(SOURCE_DIR)/analyzer/lexical
BNF_DIR = $(SOURCE_DIR)/bnf
OUTDIR = ./dist
CC = g++

objects = $(OUTDIR)/rubyc.o $(OUTDIR)/lexical-analyzer.o

$(TARGET): $(objects)
	$(CC) -o $(OUTDIR)/$(TARGET).out $(objects)

rubyc.o: $(SOURCE_DIR)/rubyc.cpp $(LEXICAL_ANALYZER_DIR)/lexical-analyzer.h
	$(CC) -c $(SOURCE_DIR)/rubyc.cpp -o $(OUTDIR)/rubyc.o

lexical-analyzer.o: $(LEXICAL_ANALYZER_DIR)/lexical-analyzer.cpp $(LEXICAL_ANALYZER_DIR)/lexical-analyzer.h
	$(CC) -c $(LEXICAL_ANALYZER_DIR)/lexical-analyzer.cpp -o $(OUTDIR)/lexical-analyzer.o

clean:
	rm *.o $(OUTDIR)/*