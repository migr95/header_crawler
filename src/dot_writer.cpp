#include <iostream>
#include "dot_writer.hpp"

void bst_print_dot_aux(tree_node* node, FILE* stream)
{
    for(auto& child : node->childs)
    {
        fprintf(stream, "    \"%s\" -> \"%s\";\n", node->key.c_str(), child.key.c_str());
        bst_print_dot_aux(&child, stream);
    }
}

void bst_print_dot(tree_node *tree, FILE* stream)
{
    fprintf(stream, "strict digraph BST {\n");
    fprintf(stream, "    node [fontname=\"Arial\"];\n");

    if (!tree)
        fprintf(stream, "\n");
    else if (tree->childs.empty())
        fprintf(stream, "    \"%s\";\n", tree->key.c_str());
    else
        bst_print_dot_aux(tree, stream);

    fprintf(stream, "}\n");
}
