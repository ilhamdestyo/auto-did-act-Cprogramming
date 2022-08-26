#
# Makefile designed for use with ctangle, cweave, gcc, and plain TeX.
#
# Copyright (C) 2002-2011, Fredrik Jonsson <http://jonsson.eu>
#
# The CTANGLE program converts a CWEB source document into a C program
# which may be compiled in the usual way. The output file includes #line
# specifications so that debugging can be done in terms of the CWEB source
# file.
#
# The CWEAVE program converts the same CWEB file into a TeX file that may
# be formatted and printed in the usual way. It takes appropriate care of
# typographic details like page layout and the use of indentation, italics,
# boldface, etc., and it supplies extensive cross-index information that it
# gathers automatically.
#
# CWEB allows you to prepare a single document containing all the informa-
# tion that is needed both to produce a compilable C program and to produce
# a well-formatted document describing the program in as much detail as the
# writer may desire.  The user of CWEB ought to be familiar with TeX as well
# as C.
#
PROJECT  = sgfilter
EXAMPLE  = example
FIGURES  = fig0 fig1 fig2 fig3 fig4 fig5 fig6
CTANGLE  = ctangle
CWEAVE   = cweave
CC       = gcc
CCOPTS   = -O2 -Wall -ansi -std=iso9899:1999 -pedantic
LNOPTS   = -lm
TEX      = tex
DVIPS    = dvips
DVIPSOPT = -ta4 -D1200
PS2PDF   = ps2pdf
METAPOST = mpost

# all: $(PROJECT) $(PROJECT).pdf

all: $(PROJECT) $(EXAMPLE) $(FIGURES) $(PROJECT).pdf

$(PROJECT): $(PROJECT).o
	$(CC) $(CCOPTS) -o $(PROJECT) $(PROJECT).o $(LNOPTS)

$(PROJECT).o: $(PROJECT).c
	$(CC) $(CCOPTS) -c $(PROJECT).c

$(PROJECT).c: $(PROJECT).w
	$(CTANGLE) $(PROJECT) $(PROJECT).c

$(PROJECT).pdf: $(PROJECT).ps
	$(PS2PDF) $(PROJECT).ps $(PROJECT).pdf

$(PROJECT).ps: $(PROJECT).dvi
	$(DVIPS) $(DVIPSOPT) $(PROJECT).dvi -o $(PROJECT).ps

$(PROJECT).dvi: $(PROJECT).tex
	$(TEX) $(PROJECT).tex

$(PROJECT).tex: $(PROJECT).w
	$(CWEAVE) $(PROJECT)

example: example.o example.m
	$(CC) $(CCOPTS) -o example example.o $(LNOPTS)
	./example 0.0 > example-0.0.dat
	./example 0.5 > example-0.5.dat
	./example 1.0 > example-1.0.dat
	./example 2.0 > example-2.0.dat
	./sgfilter -m 4 -v -nl 60 -nr 60 -i example-0.0.dat -o example-0.0-f-60.dat
	./sgfilter -m 4 -v -nl 10 -nr 10 -i example-0.0.dat -o example-0.0-f-10.dat
	./sgfilter -m 4 -v -nl 60 -nr 60 -i example-0.5.dat -o example-0.5-f-60.dat
	./sgfilter -m 4 -v -nl 10 -nr 10 -i example-0.5.dat -o example-0.5-f-10.dat
	./sgfilter -m 4 -v -nl 60 -nr 60 -i example-1.0.dat -o example-1.0-f-60.dat
	./sgfilter -m 4 -v -nl 10 -nr 10 -i example-1.0.dat -o example-1.0-f-10.dat
	./sgfilter -m 4 -v -nl 60 -nr 60 -i example-2.0.dat -o example-2.0-f-60.dat
	./sgfilter -m 4 -v -nl 10 -nr 10 -i example-2.0.dat -o example-2.0-f-10.dat

example.o: example.c
	$(CC) $(CCOPTS) -c example.c

example.c: $(PROJECT).w
	$(CTANGLE) $(PROJECT)

