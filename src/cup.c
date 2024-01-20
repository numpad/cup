#include <stdio.h>
#include <string.h>
#include <tree_sitter/api.h>

//
// defines
//

#define HIGHLIGHT printf("\x1b[31m\x1b[1m");
#define NOHIGHLIGHT printf("\x1b[0m");

//
// forward decls
//

TSLanguage *tree_sitter_cup(void);
static int fs_readfile(const char *path, char **output, long *size);
static void print_source_code(TSNode node, const char *source, long source_len);

//
// logic
//

int main(int argc, char **argv) {
	if (argc <= 1) {
		printf("usage:\t%s <in.cup>\n", argv[0]);
		return 1;
	}

	TSParser *parser = ts_parser_new();
	ts_parser_set_language(parser, tree_sitter_cup());

	
	char *source;
	long source_len;
	fs_readfile(argv[1], &source, &source_len);

	TSTree *tree = ts_parser_parse_string(parser, NULL, source, (unsigned int)source_len);
	TSNode root_node = ts_tree_root_node(tree);

	print_source_code(root_node, source, source_len);

	free(source);

	ts_tree_delete(tree);
	ts_parser_delete(parser);
	return 0;
}

//
// private impls
//

static int fs_readfile(const char *path, char **output, long *size) {
	if (size == NULL) {
		return 1;
	}

	FILE *fp = fopen(path, "r");
	if (fp == NULL) {
		return 1;
	}

	fseek(fp, 0, SEEK_END);
	*size = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	
	*output = malloc(*size * sizeof(char) + 1);
	fread(*output, sizeof(char), *size, fp);
	(*output)[*size] = '\0';

	fclose(fp);

	return 0;
}

static void print_source_code(TSNode node, const char *source, long source_len) {
    if (ts_node_is_null(node)) return;
	if (ts_node_is_error(node)) {
		printf("Error in the following code:\n");
		uint32_t start_byte = ts_node_start_byte(node);
		uint32_t end_byte = ts_node_end_byte(node);
		fwrite(&source[start_byte], 1, end_byte - start_byte, stdout);
		return;
	}

    uint32_t child_count = ts_node_child_count(node);
	if (child_count == 0) {
		uint32_t start_byte = ts_node_start_byte(node);
		uint32_t end_byte = ts_node_end_byte(node);
		fwrite(&source[start_byte], 1, end_byte - start_byte, stdout);

		// handle whitespaces
		if (end_byte + 1 < source_len) {
			if (source[end_byte] == ' ' || source[end_byte] == '\n') {
				putchar(source[end_byte]);
			}
		} else if (end_byte + 2 < source_len) {
			if (source[end_byte] == '\r' || source[end_byte + 1] == '\n') {
				putchar(source[end_byte]);
				putchar(source[end_byte + 1]);
			}
		}
	} else {
		for (uint32_t i = 0; i < child_count; i++) {
			TSNode child = ts_node_child(node, i);
			const char *type = ts_node_type(child);

			const int is_optionally_parenthesized = (strstr(type, "optionally_parenthesized_expression") != NULL);

			if (is_optionally_parenthesized) {
				HIGHLIGHT;
				putchar('(');
				NOHIGHLIGHT;
			}
			print_source_code(child, source, source_len);
			if (is_optionally_parenthesized) {
				HIGHLIGHT;
				putchar(')');
				NOHIGHLIGHT;
			}
		}
	}
}

