#for html generation, following tools are required: hevea and imagen (part of hevea package)

#Main Latex source, without any extension. 
MAIN_SOURCE = main
#all sources, with extensions
ALL_SOURCES = \
baseLangage.tex\
behavior.tex\
format.tex\
installation.tex\
introISS.tex\
main.tex\
memoire.tex\
microArchitecture.tex\
syntax.tex\
timing.tex

IMAGE_DIR = ../common/images
#############################################################
### Normal pdf output
#############################################################
pdf: $(MAIN_SOURCE).pdf
ALL_AUX = $(ALL_SOURCES:.tex:.aux)

$(MAIN_SOURCE).pdf: $(MAIN_SOURCE).tex $(ALL_SOURCES) $(MAIN_SOURCE).aux $(ALL_AUX)
	pdflatex $(MAIN_SOURCE).tex

%.aux: %.tex
	pdflatex $(MAIN_SOURCE).tex

#############################################################
### Hevea TEX to HTML translator.
#############################################################

MAIN_SOURCE_HTML = harmless
html: $(MAIN_SOURCE_HTML).html 

#rebuild patch with the following command:
#diff -u main.tex harmless.tex > hevea.patch
# The patch is used to:
# - comment the lstlisting macros
# - uncomment the use of a CSS file.
$(MAIN_SOURCE_HTML).tex: $(MAIN_SOURCE).tex
	@cp $(MAIN_SOURCE).tex $(MAIN_SOURCE_HTML).tex
	@patch $(MAIN_SOURCE_HTML).tex < hevea.patch

#hevea call: 
#  -fix    => rerun hevea until fix point
#  png.hva => use png files instead of gif
$(MAIN_SOURCE_HTML).html: $(MAIN_SOURCE_HTML).tex $(ALL_SOURCES)
	mkdir -p img
	hevea -I $(IMAGE_DIR) png.hva -fix $(MAIN_SOURCE_HTML).tex

clean:
	@rm -rf $(MAIN_SOURCE_HTML).haux $(MAIN_SOURCE_HTML).html $(MAIN_SOURCE_HTML).htoc $(MAIN_SOURCE_HTML).image.out $(MAIN_SOURCE_HTML).image.tex img/$(MAIN_SOURCE_HTML)[0-9][0-9][0-9].png $(MAIN_SOURCE_HTML).tex *~
	@rm -rf *.aux $(MAIN_SOURCE).toc $(MAIN_SOURCE).log $(MAIN_SOURCE).out $(MAIN_SOURCE).pdf
