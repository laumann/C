#ifndef _YAML_PARSER_H
#define _YAML_PARSER_H


#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void	parse_yaml_stream(FILE *stream);
void	parse_yaml_document(char *f);

#endif/*_YAML_PARSER_H*/
