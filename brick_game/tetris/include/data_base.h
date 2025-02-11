#ifndef DATA_BASE_H
#define DATA_BASE_H

typedef struct _data_base {
  char file_name[256];

  int (*read)(struct _data_base *);
  void (*write)(struct _data_base *, int);
} DataBase_t;

DataBase_t initDatabase(char *file_name);

#endif
