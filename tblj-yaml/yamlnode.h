#ifndef _YAML_NODE_H
#define _YAML_NODE_H

/* The three basic types of YAML nodes */
typedef enum _yaml_node_type_e {
	SEQUENCE,
	SCALAR,
	MAPPING
} yaml_node_e;

typedef struct _yaml_node_s {
	yaml_node_e node_type;

	union {
		/* Sequence content */
		
		/* Scalar content */

		/* Mapping content */
	} content;

	struct tag {
		char *name; /* Tag name */
		
	} tag;
} yaml_node_t;

#endif/*_YAML_NODE_H*/
