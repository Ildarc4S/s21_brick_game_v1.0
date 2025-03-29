/**
 * @file data_base.c
 * @brief Реализация работы с базой данных рекордов
 */

#include "./include/data_base.h"

/**
 * @brief Внутренняя функция чтения рекорда из файла
 * @param self Указатель на объект базы данных
 * @return Значение рекорда или DB_MIN_HIGH_SCORE если файла нет
 *
 * @details Формат файла:
 * Строка 1: "high_score: [значение]"
 *
 * @warning Не потокобезопасна - нет блокировки файла
 */
int _readToFile(DataBase_t *self) {
  int high_score = DB_MIN_HIGH_SCORE;
  FILE *file = fopen(self->file_name, "r");
  if (file) {
    fscanf(file, "high_score: %d", &high_score);
    fclose(file);
  }
  return high_score;
}

/**
 * @brief Внутренняя функция записи рекорда в файл
 * @param self Указатель на объект базы данных
 * @param high_score Значение для сохранения
 *
 * @details Формат файла:
 * Строка 1: "high_score: [значение]"
 *
 * @warning Полностью перезаписывает существующий файл
 * @note Создает файл если он не существует
 */
void _writeToFile(DataBase_t *self, int high_score) {
  FILE *file = fopen(self->file_name, "w");
  if (file) {
    fprintf(file, "high_score: %d", high_score);
    fclose(file);
  }
}

/**
 * @brief Инициализация базы данных
 * @return Настроенный объект базы данных
 *
 * @details Устанавливает функции для операций чтения/записи
 * и сохраняет имя файла для последующих операций.
 *
 * @warning Имена файлов длиннее DB_FILE_NAME_SIZE будут обрезаны
 */
DataBase_t initDataBase(char *file_name) {
  DataBase_t db = {.read = _readToFile, .write = _writeToFile};
  snprintf(db.file_name, DB_FILE_NAME_SIZE, "%s", file_name);
  return db;
}
