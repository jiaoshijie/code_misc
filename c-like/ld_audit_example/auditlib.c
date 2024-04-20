#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#define _GNU_SOURCE
#define __USE_GNU
#include <link.h>

// man 7 rtld-audit

const char *preloaded;
uintptr_t *preloaded_cookie = NULL;

// __attribute__((constructor)) static void init(void) {
//   printf("loaded from LD_AUDIT\n");
// }

unsigned int la_version(unsigned int version) {
  printf("loaded from LD_AUDIT\n");
  preloaded = getenv("LD_PRELOAD");
  return version;
}

char *la_objsearch(const char *name, uintptr_t *cookie, unsigned int flag) {
  // if (NULL != preloaded && strcmp(name, preloaded) == 0) {
  //   fprintf(stderr, "Disabling the loading of a 'preload' library: %s\n", name);
  //   return NULL;
  // }
  return (char *)name;
}

unsigned int la_objopen(struct link_map *map, Lmid_t lmid, uintptr_t *cookie) {
  if (NULL != preloaded && strcmp(map->l_name, preloaded) == 0) {
    fprintf(stderr, "A 'preload' library is about to load: %s. Following its function binding\n", map->l_name);
    preloaded_cookie = cookie;

    return LA_FLG_BINDTO | LA_FLG_BINDFROM;
  }
  return 0;
}

uintptr_t la_symbind64(Elf64_Sym *sym, unsigned int ndx, uintptr_t *refcook, uintptr_t *defcook, unsigned int *flags, const char *symname) {
  if (refcook == preloaded_cookie) {
    fprintf(stderr, "Function '%s' is intercepted\n", symname);
  }
  return sym->st_value;
}
