#ifndef _LINKED_LIST_H
#define _LINKED_LIST_H

struct linked_list_node {
  struct linked_list_node *next, *prev;
  void *elm;
};

struct linked_list {
  struct linked_list_node *first;
  int size;
};

struct linked_list      *linked_list_new();
struct linked_list_node *linked_list_new_node();
struct linked_list_node *linked_list_new_string_node(char *);
       int               linked_list_insert(struct linked_list*, struct linked_list_node*);
struct linked_list_node *linked_list_pop(struct linked_list *);
       void              linked_list_print(struct linked_list*);
#endif
