#include <stdio.h>
#include <stdlib.h>
#include "yamlparser.h"

int
main(int argc, char **argv)
{
	argc--; argv++;
	FILE *yaml_document;

	if (argc < 1) {
		/* Report usage error and quit */
		fprintf(stderr, "Usage: ./main <file1>...\n");
		exit(1);
	}

	for ( ; argc ; argv++) {
		yaml_document = fopen(*argv, "r");

		if (!yaml_document) {
			fprintf(stderr, "Failed to open document %s. Skipping.\n%s", *argv, (--argc) ? "\n" : "");
			continue;
		}

		parse_yaml_stream(yaml_document);
		
		fclose(yaml_document);

		if (--argc)
			printf("\n\n");
	}
	exit(0);
}
