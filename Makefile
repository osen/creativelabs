all:
	cd gep/lab1 && pdflatex main.tex
	mv gep/lab1/main.pdf gep/lab1/gep-lab1-cmake.pdf

	cd gep/lab2 && pdflatex main.tex
	mv gep/lab2/main.pdf gep/lab2/gep-lab2-ces.pdf

	cd gep/lab3b && pdflatex main.tex
	mv gep/lab3b/main.pdf gep/lab3b/gep-lab3b-opengl.pdf

	cd gep/lab4 && pdflatex main.tex
	mv gep/lab4/main.pdf gep/lab4/gep-lab5-resources.pdf

	cd 3dgp/lab1 && pdflatex main.tex
	mv 3dgp/lab1/main.pdf 3dgp/lab1/3dgp-lab1-2-triangle.pdf

	cd 3dgp/lab2 && pdflatex main.tex
	mv 3dgp/lab2/main.pdf 3dgp/lab2/3dgp-lab3-shaders.pdf

	cd 3dgp/lab3 && pdflatex main.tex
	mv 3dgp/lab3/main.pdf 3dgp/lab3/3dgp-lab4-architecture.pdf

	cd 3dgp/lab4 && pdflatex main.tex
	mv 3dgp/lab4/main.pdf 3dgp/lab4/3dgp-lab5-matrix.pdf

	cd 3dgp/lab5 && pdflatex main.tex
	mv 3dgp/lab5/main.pdf 3dgp/lab5/3dgp-lab6-textures.pdf

	cd 3dgp/lab7 && pdflatex main.tex
	mv 3dgp/lab7/main.pdf 3dgp/lab7/3dgp-lab7-movement.pdf
