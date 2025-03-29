/**
 * @file data_base.h
 * @brief Модуль для работы с рекордами игры
 */

#ifndef DATA_BASE_H
#define DATA_BASE_H

#include <stdio.h>

/**
 * @def Максимальная длина имени файла
 */
#define DB_FILE_NAME_SIZE 256

/**
 * @def Минимальное значение рекорда
 */
#define DB_MIN_HIGH_SCORE 0

/**
 * @struct DataBase_t
 * @brief Структура базы данных для хранения рекордов
 *
 * Позволяет читать и записывать рекорды в файл.
 * Использует указатели на функции для гибкости реализации.
 */
typedef struct _data_base {
  char file_name[DB_FILE_NAME_SIZE];  ///< Имя файла с рекордами

  /**
   * @brief Чтение рекорда из файла
   * @param db Указатель на объект базы данных
   * @return Значение рекорда
   */
  int (*read)(struct _data_base *db);

  /**
   * @brief Запись рекорда в файл
   * @param db Указатель на объект базы данных
   * @param data Значение рекорда для сохранения
   */
  void (*write)(struct _data_base *db, int data);
} DataBase_t;

/**
 * @brief Инициализация базы данных
 * @param file_name Имя файла для хранения рекордов
 * @return Инициализированный объект базы данных
 *
 * @note Файл будет создан при первой записи, если не существует
 */
DataBase_t initDataBase(char *file_name);

#endif  // DATA_BASE_H