example.m:
	@echo "clear all; close all;\
		figure(1);\
		hold on;\
		u=load('example-2.0.dat'); plot(u(:,1),u(:,2),'-b');\
		u=load('example-0.0.dat'); plot(u(:,1),u(:,2),'--k');\
		u=load('example-2.0-f-60.dat'); plot(u(:,1),u(:,2),'-r');\
		u=load('example-2.0-f-10.dat'); plot(u(:,1),u(:,2),'-m');\
		legend('var(f(x))=2.0','f(x)','SG-filtered, nl=nr=60',\
			'SG-filtered, nl=nr=10');\
		hold off;\
		title('Artificial data generated for examples of Savitzky-Golay filtering');\
		xlabel('x');\
		ylabel('f(x)');\
		figure(2);\
		hold on;\
		u=load('example-1.0.dat'); plot(u(:,1),u(:,2),'-b');\
		u=load('example-0.0.dat'); plot(u(:,1),u(:,2),'--k');\
		u=load('example-1.0-f-60.dat'); plot(u(:,1),u(:,2),'-r');\
		u=load('example-1.0-f-10.dat'); plot(u(:,1),u(:,2),'-m');\
		legend('var(f(x))=1.0','f(x)','SG-filtered, nl=nr=60','SG-filtered, nl=nr=10');\
		hold off;\
		title('Artificial data generated for examples of Savitzky-Golay filtering');\
		xlabel('x');\
		ylabel('f(x)');\
		figure(3);\
		hold on;\
		u=load('example-0.5.dat'); plot(u(:,1),u(:,2),'-b');\
		u=load('example-0.0.dat'); plot(u(:,1),u(:,2),'--k');\
		u=load('example-0.5-f-60.dat'); plot(u(:,1),u(:,2),'-r');\
		u=load('example-0.5-f-10.dat'); plot(u(:,1),u(:,2),'-m');\
		legend('var(f(x))=0.5','f(x)','SG-filtered, nl=nr=60','SG-filtered, nl=nr=10');\
		hold off;\
		title('Artificial data generated for examples of Savitzky-Golay filtering');\
		xlabel('x');\
		ylabel('f(x)');">example.m

fig00: example
	@echo "input graph;\
		beginfig(1);\
		draw begingraph(40mm,40mm);\
		setrange(0.0,-4.0,2.5,7.0);\
		pickup pencircle scaled .5pt;\
		gdraw \"example-1.0.dat\" withcolor .6[black,white];\
		pickup pencircle scaled .8pt;\
		gdraw \"example-1.0-f-10.dat\" withcolor black;\
		gdraw \"example-1.0-f-60.dat\" withcolor black;\
		pickup pencircle scaled .25pt;\
		autogrid(itick bot,itick lft);\
		glabel.bot(btex $$ x$$ etex,OUT);\
		glabel.lft(btex $$ y$$ etex,OUT);\
		endgraph; endfig; end" > fig00.mp
		$(METAPOST) fig00.mp
	$(TEX) -jobname=fig00 "\input epsf\nopagenumbers\
		\centerline{\epsfbox{fig00.1}}\bye"
	$(DVIPS) -D1200 -E fig00.dvi -o fig00.eps
	$(PS2PDF) fig00.eps fig00.pdf

fig0: example
	@echo "input graph;\
		beginfig(1);\
		draw begingraph(120mm,50mm);\
		setrange(0.0,-4.0,2.5,7.0);\
		pickup pencircle scaled .5pt;\
		gdraw \"example-1.0.dat\" withcolor .6[black,white];\
		pickup pencircle scaled .8pt;\
		gdraw \"example-1.0-f-10.dat\" withcolor blue;\
		gdraw \"example-1.0-f-60.dat\" withcolor red;\
		pickup pencircle scaled .25pt;\
		autogrid(itick bot,itick lft);\
		glabel.bot(btex $$ x$$ etex,OUT);\
		glabel.lft(btex $$ y$$ etex,OUT);\
		endgraph; endfig; end" > fig0.mp
		$(METAPOST) fig0.mp
	$(TEX) -jobname=fig0 "\input epsf\nopagenumbers\
		\centerline{\epsfbox{fig0.1}}\bye"
	$(DVIPS) -D1200 -E fig0.dvi -o fig0.eps
	$(PS2PDF) fig0.eps fig0.pdf

fig1: example
	@echo "input graph;\
		beginfig(1);\
		draw begingraph(120mm,50mm);\
		setrange(0.0,-2.0,2.5,5.0);\
		pickup pencircle scaled .5pt;\
		gdraw \"example-0.0.dat\" withcolor black;\
		pickup pencircle scaled .25pt;\
		autogrid(itick bot,itick lft);\
		glabel.bot(btex $$ x$$ etex,OUT);\
		glabel.lft(btex $$ y$$ etex,OUT);\
		endgraph; endfig; end" > fig1.mp
		$(METAPOST) fig1.mp
	$(TEX) -jobname=fig1 "\input epsf\nopagenumbers\
		\centerline{\epsfbox{fig1.1}}\bye"
	$(DVIPS) -D1200 -E fig1.dvi -o fig1.eps
	$(PS2PDF) fig1.eps fig1.pdf

