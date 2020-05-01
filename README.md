### Задача 2. Порядок обхода (4 балла)

Дано число `N < 10^6` и последовательность целых чисел из  `[-2^31..2^31]` длиной `N`.
Требуется построить бинарное дерево, заданное наивным порядком вставки.
Т.е., при добавлении очередного числа K в дерево с корнем root, если `root→Key ≤ K`, то узел `K` добавляется в правое поддерево `root`; иначе в левое поддерево `root`.

**Требования**: Рекурсия запрещена. Решение должно поддерживать передачу функции сравнения снаружи.

 Выведите элементы в порядке **pre-order** (сверху вниз).

|   in    |   out   |
| -------- -------- |
| 3       | 2 1 3   |
| 2 1 3   |         |
| ------- | ------- |
| 3       | 1 2 3   |
| 1 2 3   |         |
| ------- | ------- |
| 3       | 3 1 2   |
| 3 1 2   |         |
| ------- | ------- |
| 4       | 3 1 2 4 |
| 3 1 4 2 |         |
| ------- | ------- |
