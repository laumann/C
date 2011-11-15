ASCIIDOC=asciidoc
XMLTO	=xmlto
RM	=rm -rf

MANDOC	=README

man: doc
	man -l laumann.1

doc: README.txt
	$(ASCIIDOC) -b docbook -d manpage README.txt
	$(XMLTO) man README.xml

clean:
	$(RM) laumann.1 README.xml