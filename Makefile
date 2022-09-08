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

lexical-analyzer.o: $(LEXICAL_ANALYZER_DIR)/lexical-analyzer.cpp $(LEXICAL_ANALYZER_DIR)/lexical-analyzer.h $(BNF_DIR)/keywords.h
	$(CC) -c $(LEXICAL_ANALYZER_DIR)/lexical-analyzer.cpp -o $(OUTDIR)/lexical-analyzer.o

keywords.o: $(BNF_DIR)/keywords.cpp $(BNF_DIR)/keywords.h
	$(CC) -c $(BNF_DIR)/keywords.cpp -o $(OUTDIR)/keywords.o

operators.o: $(BNF_DIR)/operators.cpp $(BNF_DIR)/operators.h
	$(CC) -c $(BNF_DIR)/operators.cpp -o $(OUTDIR)/operators.o

clean:
	rm *.o $(OUTDIR)/*