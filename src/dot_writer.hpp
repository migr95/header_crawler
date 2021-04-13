#ifndef DOT_WRITER_HPP
#define DOT_WRITER_HPP

#include <string>
#include <vector>

struct tree_node
{
    std::string key;
    std::vector<tree_node> childs;
};

void bst_print_dot_aux(tree_node* node, FILE* stream);

void bst_print_dot(tree_node* tree, FILE* stream);

#endif //DOT_WRITER_HPP
