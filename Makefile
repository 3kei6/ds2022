make:
	g++ -o test main.cpp

report:
	xelatex report.tex
	rm report.aux
	rm report.log
