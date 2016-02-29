/*
    Упорядочить по длине строки, читаемые из стандартного входного потока.
    Вывести их на печать в порядке увеличения длины.
    Для решения задачи использовать односвязный динамический список.

    Если кратко, то односвязный списов представляет собой набор элементов, в котором у каждого из них содержится ссылка на следующий. 
    Графически можно представить в следующем виде:

        [value1] -> [value2] -> [value3] -> [value4] -> [value5] -> ...

    Здесь под "valueX" - понимается какой-то набор данных, которые нужно хранить (встроенные типы данных, структуры и прочая).
    Для работы со списком в самом простом случае достаточно хранить указатель, который будет указывать на его начало:

        [value1] -> [value2] -> [value3] -> [value4] -> [value5] -> ...
        ^
        |
      list_ptr
    и затем просто проходить по всем элемента до конца, используя ссылки.

    Вставка узлов зависит от требуемого действия и может быть реализована в любое место списка.

    В C++ (да и С) узел списка удобно представлять в виде структуры, содержащей указатель на саму себя:
        struct Node {
            // тут объявляются поля для данных

            Node *next; // указатель на следующий элемент списка.
        };


    *Отличие от пособия*:
        -> используется C++ вместо C
        -> функции для работы со списком выделены в отдельную библиотеку

    Скомпилировать можно либо путём добавления всех файлов в проект CodeBlocks.
    Либо используя окно командной строки (cmd.exe в Windows).

    Для второго способа необходимо:
        - открыть командную строку;
        - узнать полный путь к компилятору (например: "C:\Program Files (x86)\CodeBlocks\MinGW\bin\mingw32-g++.exe" - при дефолтной установке CodeBlocks)
        - перейти к директорию с исходными файлами
        - ввести команду вида:
            "C:\Program Files (x86)\CodeBlocks\MinGW\bin\mingw32-g++.exe" -std=c++11 -o 10_1.ex 10_1_main.cpp 10_1_listlib.cpp
            
            * в Linux дистрибутивах проще:
            g++ -std=c++11 -o 10_1.ex 10_1_main.cpp 10_1_listlib.cpp
*/

#include <iostream>

#include "10_1_listlib.h"

using namespace std;
using namespace listlib;


int main()
{
    Cell *cell_list{nullptr}, *new_cell;

    cout << "Enter lines to collect (empty line to exit)" << endl;

    while (true) {
        new_cell = listlib::create_cell();
        if (new_cell == nullptr)
            break;

        cell_list = insert_to_list(cell_list, new_cell);
    }

    cout << "Printing tree:" << endl;
    print_list(cell_list);
    clear_list(cell_list);
    return 0;
}
