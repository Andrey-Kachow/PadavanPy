# Нахождение выхода из лабиринта
Задача: Найти путь из точки A в точку B в лабиринте.
Дан файл `maze.txt` следующего содержания:
```
###############
A   #         #
# ### ####### #
#   # #   # # #
### # # # # # #
#   #   # #   #
# ####### #####
#   #     #   #
### # ### # # #
#   #   #   # #
# ####### ### #
# #     # # # #
# ### # # # # #
#     #   #   B
###############
```
Символ `'#'` означает стены, `' '` (пробел) обозначает туннели, по которым можно ходить, а символы `'A'` и `'B'` означают позицию начала и конца пути.
Необходимо:
1) Написать программу, которая прочитает данный файл и сохранит лабиринт в виде массива-строки.
2) Реализует структуру очередь, элементами которой будут структура или указатель на структуру точки в пути.
3) Используя Поиск в ширину реализовать нахождение пути из точки A в точку B.
4) Вывести на экран лабиринт с закрашенными клетками пути

## Руководство к выполнению задачи

### Шаг 1. Сохранение игрового поля - лабиринта.
Лабиринт представлен в виде квадрата 15x15 клеток, но задача должна уметь решать лабиринты поизвольных размеров. Поэтому необходимо прочитать файл и понять размер выделяемого буфера, который нужно выделить с помощью функции `malloc`. Разрешено допустить, что поле будет квадратным, поэтому можно догадаться о размере буфера, прочитав первую строчку файла, например с помощью `fgets`.
Как пример, можно использовать следующие глобальные переменные для хранения:
```
char * maze_buffer;
int maze_buffer_width; // для получения размера буфера можно возвести ширину в квадрат.
```
Можно также упразднить допущение о квадратной форме лабиринта и прочитать файл дважды.
Один раз для понимания ширины и высоты буфера, глядя на количество строк и длину строки текстового файла.
Такой более гибкий подход и усложнение задачи приветствуется.
```
char * maze_buffer;
int maze_width;
int maze_height; // Размер буфера = ширина * высота
```

### Шаг 2. Реализация структуры очереди.
Очередь должна хранить в себе элементы, которые представляют собой шаги пути от входа в лабиринт к выходу.
Структура шага, или позиции на пути обязаны иметь данные, позволяюшие знать посещаемое местоположение лабиринта, а также ссылку на местоположение, откуда пришли.
Например можно использовать что-то вроде приведенного ниже.
```
struct path_position {
    int y;
    int x;
    struct path_position *previous_position;
};

struct path_queue {
  // ...
  struct path_position **array; // указатель на массив указателей на элементы очереди
};
```
Примечание: Вместо массива указателей на `struct path_position` можно использовать массив структур.
В этом случае не нужно будет использовать `malloc` для создания каждого `struct path_position`.

#### Подзадача 2.1 Адаптируйте структуру очередь для хранения элементов
1) Напишите функцию-конструктор, создающую очередь. Например `queue_create`
2) Релизуйте операции `add`, `poll`, `is_empty`.

### Шаг 3. Алгоритм BFS для нахождения выхода из лабиринта

0) Создать очередь
1) Создать точку старта в лабиринт ('A') и добавить ее в очередь.
2) Пока в очереди не осталось точек пути:
   * Взять точку-позицию `current_position` из очереди.
   * Если всякая соседняя точка (выше, ниже, левее, правее) не является стеной и раньше не встречалась на пути(*):
     - Добавить эту точку в очередь.
   * Если `current_position` является выходом из лабиринта, "закрасить" все предыдущие позиции, заменив символ пробела на `'-'` (например)

(*) - сосед встречался на пути, если `x,y` соседа совпадает с `x,y` у аттрибута `previous_position`, то есть `current_position` или у предыдуще. При этом нужно проверить все previous posiitons, так как предыдущие точки ссылаются на другие предыдущие точки и так до начала пути.

### Шаг 4. Вывести лабиринт на экран.
В качестве усложнения задачи можно записать пройденный лабиринт в файл, путь к которому указан в `argv`.