fig2: example
	@echo "input graph;\
		beginfig(1);\
		draw begingraph(120mm,50mm);\
		setrange(0.0,-7.0,2.5,7.0);\
		pickup pencircle scaled .5pt;\
		gdraw \"example-2.0.dat\" withcolor black;\
		pickup pencircle scaled .8pt;\
		gdraw \"example-0.0.dat\" withcolor red;\
		gdraw (0.1,-5.2)--(0.3,-5.2) withcolor red;\
		glabel.rt(btex Underlying function $$ g(x)$$ etex,(0.3,-5.2));\
		pickup pencircle scaled .5pt;\
		gdraw (0.1,-6.2)--(0.3,-6.2) withcolor black;\
		glabel.rt(btex $$ g(x)$$ with added Gaussian noise of variance $$ {\rm var}(u(x))=2.0$$ etex,(0.3,-6.2));\
		pickup pencircle scaled .25pt;\
		autogrid(itick bot,itick lft);\
		glabel.bot(btex $$ x$$ etex,OUT);\
		glabel.lft(btex $$ y$$ etex,OUT);\
		endgraph; endfig; end" > fig2.mp
		$(METAPOST) fig2.mp
	$(TEX) -jobname=fig2 "\input epsf\nopagenumbers\
		\centerline{\epsfbox{fig2.1}}\bye"
	$(DVIPS) -D1200 -E fig2.dvi -o fig2.eps
	$(PS2PDF) fig2.eps fig2.pdf

fig3: example
	@echo "input graph;\
		beginfig(1);\
		draw begingraph(120mm,50mm);\
		setrange(0.0,-7.0,2.5,7.0);\
		pickup pencircle scaled .5pt;\
		gdraw \"example-2.0.dat\" withcolor .6[black,white];\
		pickup pencircle scaled .8pt;\
		gdraw \"example-0.0.dat\" dashed evenly withcolor black;\
		gdraw \"example-2.0-f-10.dat\" withcolor blue;\
		gdraw \"example-2.0-f-60.dat\" withcolor red;\
		gdraw (0.1,-3.2)--(0.3,-3.2) dashed evenly withcolor black;\
		glabel.rt(btex Underlying function $$ g(x)$$ etex,(0.3,-3.2));\
		gdraw (0.1,-4.2)--(0.3,-4.2) withcolor .6[black,white];\
		glabel.rt(btex $$ g(x)$$ with added Gaussian noise of variance $$ {\rm var}(u(x))=2.0$$ etex,(0.3,-4.2));\
		gdraw (0.1,-5.2)--(0.3,-5.2) withcolor blue;\
		glabel.rt(btex Filtered with $$ m=4$$ and $$ {\it nl}={\it nr}=10$$ etex,(0.3,-5.2));\
		gdraw (0.1,-6.2)--(0.3,-6.2) withcolor red;\
		glabel.rt(btex Filtered with $$ m=4$$ and $$ {\it nl}={\it nr}=60$$ etex,(0.3,-6.2));\
		pickup pencircle scaled .25pt;\
		autogrid(itick bot,itick lft);\
		glabel.bot(btex $$ x$$ etex,OUT);\
		glabel.lft(btex $$ y$$ etex,OUT);\
		endgraph; endfig; end" > fig3.mp
		$(METAPOST) fig3.mp
	$(TEX) -jobname=fig3 "\input epsf\nopagenumbers\
		\centerline{\epsfbox{fig3.1}}\bye"
	$(DVIPS) -D1200 -E fig3.dvi -o fig3.eps
	$(PS2PDF) fig3.eps fig3.pdf

fig4: example
	@echo "input graph;\
		beginfig(1);\
		draw begingraph(120mm,50mm);\
		setrange(0.0,-7.0,2.5,7.0);\
		pickup pencircle scaled .5pt;\
		gdraw \"example-1.0.dat\" withcolor .6[black,white];\
		pickup pencircle scaled .8pt;\
		gdraw \"example-0.0.dat\" dashed evenly withcolor black;\
		gdraw \"example-1.0-f-10.dat\" withcolor blue;\
		gdraw \"example-1.0-f-60.dat\" withcolor red;\
		gdraw (0.1,-3.2)--(0.3,-3.2) dashed evenly withcolor black;\
		glabel.rt(btex Underlying function $$ g(x)$$ etex,(0.3,-3.2));\
		gdraw (0.1,-4.2)--(0.3,-4.2) withcolor .6[black,white];\
		glabel.rt(btex $$ g(x)$$ with added Gaussian noise of variance $$ {\rm var}(u(x))=1.0$$ etex,(0.3,-4.2));\
		gdraw (0.1,-5.2)--(0.3,-5.2) withcolor blue;\
		glabel.rt(btex Filtered with $$ m=4$$ and $$ {\it nl}={\it nr}=10$$ etex,(0.3,-5.2));\
		gdraw (0.1,-6.2)--(0.3,-6.2) withcolor red;\
		glabel.rt(btex Filtered with $$ m=4$$ and $$ {\it nl}={\it nr}=60$$ etex,(0.3,-6.2));\
		pickup pencircle scaled .25pt;\
		autogrid(itick bot,itick lft);\
		glabel.bot(btex $$ x$$ etex,OUT);\
		glabel.lft(btex $$ y$$ etex,OUT);\
		endgraph; endfig; end" > fig4.mp
		$(METAPOST) fig4.mp
	$(TEX) -jobname=fig4 "\input epsf\nopagenumbers\
		\centerline{\epsfbox{fig4.1}}\bye"
	$(DVIPS) -D1200 -E fig4.dvi -o fig4.eps
	$(PS2PDF) fig4.eps fig4.pdf

