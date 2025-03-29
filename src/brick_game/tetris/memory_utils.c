/**
 * @file memory_utils.c
 * @brief Реализация работы с памятью для игрового поля
 */

#include "./include/memory_utils.h"

/**
 * @brief Создает и инициализирует игровое поле
 * @return Указатель на созданное поле или NULL при ошибке
 *
 * @details Алгоритм работы:
 * 1. Выделяет память под массив указателей
 * 2. Для каждой строки выделяет память под ячейки
 * 3. При ошибке освобождает всю выделенную память
 * 4. Все ячейки заполняются нулями через calloc()
 *
 * @code
 * int **field = newField(10, 20);
 * if (field == NULL) {
 *     // обработка ошибки
 * }
 * @endcode
 */
int **newField(int width, int height) {
  int error_code = MEMORY_UTIL_OK;
  int **field = (int **)calloc(height, sizeof(int *));
  if (field == NULL) {
    error_code = MEMORY_UTIL_ERROR;
  }

  for (int i = 0; i < height && error_code != MEMORY_UTIL_ERROR; i++) {
    field[i] = (int *)calloc(width, sizeof(int));
    if (field[i] == NULL) {
      error_code = MEMORY_UTIL_ERROR;
    }
  }

  if (error_code) {
    freeField(&field, height);
    field = NULL;
  }

  return field;
}

/**
 * @brief Корректно освобождает память игрового поля
 *
 * @details Алгоритм работы:
 * 1. Проверяет валидность входных параметров
 * 2. Последовательно освобождает каждую строку
 * 3. Освобождает массив указателей
 * 4. Устанавливает исходный указатель в NULL
 *
 * @code
 * int **field = newField(10, 20);
 * // ... использование поля ...
 * freeField(&field, 20);
 * // теперь field == NULL
 * @endcode
 */
void freeField(int ***field, int height) {
  if (!*field || !field) {
    return;
  }

  for (int i = 0; i < height; i++) {
    free((*field)[i]);
    (*field)[i] = NULL;
  }

  free(*field);
  *field = NULL;
}
