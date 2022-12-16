#include "BBT_tree.h"

int main()
{
  BBT_tree root;
  std::vector<int> Array = { 9, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
  root.insert_array(Array);
  root.inorder_tree();
  fputc('\n', stdout);
  return 0;
}
