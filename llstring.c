#include "llstring.h"
#include <libndls.h>

void debug(unsigned int value) {
	char intstr[(int)((ceil(log10(value))+1)*sizeof(char))];
	sprintf(intstr, "%d", value);
	show_msgbox("Debug", intstr);
}

void init_line_t_ptr(line_t * l) {
	l->vstr = malloc(sizeof(vstring));
	l->next = NULL;
	l->prev = NULL;
}

void insert_after(line_t * node, line_t * new_node) {
	if (node == NULL) return;
	
	if (node->next != NULL) {
		node->next->prev = new_node;
	}
	
	if (new_node != NULL) {
		new_node->prev = node;
		new_node->next = node->next;
	}
	node->next = new_node;
}

void insert_before(line_t * node, line_t * new_node) {
	if (node == NULL) return;
	
	if (node->prev != NULL) {
		node->prev->next = new_node;
	}
	node->prev = new_node;

	if (new_node != NULL) {
		if(new_node->next != NULL) {
			new_node->next->prev = NULL;
		}
		new_node->next = node;
	}
}

line_t * string_to_llist(vstring str) {

	line_t * head = malloc(sizeof(line_t));
	init_line_t_ptr(head);
	line_t * tail = head;

	unsigned int index = 0;

	while (index < str.len) {
		unsigned int old_index = index;
		
		while (index < str.len && str.str[index] != '\n') {
			index++;
		}
		
		if (str.str[index] == '\n') {
			index++;
		}
		
		unsigned int cur_line_len = index - old_index;
		tail->vstr->str = malloc((cur_line_len+1)*sizeof(char));
		tail->vstr->len = (size_t)(cur_line_len);

		for (unsigned int i = 0; i < cur_line_len; i++) {
			tail->vstr->str[i] = str.str[old_index + i];
		}

		line_t * new_node = malloc(sizeof(line_t));
		init_line_t_ptr(new_node);
		insert_after(tail, new_node);
		tail = new_node;
	}

	tail = tail->prev;
	free(tail->next);
	tail->next = NULL;

	return head;
}

vstring llist_to_string(line_t * head) {
	vstring out;

	unsigned int total_chars = 0;

	line_t * cur = head;
	while (cur != NULL) {
		total_chars += cur->vstr->len;
		cur = cur->next;
	}

	out.str = malloc((total_chars+1)*sizeof(char));
	out.len = (size_t)(total_chars-1);

	cur = head;
	unsigned int main_index = 0;
	
	while (cur != NULL) {
		for (unsigned int sub_index = 0; sub_index < cur->vstr->len; sub_index++) {
			out.str[main_index] = cur->vstr->str[sub_index];
			main_index++;
		}
		cur = cur->next;
	}

	out.str[main_index] = '\0';

	return out;
}
