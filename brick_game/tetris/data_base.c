#include "./include/data_base.h"
#include <stdio.h>
#include <ncurses.h>

int _readToFile(DataBase_t *this) {
  int high_score = 0;
  FILE *file = fopen(this->file_name, "r");
  if (file) {
    mvprintw(18, 20, "write file %s", this->file_name);
    fscanf(file, "high_score: %d", &high_score);
    fclose(file);
  }

  mvprintw(17, 18, "write file %s", this->file_name);
  return high_score;
}

void _writeToFile(DataBase_t *this, int high_score) {
  FILE *file = fopen(this->file_name, "w");
  if (file) {
    fprintf(file, "high_score: %d", high_score);
    fclose(file);
  } 
}

DataBase_t initDatabase(char *file_name) {
  mvprintw(40, 30, "%s", file_name);
  DataBase_t db = {
    .read = _readToFile,
    .write = _writeToFile
  };
  sprintf(db.file_name, "%s", file_name);
  return db;
}

