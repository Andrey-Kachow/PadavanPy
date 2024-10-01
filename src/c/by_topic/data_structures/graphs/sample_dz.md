# DZ:

Ответы должны быть краткие. Не нужно строчить сочинения. Задание должно занять не больше часа-полтора.

# 1. Стеки и Очереди
прочитать про стэк и очереди. А также подготовить краткие ответы на вопросы. Советую записать в текстовом файле или тетрадке-заметках, но буду спрашивать устно вначале следующего занятия.

* что такое LIFO
```
Last In First Out
```

* что такое FIFO
```
First In First Out
```

* структура очередь (Queue), какие основные операции существуют. Перечислить таковые.

(Например у схожей структуры стэка Stack их три основных: push, pop и peek. Можно выделить жополнительные is_empty и is_full, size. Таким же образом перечислить операции очереди)

```
add (append, push_back, put, insert)
poll (pop, pop_front, take, next_task)
is_empty
size (len, length)
```

# 2. Интерфейсы. Начало
Подумайте о том, в чем отличие абстрактной структуры данных от конкретной реализации. Абстракции так же известны под термином интерфейс. В задании graph_traversal.c как устроена реализация стека, а в чем заключается сам интерфейс?
```
Интерфейс -- набор функций-методов работы с абстрактной структурой данных
Реализация -- код функций или конкретные алгоритмы и набор переменных, обеспечивающих работу структуры. 
```

# 3. Графы. 
Помимо матричного представления графоф (adjacency matrix) существует еще два вида (для произвольной формы графа).

* Массив пар узлов, обозначающий связи
* Adjacency Lists - массив списков, где список под индексом i содержит индексы всех узлов, связаных с узлом i.

Реализуйте граф схемы городов из задания graph_traversal.c в виде массива пар узлов, обозначающих связи.

В качестве челленджа попробуйте реализовать тотже граф в виде Adjacency lists. С какими трудностями столкнулись в языке Си? Если не удалось, попробуйте на Python.



# Классная работа (так же известная, как замечательная работа):

## Очереди и Стеки:

Соотнести понятия LIFO и FIFO c структурами Стека и Очереди

## Графы:

Какие графы или информацию сводимую к графам лучше представлять в виде матрицы смежности, а какие в виде списка смежности или списка пар?
Примечание: Структура связи двух узлов может хранить дополнительные данные.
Примечаени: Могут быть альтернативные варианты хранения связей узлов графа.

* Схема железнодорожных станций Московского метро.
* Комментарии и threads в соцсети. Взаимосвязь между тем, какой комментарий опубликован под каким постом или комментарием (комментировать можно не только пост, но и комментарий).
* Статусы дружбы, подписок пользователей в социальной сети Вконтакте.
* Веса связей между нейронами нейросети, например чат GPT.
* Карта игрового поля игры в шахматы, шашки, пэкмэн и танчики

## Кодирование:

* Задача -> DFS vs BFS
* Реализовать очередь
* Релизовать стек или адаптировать имеющийся
* Династия романовых -- кто нгаследник?

```
/*
 * Romanov Dynasty - Male Descendants of Emperor Paul I (Grandchildren Included)
 *                   (Generated with Chat GPT)
 * 
 * Emperor Paul I (1754–1801) married Sophie Dorothea of Württemberg (Maria Feodorovna)
 * ├── 1. Alexander I (1777–1825), Emperor of Russia
 * │      - Married Louise of Baden (Elisabeth Alexeievna)
 * │      - No male issue
 * │
 * ├── 2. Konstantin Pavlovich (1779–1831), Grand Duke of Russia
 * │      - Married twice, no legitimate male issue
 * │
 * ├── 3. Nicholas I (1796–1855), Emperor of Russia
 * │      - Married Charlotte of Prussia (Alexandra Feodorovna)
 * │      - Male Issue:
 * │        ├── 1. Alexander II (1818–1881), Emperor of Russia
 * │        │      - Married Marie of Hesse (Maria Alexandrovna)
 * │        │      - Male Issue:
 * │        │        ├── Alexander III (1845–1894), Emperor of Russia
 * │        │        │      - Married Dagmar of Denmark (Maria Feodorovna)
 * │        │        │      - Male Issue:
 * │        │        │        ├── Nicholas II (1868–1918), Emperor of Russia
 * │        │        │        ├── Grand Duke George Alexandrovich (1871–1899)
 * │        │        │        └── Grand Duke Michael Alexandrovich (1878–1918)
 * │        │        │
 * │        │        └── Grand Duke Vladimir Alexandrovich (1847–1909)
 * │        │              - Married Duchess Marie of Mecklenburg-Schwerin
 * │        │              - Male Issue:
 * │        │                ├── Grand Duke Kirill Vladimirovich (1876–1938)
 * │        │                ├── Grand Duke Boris Vladimirovich (1877–1943)
 * │        │                └── Grand Duke Andrei Vladimirovich (1879–1956)
 * │        │
 * │        ├── Grand Duke Konstantin Nikolayevich (1827–1892)
 * │        │      - Married Alexandra of Saxe-Altenburg
 * │        │      - Male Issue:
 * │        │        ├── Grand Duke Nicholas Konstantinovich (1850–1918)
 * │        │        ├── Grand Duke Konstantin Konstantinovich (1858–1915)
 * │        │        ├── Grand Duke Dmitry Konstantinovich (1860–1919)
 * │        │        └── Grand Duke Vyacheslav Konstantinovich (1862–1879)
 * │        │
 * │        ├── Grand Duke Nicholas Nikolaevich (1831–1891)
 * │        │      - Married Alexandra of Oldenburg
 * │        │      - Male Issue:
 * │        │        ├── Grand Duke Nicholas Nikolaevich (1856–1929)
 * │        │        └── Grand Duke Peter Nikolaevich (1864–1931)
 * │        │
 * │        └── Grand Duke Michael Nikolaevich (1832–1909)
 * │              - Married Princess Cecilie of Baden
 * │              - Male Issue:
 * │                ├── Grand Duke Nicholas Mikhailovich (1859–1919)
 * │                ├── Grand Duke Michael Mikhailovich (1861–1929)
 * │                ├── Grand Duke George Mikhailovich (1863–1919)
 * │                └── Grand Duke Alexander Mikhailovich (1866–1933)
 * │
 * ├── 4. Michael Pavlovich (1798–1849), Grand Duke of Russia
 * │      - Married Charlotte of Württemberg (Elena Pavlovna)
 * │      - No male issue
 * │
 * └── 5. Grand Duke Konstantin Pavlovich (1827–1892)
 *        - Married Alexandra of Saxe-Altenburg
 *        - Male Issue:
 *        ├── Grand Duke Nicholas Konstantinovich (1850–1918)
 *        ├── Grand Duke Konstantin Konstantinovich (1858–1915)
 *        ├── Grand Duke Dmitry Konstantinovich (1860–1919)
 *        └── Grand Duke Vyacheslav Konstantinovich (1862–1879)
 */
```