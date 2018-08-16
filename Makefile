all:
	cd gep/lab1 && pdflatex main.tex
	mv gep/lab1/main.pdf gep/lab1/gep-lab1-cmake.pdf

	cd 3dgp/lab1 && pdflatex main.tex
	mv 3dgp/lab1/main.pdf 3dgp/lab1/3dgp-lab1-triangle.pdf

	cd 3dgp/lab2 && pdflatex main.tex
	mv 3dgp/lab2/main.pdf 3dgp/lab2/3dgp-lab2-shaders.pdf

	cd 3dgp/lab3 && pdflatex main.tex
	mv 3dgp/lab3/main.pdf 3dgp/lab3/3dgp-lab3-architecture.pdf
