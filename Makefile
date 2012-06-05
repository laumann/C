ASCIIDOC=asciidoc
XMLTO=xmlto
RM=rm -rfv

PROJECTS= begin
PROJECTS+=binarytree
PROJECTS+=bits
PROJECTS+=cbook
PROJECTS+=ch8
PROJECTS+=curse
PROJECTS+=debug
PROJECTS+=linkedlist
PROJECTS+=pattern
PROJECTS+=progress
PROJECTS+=redblacktree
PROJECTS+=tblj-yaml
PROJECTS+=trigrapher
PROJECTS+=UVa
PROJECTS+=write

all:
	@for p in $(PROJECTS); do make -C $$p; done

man: doc
	@man -l laumann.1

doc: README.txt
	$(ASCIIDOC) -b docbook -d manpage README.txt
	$(XMLTO) man README.xml

clean:
	@$(RM) laumann.1 README.xml

clean-all:
	@for p in $(PROJECTS); do make -C $$p clean; done

.PHONY: clean clean-all all man doc
