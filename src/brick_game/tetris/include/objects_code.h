/**
 * @file objects_code.h
 * @brief Заголовочный файл с определениями кодов объектов и режимов паузы
 */

#ifndef OBJECTS_CODE
#define OBJECTS_CODE

/**
 * @enum ObjectCode_t
 * @brief Коды объектов игрового поля
 *
 * Определяет все возможные типы объектов, которые могут находиться на игровом
 * поле. Отрицательные значения используются для служебных объектов.
 */
typedef enum {
  OBJECT_CODE_AIR = -2,   ///< Воздух/пустое пространство
  OBJECT_CODE_WALL = -1,  ///< Стена/граница поля

  OBJECT_CODE_TETRAMINO_I = 1,  ///< Тетромино I-формы (палка)
  OBJECT_CODE_TETRAMINO_O = 2,  ///< Тетромино O-формы (квадрат)
  OBJECT_CODE_TETRAMINO_T = 3,  ///< Тетромино T-формы (Т-образное)
  OBJECT_CODE_TETRAMINO_S = 4,  ///< Тетромино S-формы (зигзаг)
  OBJECT_CODE_TETRAMINO_Z = 5,  ///< Тетромино Z-формы (обратный зигзаг)
  OBJECT_CODE_TETRAMINO_J = 6,  ///< Тетромино J-формы (Г-образное)
  OBJECT_CODE_TETRAMINO_L = 7,  ///< Тетромино L-формы (обратное Г-образное)
} ObjectCode_t;

/**
 * @enum PauseMode_t
 * @brief Режимы работы игры (включая паузу)
 *
 * Определяет все возможные состояния игры, включая стандартные режимы
 * и специальные состояния (пауза, завершение игры и т.д.)
 */
typedef enum {
  PAUSE_MODE_PAUSE = 1,      ///< Игра поставлена на паузу
  PAUSE_MODE_CONTINUE = 2,   ///< Игра продолжается (активный режим)
  PAUSE_MODE_START = 3,      ///< Начальное состояние (меню или стартовый экран)
  PAUSE_MODE_GAME_OVER = 4,  ///< Игра завершена (проигрыш)
  PAUSE_MODE_EXIT = 5,       ///< Выход из игры
  PAUSE_MODE_WIN = 6         ///< Победа в игре (если предусмотрена)
} PauseMode_t;

#endif  // OBJECTS_CODE
