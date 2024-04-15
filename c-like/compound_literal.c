#include <stdio.h>

// [C99:6.5.2.5]

struct llist {
  int val;
  struct llist *next;
};

#define cons(x, y) (struct llist[]){x, y}

void print(struct llist *head) {
  while (head && head->next) {
    printf("%d->", head->val);
    head = head->next;
  }
  head && printf("%d\n", head->val);
}

int main() {
  struct llist *head = cons(9, cons(5, cons(4, cons(7, NULL))));
  print(head);

  printf("%p\n", head);
  printf("%p\n", &head);
  return 0;
}
