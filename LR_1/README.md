# Лабораторная работа №1 — абстрактные структуры данных

Программа работает с массивом, односвязным списком, двусвязным списком, стеком и очередью на C++ и Go. Дерево варианта 3 — Complete Binary Tree — сделано на C++, как указано в задании. Используются структуры и отдельные функции, классов нет.

## Файлы проекта

```text
LR1_Project/
  cpp/
    main.cpp          запуск и чтение аргументов командной строки
    commands.cpp      выполнение команд
    commands.h        объявление обработчика команд
    structures.h      описания структур и функций
    registry.cpp      хранение структур по именам
    array.cpp         массив
    singly_list.cpp   односвязный список
    doubly_list.cpp   двусвязный список
    stack.cpp         стек
    queue.cpp         очередь
    complete_tree.cpp Complete Binary Tree
    storage.cpp       чтение и запись файла
    storage.h         объявления функций чтения и записи
  go/
    main.go           запуск программы
    commands.go       выполнение команд
    storage.go        чтение и запись файла
    array.go          массив
    singly_list.go    односвязный список
    doubly_list.go    двусвязный список
    stack.go          стек
    queue.go          очередь
    go.mod
  data.txt            файл данных
  build_cpp.bat       сборка C++ в Windows
  build_go.bat        сборка Go в Windows
```

## Сборка и запуск

Команды запускаются из корневой папки проекта. Нужны установленный компилятор `g++` для C++ и Go версии 1.20 или новее для Go. В Windows можно запустить соответствующий `.bat` файл.

### C++

```text
g++ -std=c++17 -Wall -Wextra -pedantic -I cpp cpp/main.cpp cpp/registry.cpp cpp/array.cpp cpp/singly_list.cpp cpp/doubly_list.cpp cpp/stack.cpp cpp/queue.cpp cpp/complete_tree.cpp cpp/storage.cpp cpp/commands.cpp -o lab1.exe
lab1.exe --file data.txt --query "MPUSH nums 10"
lab1.exe --file data.txt --query "MPUSH nums 20"
lab1.exe --file data.txt --query "PRINT nums"
```

### Go

```text
cd go
go build -o lab1-go.exe .
lab1-go.exe --file go_data.txt --query "MPUSH nums 10"
lab1-go.exe --file go_data.txt --query "PRINT nums"
```

Каждый запуск выполняет одну команду. Сначала программа загружает структуры из файла, а после изменения записывает их обратно. Если файла нет, он создаётся при первой изменяющей команде.

## Команды

Формат запуска: `ПРОГРАММА --file ФАЙЛ --query "КОМАНДА ИМЯ [АРГУМЕНТЫ]"`. Индексы массива и списков начинаются с нуля. Для вставки до или после значения сначала указывается значение существующего элемента, затем новое значение.

| Структура | Команды |
|---|---|
| Массив | `MPUSH имя значение`, `MINSERT имя индекс значение`, `MGET имя индекс`, `MDEL имя индекс`, `MSET имя индекс значение`, `MLEN имя`, `MPRINT имя` |
| Односвязный список | `FPUSH имя значение` (в конец), `FHEAD имя значение` (в начало), `FBEFORE имя целевое значение новое значение`, `FAFTER имя целевое значение новое значение`, `FDEL имя значение`, `FDELHEAD имя`, `FDELTAIL имя`, `FDELBEFORE имя значение`, `FDELAFTER имя значение`, `FMEMBER имя значение`, `FGET имя индекс`, `FPRINT имя` |
| Двусвязный список | Те же действия с первой буквой `L`: `LPUSH`, `LHEAD`, `LBEFORE`, `LAFTER`, `LDEL`, `LDELHEAD`, `LDELTAIL`, `LDELBEFORE`, `LDELAFTER`, `LMEMBER`, `LGET имя индекс`, `LPRINT имя`; `LREVERSE имя` выводит список в обратном порядке |
| Стек | `SPUSH имя значение`, `SPOP имя`, `SGET имя`, `SPRINT имя` |
| Очередь | `QPUSH имя значение`, `QPOP имя`, `QGET имя`, `QPRINT имя` |
| Complete Binary Tree (только C++) | `TINSERT имя значение`, `TGET имя значение`, `TCHECK имя`, `TPRINT имя` |

Команда `PRINT имя` также выводит структуру с этим именем. Для Complete Binary Tree удаление заменено проверкой `TCHECK`, как требует вариант 3.

## Строковые значения

Массив, оба списка, стек и очередь хранят строки: `std::string` в C++ и `string` в Go. В функциях поиска, вставки и удаления по значению используются строки. Индексы, размеры и вместимость остаются `int`. Дерево хранит `int`.

Значение в командной строке — одно слово без пробелов и переводов строки. Например: `apple`, `яблоко`, `hello_123`, `001`. Запись `001` сохраняется именно как строка, без превращения в число 1. Для имён структур также используйте одно слово.

Примеры запуска на Linux после сборки:
```bash
./lab1 --file strings.txt --query "MPUSH fruit яблоко"
./lab1 --file strings.txt --query "MINSERT fruit 0 груша"
./lab1 --file strings.txt --query "MGET fruit 1"
./lab1 --file strings.txt --query "FPUSH names Тимур"
./lab1 --file strings.txt --query "FMEMBER names Тимур"
./lab1 --file strings.txt --query "LPUSH colors red"
./lab1 --file strings.txt --query "LAFTER colors red blue"
./lab1 --file strings.txt --query "SPUSH history page1"
./lab1 --file strings.txt --query "SPOP history"
./lab1 --file strings.txt --query "QPUSH tasks task1"
./lab1 --file strings.txt --query "QPOP tasks"
./lab1 --file strings.txt --query "TINSERT tree 42"
```

В файле данные сохраняются в прежнем формате, например `M fruit груша яблоко`. Старые числовые значения линейных структур читаются как строки. Используйте отдельные файлы данных для Go и C++, если в C++ сохраняется дерево: Go-версия дерево не обрабатывает.
