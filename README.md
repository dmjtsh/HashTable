# 💥Dimas Hash Table Research💥
## Описание

Это исследование Хэш-Таблицы является частью курсов Системного Программирования в МФТИ.

В нем я хотел исследовать работу Хэш-Таблицы в зависимости от разных Хэш-Функций, а так же я хотел показать, как с помощью знания **ASM x86** можно ускорить ее работу.

## Часть 1. Принцип Работы Хэш-Таблицы

## Часть 2. Тест Хэш-Функций

### Zero Hash

<img src="assets/ZeroHash.jpg" width="600">

$$ D = 1468,75$$

### Strlen Hash

<img src="assets/StrlenHash.jpg" width="600">

$$ D = 266,87$$

### AsciiCodeSum Hash (301 elem)

<img src="assets/AsciiCodeSumHash301.jpg" width="600">

$$ D = 3,23 $$

### AsciiCodeSum Hash (101 elem)

<img src="assets/AsciiCodeSumHash101.jpg" width="600">

$$ D = 11,49 $$

### Dimas Hash

<img src="assets/DimasHash.jpg" width="600">

$$ D = 3,5 $$

### CRC32 Hash

<img src="assets/CRC32Hash.jpg" width="600">

$$ D = 3,13 $$

## Часть 3. Ускорение Хэш-Таблицы

### Ускорение Intrinsic'ами

<img src="assets/first_opt1.png" width="700">

<img src="assets/first_opt2.png" width="700">

|     **N измерения**     |    **1**   |   **2**   |   **3**   |   **4**   |   **5**   | **Среднее Значение**         |
|:-----------------------:|:----------:|:---------:|:---------:|:---------:|:---------:|--------------------------|
| **N тактов CPU, NoOpt** | 1010470110 | 979717050 | 977260500 | 982267980 | 986959350 |$$ 987334998 \pm 0.13 * 10^8 $$|
|  **N тактов CPU, Opt**  |  261537660 | 260254081 | 259941030 | 262473540 | 259767900 | $$ 260794842 +- 0.11 * 10^8 $$ |

Оптимизировали в 3,78 раз

### Ускорение ASM вставкой

<img src="assets/second_opt1.png" width="700">

💘 **Dmit DREC MIPT 2024**
