/*
    !Все файлы с номерами меньше текущего в одной директории - обязательны к прочтению в порядке возрастания номеров!

    Как и с простыми/составными типами данных, для классов могут использоваться переменные-указатели.
    А с помощью указателей, можно создавать/удалять объекты классов динамически. Рассмотрим следующий
    класс:
        class TestCl
        {
            int num;
            char symb;

        public:
            TestCl(int _num, char _symb) : num{_num}, symb{_symb}
            {}

            TestCl() : num{9}, symb{'+'}
            {}

            void change_num(int another)
            {
                num += another;
            }

            int get_num()
            {
                return num;
            }
        };

    Для динамического создания классов должен быть использован оператор "new" (а не malloc/calloc/realloc из
    языка C):
        // объявляем переменную указатель нашего типа данных
        TestCl *obj1;

        // динамически выделяем память под один объект.
        // std::nothrow здесь используется, чтобы в случае неудачного выделения памяти был возращён nullptr
        // В данном случае
        obj1 = new (std::nothrow) TestCl;

    Оператор new для класса делает два действия:
        1) выделяет память под все поля класса
        2) вызывает конструктор класса.
    В строчке "obj1 = new (std::nothrow) TestCl;" - new вызывает конструктор по умолчанию (который без параметров, см. выше)

    Когда конструкторов у класса несколько, можно в явном виде указать оператору new, какая версия нам требуется:
        TestCl *obj2 = new TestCl(5, '$'), *obj3 = new TestCl();
        // std::nothrow - не указан, для obj2 вызван конструктор с параметрами, для obj3 - конструктор по умолчанию

    Доступ к метода класса для конкретного указателя-на-объект осуществляется такими же способами, как
    и для указателей на простые типы данных:
        // или через разыменование:
        cout << (*obj2).get_num();

        // или через оператор ->:
        obj3->change_num(-9);

    Чтобы удалить объект класса, который был выделен динамически - используется оператор delete:
        delete obj1;
        delete obj2;
        delete obj3;
*/

#include <iostream>
#include <cmath>

using namespace std;

/*
    Продолжение разработки класса FillingMachine.

    Задача для этого класса была сформулирована так: хотим получить класс, описывающий некоторое
    разливочное устройство (резервуар) для жидкости. Основными характеристиками такой штукенции являются:
        * вместимость       - максимальный объём, измеряем в действительных числах
        * текущий уровень   - каков запас жидкости в данный момент. Также измеряется в действительных числах

    А методы класса - будут объяснены ниже. Сам класс будет везде написан по следующему принципу:
        идёт объявление класса (поля + объявления методов), затем функция main, и только после неё
        реализация всех методов класса.

    Изменения:
        -> добавлен конструктор по умолчанию
*/
class FillingMachine
{
    double capacity;            // максимальныя вместимость
    double current_volume;      // текущий объём

public:
    FillingMachine();
    FillingMachine(double init_value);
    FillingMachine(const FillingMachine& other);

    // возращает вместимость конкретного объекта
    double get_capacity();

    // проверяем, есть ли жидкость в объекте. Возращаем булево значение (истина / ложь, они же - true / false).
    bool is_empty();
    // обратная проверка - не заполнен ли объект
    bool is_full();

    // снова заполняем наш резервуар до максимальной вместимости
    void restore_full_volume();


    /*
        Пробуем запросить требуемый объём из резервуара.
        В случае, если запрошенный объём больше текущего количества -
        возращается отрицательное число (как способ обнаружить и обработать ошибку).
    */
    double take_volume(double required_vol);
};

int main()
{
    FillingMachine *fm1, *fm2;

    fm1 = new (nothrow) FillingMachine(10);
    if ( fm1 == nullptr ) {
        cerr << "Error with memory allocation";
        exit(1);
    }

    fm2 = new (nothrow) FillingMachine;
    if ( fm2 == nullptr ) {
        cerr << "Error with memory allocation";
        exit(1);
    }

    cout << "take 4.5 volume from fm1 object. The returned value is " << fm1->take_volume(4.5) << endl;

    cout.setf(ios_base::boolalpha);
    cout << "Is fm1 empty: " << fm1->is_empty() << endl;
    cout << "Is fm1 full: " << fm1->is_full() << endl;

    //cout << ld << endl;

    double result = fm1->take_volume(5.5);
    if (result < 0) {
        cout << "No enough volume at device" << endl;
    }

    cout << "Is fm1 empty: " << fm1->is_empty() << endl;
    cout << "Is fm2 full: "<< fm2->is_full() << endl;

    // освобождаем память под объекты
    delete fm1;
    delete fm2;

    return 0;
}

double FillingMachine::get_capacity()
{
    return capacity;
}

bool FillingMachine::is_empty()
{
    return current_volume <= 0;
}

bool FillingMachine::is_full()
{
    if ( current_volume <= 0 ) {
        return false;
    } else {
        return abs(capacity - current_volume) < 0.0000001;
    }
}

void FillingMachine::restore_full_volume()
{
    current_volume = capacity;
}

double FillingMachine::take_volume(double required_vol)
{
    if ( required_vol > current_volume ) {
        return -1.0;
    }

    current_volume -= required_vol;
    return required_vol;
}

/*
    Констурктор с параметром: устанавливаем одновременно и вместимость, и текущее значение объёма.
*/
FillingMachine::FillingMachine(double initial_cap) :
    capacity{initial_cap}, current_volume{initial_cap}
{
    // Вывод только для понимания работы программы, конечно же в нём смысла нет в реальном классе
    cout << "Constructor FillingMachine(double initial_cap) called" << endl;
}

/*
    Констуруктор копирования
*/
FillingMachine::FillingMachine(const FillingMachine& other) : capacity{other.capacity}, current_volume{other.current_volume}
{
    // Вывод только для понимания работы программы, конечно же в нём смысла нет в реальном классе
    cout << "Copy constructor called" << endl;
}

/*
    Конструктор по умолчанию.
    Пусть присваивает значение 25.0 для capacity и current_volume
*/
FillingMachine::FillingMachine() : capacity{25.0}, current_volume{25.0}
{
    cout << "Default constructor called" << endl;
}
