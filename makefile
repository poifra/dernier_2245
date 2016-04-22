

.PHONY: clean format release rapport

format: $(DEPS)
	cd 1/src/ && make format
	cd 2/src/ && make format

all: $(DEPS)
	cd 1/src/ && make
	cd 2/src/ && make

rapport: rapport.tex
	pdflatex rapport.tex

release: rapport clean format
	tar -czvf ../tp3.tar.gz .

clean:
	cd 1/src && make clean
	cd 2/src && make clean
	rm -f *.aux *.log
