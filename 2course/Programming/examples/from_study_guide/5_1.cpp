/*
    Определить функцию для вычисления по формуле Ньютона приблежённого значения
    арифметического квадратного корня. В формуле Ньютона итерации определяются
    по формуле r_[n+1] = (r_[n] + x / r_[n]) / 2

    Версия для C++
*/
#include <iostream>
#include <cmath>
#include <clocale>

const double PRECISION = 0.000000001;

/*
    Объявление функции с именем newton_root.
    Она принимает один аргумент типа double и возращает значение типа double.
    Объявление без описания тела функции (блок кода в фигурных скобках) - позволяет
    делать вызов этой функции в любом месте, до определения самой функции.
*/
double newton_root(double );

int main()
{
    std::setlocale(LC_ALL, "RUS");

    double x, result;

    std::cout << "Введите x: ";
    std::cin >> x;

    // вызываем функцию, передавая ей в качестве аргумента переменную x и сохраняя возращённый ею результат в переменной result
    result = newton_root(x);
    std::cout << "Корень из x: " << result;

    return 0;
}

/*
    Ниже производится определение функции. В отличие от объявления, здесь обязательно указание имени передаваемых аргументов.
    Имя аргумента используется только в теле функции.

    Стоит заметить, что отделение объявления и определения функции не является обязательным при записи всего в одном файле.
*/
double newton_root(double num)
{
    double r_cur, r_next = num;

    /*
        Действительные числа (float, double) лучше сравнивать с некоторой заранее определённой
        точностью по числу знаков после запятой.
        num == 0.0 - не гарантирует, что сравнение будет истино даже если num = 0;
    */
    if (num < PRECISION)
        return 0.0;

    do {
        r_cur = r_next;
        r_next = (r_cur + num / r_cur) / 2;
    } while (fabs(r_cur - r_next) > PRECISION);

    return r_next;
}
