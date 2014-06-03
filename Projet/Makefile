CC = gcc
CFLAGS = -Wall -pedantic -g
LDFLAGS =
project = foo_bar
bin = bin
doc = doc
src = src
objects := $(foreach obj, \
	data.o \
	server.o\
	, $(src)/$(obj))

default: $(bin)/$(project)

%.o: %.c %.h
	$(CC) -c $(CFLAGS) -o $@ $<

$(bin):
	mkdir $(bin)

$(bin)/$(project): $(src)/$(project).c $(objects) $(bin)
	$(CC) $(CFLAGS) -o $@ $< $(objects) $(LDFLAGS)

doc.pdf: $(doc)/doc.tex
	pdflatex -output-directory $(doc) $^
	pdflatex -output-directory $(doc) $^
	mv $(doc)/$@ .

.PHONY: clean

clean:
	rm -rf $(bin)
	rm -f $(src)/*.o
	rm -f $(doc)/doc.{aux,log,toc}
