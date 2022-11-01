TARGET = main
TEST_TARGET = test

SOURCE_DIR = ./src
LEXICAL_ANALYZER_DIR = $(SOURCE_DIR)/analyzer/lexical
SYNTACTIC_ANALYZER_DIR = $(SOURCE_DIR)/analyzer/syntactic
BNF_DIR = $(SOURCE_DIR)/bnf
OUTDIR = ./dist
CC = g++
DEBUG_FLAGS = -g

objects = $(OUTDIR)/heat.o $(OUTDIR)/lexical-analyzer.o $(OUTDIR)/syntactic-analyzer.o $(OUTDIR)/keywords.o $(OUTDIR)/operators.o $(OUTDIR)/delimiters.o $(OUTDIR)/identifiers.o
test_objects = $(OUTDIR)/test.o $(OUTDIR)/keywords.o $(OUTDIR)/operators.o $(OUTDIR)/delimiters.o $(OUTDIR)/identifiers.o

$(TARGET): $(objects)
	$(CC) -o $(OUTDIR)/$(TARGET).out $(objects) $(DEBUG_FLAGS)

$(TEST_TARGET): $(test_objects)
	$(CC) -o $(OUTDIR)/$(TEST_TARGET).out $(test_objects)

$(OUTDIR)/test.o: $(LEXICAL_ANALYZER_DIR)/tests/lexical-analyzer.spec.cpp $(LEXICAL_ANALYZER_DIR)/lexical-analyzer.h
	$(CC) -c $(LEXICAL_ANALYZER_DIR)/tests/lexical-analyzer.spec.cpp -o $(OUTDIR)/test.o

$(OUTDIR)/heat.o: $(SOURCE_DIR)/heat.cpp $(LEXICAL_ANALYZER_DIR)/lexical-analyzer.h
	$(CC) -c $(SOURCE_DIR)/heat.cpp -o $(OUTDIR)/heat.o 

$(OUTDIR)/lexical-analyzer.o: $(LEXICAL_ANALYZER_DIR)/lexical-analyzer.cpp $(LEXICAL_ANALYZER_DIR)/lexical-analyzer.h $(BNF_DIR)/keywords.h
	$(CC) -c $(LEXICAL_ANALYZER_DIR)/lexical-analyzer.cpp -o $(OUTDIR)/lexical-analyzer.o 

$(OUTDIR)/syntactic-analyzer.o: $(SYNTACTIC_ANALYZER_DIR)/syntactic-analyzer.cpp $(SYNTACTIC_ANALYZER_DIR)/syntactic-analyzer.h $(BNF_DIR)/keywords.h
	$(CC) -c $(SYNTACTIC_ANALYZER_DIR)/syntactic-analyzer.cpp -o $(OUTDIR)/syntactic-analyzer.o $(DEBUG_FLAGS)

$(OUTDIR)/keywords.o: $(BNF_DIR)/keywords.cpp $(BNF_DIR)/keywords.h
	$(CC) -c $(BNF_DIR)/keywords.cpp -o $(OUTDIR)/keywords.o 

$(OUTDIR)/operators.o: $(BNF_DIR)/operators.cpp $(BNF_DIR)/operators.h
	$(CC) -c $(BNF_DIR)/operators.cpp -o $(OUTDIR)/operators.o 

$(OUTDIR)/delimiters.o: $(BNF_DIR)/delimiters.cpp $(BNF_DIR)/delimiters.h
	$(CC) -c $(BNF_DIR)/delimiters.cpp -o $(OUTDIR)/delimiters.o 

$(OUTDIR)/identifiers.o: $(BNF_DIR)/identifiers.cpp $(BNF_DIR)/identifiers.h
	$(CC) -c $(BNF_DIR)/identifiers.cpp -o $(OUTDIR)/identifiers.o 

clean:
	rm *.o $(OUTDIR)/**