fig5: example
	@echo "input graph;\
		beginfig(1);\
		draw begingraph(120mm,50mm);\
		setrange(0.0,-7.0,2.5,7.0);\
		pickup pencircle scaled .5pt;\
		gdraw \"example-0.5.dat\" withcolor .6[black,white];\
		pickup pencircle scaled .8pt;\
		gdraw \"example-0.0.dat\" dashed evenly withcolor black;\
		gdraw \"example-0.5-f-10.dat\" withcolor blue;\
		gdraw \"example-0.5-f-60.dat\" withcolor red;\
		gdraw (0.1,-3.2)--(0.3,-3.2) dashed evenly withcolor black;\
		glabel.rt(btex Underlying function $$ g(x)$$ etex,(0.3,-3.2));\
		gdraw (0.1,-4.2)--(0.3,-4.2) withcolor .6[black,white];\
		glabel.rt(btex $$ g(x)$$ with added Gaussian noise of variance $$ {\rm var}(u(x))=0.5$$ etex,(0.3,-4.2));\
		gdraw (0.1,-5.2)--(0.3,-5.2) withcolor blue;\
		glabel.rt(btex Filtered with $$ m=4$$ and $$ {\it nl}={\it nr}=10$$ etex,(0.3,-5.2));\
		gdraw (0.1,-6.2)--(0.3,-6.2) withcolor red;\
		glabel.rt(btex Filtered with $$ m=4$$ and $$ {\it nl}={\it nr}=60$$ etex,(0.3,-6.2));\
		pickup pencircle scaled .25pt;\
		autogrid(itick bot,itick lft);\
		glabel.bot(btex $$ x$$ etex,OUT);\
		glabel.lft(btex $$ y$$ etex,OUT);\
		endgraph; endfig; end" > fig5.mp
		$(METAPOST) fig5.mp
	$(TEX) -jobname=fig5 "\input epsf\nopagenumbers\
		\centerline{\epsfbox{fig5.1}}\bye"
	$(DVIPS) -D1200 -E fig5.dvi -o fig5.eps
	$(PS2PDF) fig5.eps fig5.pdf

fig6: example
	@echo "input graph;\
		beginfig(1);\
		draw begingraph(120mm,50mm);\
		setrange(0.0,-7.0,2.5,7.0);\
		pickup pencircle scaled .8pt;\
		gdraw \"example-0.0.dat\" dashed evenly withcolor black;\
		gdraw \"example-0.0-f-10.dat\" withcolor blue;\
		gdraw \"example-0.0-f-60.dat\" withcolor red;\
		gdraw (0.1,-3.2)--(0.3,-3.2) dashed evenly withcolor black;\
		glabel.rt(btex Underlying function $$ g(x)$$ etex,(0.3,-3.2));\
		gdraw (0.1,-4.2)--(0.3,-4.2) withcolor blue;\
		glabel.rt(btex Filtered with $$ m=4$$ and $$ {\it nl}={\it nr}=10$$ etex,(0.3,-4.2));\
		gdraw (0.1,-5.2)--(0.3,-5.2) withcolor red;\
		glabel.rt(btex Filtered with $$ m=4$$ and $$ {\it nl}={\it nr}=60$$ etex,(0.3,-5.2));\
		pickup pencircle scaled .25pt;\
		autogrid(itick bot,itick lft);\
		glabel.bot(btex $$ x$$ etex,OUT);\
		glabel.lft(btex $$ y$$ etex,OUT);\
		endgraph; endfig; end" > fig6.mp
		$(METAPOST) fig6.mp
	$(TEX) -jobname=fig6 "\input epsf\nopagenumbers\
		\centerline{\epsfbox{fig6.1}}\bye"
	$(DVIPS) -D1200 -E fig6.dvi -o fig6.eps
	$(PS2PDF) fig6.eps fig6.pdf

clean:
	-rm -Rf $(PROJECT) *~ *.c *.h *.o *.exe *.dat *.pdf *.mp *.trj *.mpx
	-rm -Rf *.tex *.aux *.log *.toc *.idx *.scn *.dvi *.ps *.1 *.eps
	-rm -Rf example *.m

archive:
	make -ik clean
	tar --gzip --directory=../ -cf ../$(PROJECT).tar.gz $(PROJECT)
