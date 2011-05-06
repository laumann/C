#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
 * write - a simple program that writes the given arguments to a file
 * or to stdout (default is stdout).
 */

#define OVERWRITE	(1<<0)
#define APPEND		(1<<1)

const char write_usage_string[] =
  "write [--help] [--output|--append <FILE>] [<args>]";

const char write_help_string[] =
  "There are three ways of using this tool. Either write to stdout (default),\n"
  "writing to a file (overwriting it if it exists) or append to a file. The options\n"
  "for writing/appending to a file are mutually exclusive meaning you cannot specify\n"
  "-o and -a at the same time.\n\n"
  "-o overwrites the file if it exists and creates the file and creates it if it doesn't.\n\n"
  "-a appends to the indicated file, but it expects this file to exist (no free magic).";

const char write_cmd_list[] =
  "Options:\n"
  "  -a, --append <FILE>    Append to FILE.\n"
  "  -o, --output <FILE>    Write to FILE (overwrite if it exists).\n"
  "  -h, --help             Get help.";

/*
 * prefixcmp shamelessly stolen from strbuf.c in git
 */
int
prefixcmp(const char *str, const char *prefix)
{
  /* printf("Given '%s' and '%s'\n", str, prefix); */
  for (; ; str++, prefix++) {
    if (!*prefix) {
      /* printf("Returning: 0\n"); */
      return 0;
    }
    else if (*str != *prefix) {
      /* printf("Returning: %i\n", ((unsigned char)*prefix - (unsigned char)*str)); */
      return (unsigned char)*prefix - (unsigned char)*str;
    }
  }
}

/*
 * Write the given array to stream.
 */
int
write_ary_to_stream(FILE *stream, char **ary, int sz)
{
  int i;
  fprintf(stream, "%s", ary[0]);
  for (i=1; i<sz; i++)
    fprintf(stream, " %s", ary[i]);
  fprintf(stream, "\n");	    

  return 0;
}

int
write_ary(char **ary, int sz, int DEST, const char *dest)
{
  FILE *fp;
  
  if (!DEST) {
     write_ary_to_stream(stdout, ary, sz);
  }
  else if (DEST & OVERWRITE) {
     if ((fp = fopen(dest, "w+")) != NULL) {
       write_ary_to_stream(fp, ary, sz);
     }
     else {
       fprintf(stderr, "Could not write to file: %s\n", dest);
       return 1;
     }
     return fclose(fp);
  }
  else if (DEST & APPEND) {
    if ((fp = fopen(dest, "a+")) != NULL) {
      write_ary_to_stream(fp, ary, sz);
    }
    else {
      fprintf(stderr, "Could not append to file: %s\n", dest);
    }
    return fclose(fp);
   }
  else {
    fprintf(stderr, "Error: For some reason, I don't know where to write to. This cannot be good. See 'write --help'.\n");
    return 1;
  }
  return 0;
}

/* main method */
int
main(int argc, char **argv)
{
  if (argc==1) {
    /* No arguments, give help */
    printf("Usage: %s\n\n", write_usage_string);
    printf("%s\n", write_cmd_list);
    exit(1);
  }

  int i,j=0;
  int DEST=0; /* 0=write to stdout (default), 1=overwrite FILE,
	       2=append to FILE, 3=both were specified (conflict) */
  const char *arg, *dest;
  char *str_ary[BUFSIZ];

  /* Handle command line arguments. Iterate through commands - pick up
     on -o, -a and -h */
  for (i=1; i<argc; ++i) {

    arg = argv[i];

    /* command? */
    if (prefixcmp(arg, "-") == 0) {

      arg++;

      if (!strcmp(arg, "h") || !strcmp(arg, "-help")) {
	/* User requested help - give it */
	printf("Usage: %s\n\n", write_usage_string);
	printf("%s\n\n", write_help_string);
	printf("%s\n", write_cmd_list);
	return 0;
      }
      else if (!strcmp(arg, "o") || !strcmp(arg, "-output")) {
	if (i+1==argc) {
	  fprintf(stderr, "Error: No output file indicated. See 'write --help'. Exiting.\n");
	  exit(1);
	}

	dest = argv[++i];
	DEST = DEST | OVERWRITE;
      }
      else if (!strcmp(arg, "a") || !strcmp(arg, "-append")) {
	if (i+1==argc) {
	  fprintf(stderr, "Error: No file for appending indicated. See 'write --help'. Exiting.\n");
	  exit(1);
	}
	dest = argv[++i];
	DEST = DEST | APPEND;
      }
      else {
	/* Not a recognized command - complain */
	fprintf(stderr, "write: Unknown option '-%s'. See 'write --help'.\n", arg);
	exit(1);
      }

      /* Check here if both -o and -a were specified (and give an error if so). */
      if (DEST & OVERWRITE & APPEND) {
	fprintf(stderr, "Error: You cannot specify both --output and --append!\n\n");
	printf("%s\n", write_cmd_list);
	exit(DEST);
      }
    }
    else {
      /* Not a command, but something to output, collect it. */
      /* printf("Collecting '%s' for outputting.\n", arg); */
      str_ary[j] = (char*)arg;
      j++;
    }
    /* printf("%s ", argv[i]); */
  }

  exit(write_ary(str_ary, j, DEST, dest));
}
