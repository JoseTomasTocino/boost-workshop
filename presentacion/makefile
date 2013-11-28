# makefile por Noelia Sales Montes

NOM = presentacion
PRES = ${NOM}.tex
PDF = ${NOM}.pdf

all: clean ${PDF}

pdf: ${PDF}

${PDF}: ${PRES}
	pdflatex ${PRES}
	pdflatex ${PRES}
	latex_count=5 ; \
	while egrep -s 'Recompilando (LaTeX|para obtener las referencias correctamente)' ${NOM}.log && [ $$latex_count -gt 0 ] ;\
	    do \
	      echo "Recompilando latex...." ;\
	      pdflatex ${PRES} ;\
	      latex_count=`expr $$latex_count - 1` ;\
	     done


clean: 
	rm -f *.ps *.dvi *.aux *.toc *.idx *.ind *.ilg \
	*.log *.out *.snm *.nav *.vrb *~
