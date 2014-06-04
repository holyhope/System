CC = gcc
project = Feugueur_Glevarec_Peronnet

BIN_FOLDER = bin
DOC_FOLDER = doc
SRC_FOLDER = src
OBJ_FOLDER = objects
HEADER_FOLDER = include

objects := $(foreach obj, \
	follow.o \
	server.o \
	users.o \
	data.o \
	log.o \
	, $(OBJ_FOLDER)/$(obj))

CFLAGS = -Wall -pedantic -g
LDFLAGS = -I$(HEADER_FOLDER)/

default: $(project)

$(BIN_FOLDER):
	mkdir $(BIN_FOLDER)
	
$(HEADER_FOLDER):
	mkdir $(HEADER_FOLDER)
	
$(SRC_FOLDER):
	mkdir $(SRC_FOLDER)
	
$(OBJ_FOLDER):
	mkdir $(OBJ_FOLDER)

$(OBJ_FOLDER)/%.o: $(SRC_FOLDER)/%.c $(HEADER_FOLDER)/%.h $(OBJ_FOLDER)
	$(CC) -c $(CFLAGS) -o $@ $< $(LDFLAGS)

%.c: $(SRC_FOLDER)

%.h: $(HEADER_FOLDER)

$(project): $(SRC_FOLDER)/$(project).c $(objects) $(BIN_FOLDER)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< $(objects)

doc.pdf: $(DOC_FOLDER)/doc.tex
	pdflatex -output-directory $(DOC_FOLDER) $^
	mv $(DOC_FOLDER)/$@ .
	
doxygen:
	doxygen

clean:
	rm -f $(OBJ_FOLDER)/*
	rm -f $(DOC_FOLDER)/doc.{aux,log,toc}
	rm -rf $(DOC_FOLDER)/html
	rm -rf $(DOC_FOLDER)/latex

mrproper: clean
	rm -f $(BIN_FOLDER)/*
