all:
	cd gep/lab1 && pdflatex main.tex
	mv gep/lab1/main.pdf gep/lab1/gep-lab1-cmake.pdf

	cd 3dgp/lab1 && pdflatex main.tex
	mv 3dgp/lab1/main.pdf 3dgp/lab1/3dgp-lab1-triangle.pdf
