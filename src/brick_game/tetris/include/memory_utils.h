/**
 * @file memory_utils.h
 * @brief Модуль работы с динамической памятью для игрового поля
 */

#ifndef MEMORY_UTILS_H
#define MEMORY_UTILS_H

#include <stdlib.h>

/**
 * @def Код ошибки при работе с памятью
 * @note Возвращается при неудачном выделении памяти
 */
#define MEMORY_UTIL_ERROR 1

/**
 * @def Код успешного выполнения операции
 */
#define MEMORY_UTIL_OK 0

/**
 * @brief Создает двумерный массив для игрового поля
 * @param width Ширина поля (количество столбцов)
 * @param height Высота поля (количество строк)
 * @return Указатель на созданное поле или NULL при ошибке
 *
 * @warning Требует обязательного освобождения через freeField()
 * @note Все ячейки инициализируются нулями
 */
int **newField(int width, int height);

/**
 * @brief Освобождает память игрового поля
 * @param field Указатель на указатель на поле
 * @param height Высота поля (количество строк)
 *
 * @details Безопасно обрабатывает NULL-указатели
 * @note После вызова указатель field устанавливается в NULL
 */
void freeField(int ***field, int height);

#endif  // MEMORY_UTILS_H
