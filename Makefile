TARGET = main
TEST_TARGET = test

SOURCE_DIR = ./src
LEXICAL_ANALYZER_DIR = $(SOURCE_DIR)/analyzer/lexical
SYNTACTIC_ANALYZER_DIR = $(SOURCE_DIR)/analyzer/syntactic
SEMANTIC_ANALYZER_DIR = $(SOURCE_DIR)/analyzer/semantic
BNF_DIR = $(SOURCE_DIR)/bnf
OUTDIR = ./dist
CC = g++
DEBUG_FLAGS = -g

objects = $(OUTDIR)/heat.exe $(OUTDIR)/lexical-analyzer.exe $(OUTDIR)/syntactic-analyzer.exe $(OUTDIR)/semantic-analyzer.exe $(OUTDIR)/keywords.exe $(OUTDIR)/operators.exe $(OUTDIR)/delimiters.exe $(OUTDIR)/identifiers.exe
test_objects = $(OUTDIR)/test.exe $(OUTDIR)/keywords.exe $(OUTDIR)/operators.exe $(OUTDIR)/delimiters.exe $(OUTDIR)/identifiers.exe

$(TARGET): $(objects)
	$(CC) -o $(OUTDIR)/$(TARGET).exe $(objects) $(DEBUG_FLAGS)

$(TEST_TARGET): $(test_objects)
	$(CC) -o $(OUTDIR)/$(TEST_TARGET).exe $(test_objects)

$(OUTDIR)/test.exe: $(LEXICAL_ANALYZER_DIR)/tests/lexical-analyzer.spec.cpp $(LEXICAL_ANALYZER_DIR)/lexical-analyzer.h
	$(CC) -c $(LEXICAL_ANALYZER_DIR)/tests/lexical-analyzer.spec.cpp -o $(OUTDIR)/test.exe

$(OUTDIR)/heat.exe: $(SOURCE_DIR)/heat.cpp $(LEXICAL_ANALYZER_DIR)/lexical-analyzer.h
	$(CC) -c $(SOURCE_DIR)/heat.cpp -o $(OUTDIR)/heat.exe 

$(OUTDIR)/lexical-analyzer.exe: $(LEXICAL_ANALYZER_DIR)/lexical-analyzer.cpp $(LEXICAL_ANALYZER_DIR)/lexical-analyzer.h $(BNF_DIR)/keywords.h
	$(CC) -c $(LEXICAL_ANALYZER_DIR)/lexical-analyzer.cpp -o $(OUTDIR)/lexical-analyzer.exe 

$(OUTDIR)/syntactic-analyzer.exe: $(SYNTACTIC_ANALYZER_DIR)/syntactic-analyzer.cpp $(SYNTACTIC_ANALYZER_DIR)/syntactic-analyzer.h $(BNF_DIR)/keywords.h
	$(CC) -c $(SYNTACTIC_ANALYZER_DIR)/syntactic-analyzer.cpp -o $(OUTDIR)/syntactic-analyzer.exe $(DEBUG_FLAGS)

$(OUTDIR)/semantic-analyzer.exe: $(SEMANTIC_ANALYZER_DIR)/semantic-analyzer.cpp $(SEMANTIC_ANALYZER_DIR)/semantic-analyzer.h $(BNF_DIR)/keywords.h
	$(CC) -c $(SEMANTIC_ANALYZER_DIR)/semantic-analyzer.cpp -o $(OUTDIR)/semantic-analyzer.exe $(DEBUG_FLAGS)

$(OUTDIR)/keywords.exe: $(BNF_DIR)/keywords.cpp $(BNF_DIR)/keywords.h
	$(CC) -c $(BNF_DIR)/keywords.cpp -o $(OUTDIR)/keywords.exe 

$(OUTDIR)/operators.exe: $(BNF_DIR)/operators.cpp $(BNF_DIR)/operators.h
	$(CC) -c $(BNF_DIR)/operators.cpp -o $(OUTDIR)/operators.exe 

$(OUTDIR)/delimiters.exe: $(BNF_DIR)/delimiters.cpp $(BNF_DIR)/delimiters.h
	$(CC) -c $(BNF_DIR)/delimiters.cpp -o $(OUTDIR)/delimiters.exe 

$(OUTDIR)/identifiers.exe: $(BNF_DIR)/identifiers.cpp $(BNF_DIR)/identifiers.h
	$(CC) -c $(BNF_DIR)/identifiers.cpp -o $(OUTDIR)/identifiers.exe 

clean:
	rm *.exe $(OUTDIR)/**