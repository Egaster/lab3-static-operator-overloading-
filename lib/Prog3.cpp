#include "Prog3.h"

namespace Static {

    bool correctGetInt(int &a) {
        std::cin >> a;
        if (!std::cin.good()) { // проверка на правильность ввода
            std::cin.clear();
            std::cin.ignore();
            return false;
        } else {
            return true;
        }
    }

    int getNum() {
        int number;
        while (!correctGetInt(number)) {
            std::cout << "Wrong number! Enter number again!" << std::endl;
        }
        return number;
    }

    int dialog(const char* msgs[], int N)
    {
        char* errmsg = (char*)"";
        int rc;
        int i;
        do {
            puts(errmsg);
            errmsg = (char*)"You are wrong. Repeate, please!";
            for (int i = 0; i < N; ++i)
                puts(msgs[i]);
            puts("Make your choice: —>");
            rc = getNum();
        } while (rc < 0 || rc >= N);
        return rc;
    }

    BinVec::BinVec() noexcept { // пустой конструктор
        length = 0;
    }

    void transferToBin(int &a, char *data, int &length, int M) {  /// исправить
        int i = 0;
        char z;
        if (a >= 0) {
            z = '0';
        } else {
            z = '1';
        }
        do {
            if (i + 1 >= M) { // 1 ячейка знака числа 1 - или 0 +
                throw std::out_of_range("This number too big!"); /// tut!!!
            }
            if (a % 2 == 0) {
                data[i] = '0';
            } else {
                data[i] = '1';// записываем 1 или 0
            }
            a = a / 2;
            i++;
        } while (a != 0);
        length = i;
        data[M - 1] = z;
    }


    BinVec::BinVec(std::string const &a) {
        int ptr = std::stoi(a);
        transferToBin(ptr, data, length, M);
    }

    BinVec::BinVec(int a) {
        transferToBin(a, data, length, M);
    }

    void copy(char const k[], char m[], int M, int length) noexcept { // обычное копирование чисел
        for (int i = 0; i < length; i++) {
            m[i] = k[i];
        }
        int s = M - 1;
        m[s] = k[s];
    }

    BinVec::BinVec(BinVec const &a) noexcept { // копирующий конструктор
        copy(a.data, data, BinVec::M, a.length);
        length = a.length;
    }

    BinVec::BinVec(BinVec &&a) noexcept {    // перемещающий конструктор
        copy(a.data, data, BinVec::M, a.length);
        length = a.length;
        a.length = 0;
    }

    void addition(char const a[], char b[], int len, int max) { // заполнение для дополнительного кода
        bool flag = true; // запоминаем единицу, которую хотим добавить, чтобы 2 раза не проходить массив
        int k = 0, i; // k нужна для выявления переполнения при переходе из доп кода в прямой
        for (i = 0; i < len; i++) {
            if (flag) {
                if (a[i] == '0') {
                    b[i] = '0';
                    k++;
                } else {
                    b[i] = '1';
                    flag = false;
                }
            } else {
                if (a[i] == '0') {
                    b[i] = '1';
                } else {
                    b[i] = '0';
                    k++;
                }
            }
        }
        if (a[max - 1] == '1' && i == k) {
            throw std::invalid_argument("Доп -> прямой: случилось переполнение");
        }
        b[max - 1] = a[max - 1];
    }

    char BinVec::signum() const {
        return data[M - 1];
    }

    BinVec BinVec::additionalCode() const {
        BinVec rev;
        if (signum() == '0') {  ///
            copy(data, rev.data, length, M);
        } else {
            addition(data, rev.data, length, M);
        }
        rev.length = length;
        std::cout <<"Dop code: "<< std::endl;
        return rev;
    }

    void BinVec::output(std::ostream &a) const noexcept {
        if (length != 0) {
            a << data[M - 1];
            for (int i = length - 1; i >= 0; i--) {
                a << data[i];
            }
            a << std::endl;
        }
    }


    BinVec &BinVec::operator=(BinVec &&a) noexcept {
        copy(a.data, data, BinVec::M, a.length);
        length = a.length;
        a.length = 0;
        return *this;
    }

    std::ostream &operator<<(std::ostream &a, BinVec const &number) noexcept { // перегрузка оператора <<
        number.output(a);
        return a;
    }

    void oneBitSum(char const &a, char const &b, char &m, int &flag) {
        if (a == '0' && b == '0') {
            if (flag) {
                m = '1';
            } else {
                m = '0';
            }
            flag = 0;
        } else {
            if (a == '1' && b == '1') {
                if (flag) {
                    m = '1';
                } else {
                    m = '0';
                }
                flag = 1;
            } else {
                if (flag) {
                    m = '0';
                    flag = 1;
                } else {
                    m = '1';
                }
            }
        }
    }

    std::string &BinVec::output(std::string &str) const {
        if (length != 0) {
            str.resize(length + 1);
            str.at(0) = data[M - 1];
            for (int i = length - 1, j = 1; i >= 0; i--, j++) {
                str.at(j) = data[i];
            }
        } else{
            str.clear();
        }
        return str;
    }

    void add(char const a[], char const b[], char s[], int const &len, int &i, int max, int &flag) noexcept {
        if (b[max - 1] == '0') { // во время суммирования смотрим на знак меньшего числа
            for (; i < len; i++) {
                oneBitSum('0', a[i], s[i], flag);
            }
        } else {
            for (; i < len; i++) {
                oneBitSum('1', a[i], s[i], flag);
            }
        }
    }

    void bitSum(char const a[], char const b[], char s[], int const &len_a, int const &len_b, int &len, int max) {
        int fl = 0;
        int len_k, i;
        if (len_a > len_b) {
            len_k = len_b;
        } else {
            len_k = len_a;
        }
        for (i = 0; i < len_k; i++) { // суммируем без битового знака и до разряда меньшего числа
            oneBitSum(a[i], b[i], s[i], fl);
        }
        if (len_a > len_b) {
            add(a, b, s, len_a, i, max, fl);
        } else {
            add(b, a, s, len_b, i, max, fl); // расширение до одного разряда
        }
        if ((fl && a[max - 1] == '0' && b[max - 1] == '0') ||
            (!fl && a[max - 1] == '1' && b[max - 1] == '1')) {
            if (i < max - 2) { // можем расширить разрядную сетку для ответа
                if (a[max - 1] == '0') {
                    s[i] = '1';
                    fl = 0;
                } else {
                    s[i] = '0';
                    fl = 1;
                }
                i++;
            } else { // иначе ответ выйдет на знаковую часть -> ответ уже не будет правильным
                throw std::out_of_range("Overflow");
            }
        }
        oneBitSum(a[max - 1], b[max - 1], s[max - 1], fl); // считаем знак двоичного числа
        len = i;
    }

    BinVec smallIncludingOr(BinVec const &num1, BinVec const &num2) {
        BinVec vec;
        bitSum(num1.data, num2.data, vec.data, num1.length, num2.length, vec.length,
               BinVec::M); // суммируем биты + смотрим на переполнение
        return vec;
    }

    BinVec operator+(BinVec const &num1, BinVec const &num2) {
        return smallIncludingOr(num1, num2);
    }

    void includingOr() { /// tut
        std::string ch1, ch2;
        std::cout << "Введите первое число" << std::endl;
        if (!(std::cin >> ch1)) {
            std::cout << "error" << std::endl;
            return;
        }
        std::cout << "Введите второе число" << std::endl;
        if (!(std::cin >> ch2)) {
            std::cout << "error" << std::endl;
            return;
        }
        BinVec num;
        BinVec num1(ch1), num2(ch2);
        try {
            num = num1 + num2;
            std::cout << num;
        } catch (std::out_of_range const &err2) {
            std::cout << err2.what() << std::endl;
        }
    }


    void oneBitAnd(char const &a, char const &b, char &m) {
        if (a == '0' && b == '0') {

            m = '0';
        } else {
            if (a == '1' && b == '1') {
                m = '1';
            } else {
                m = '0';
            }
        }
    }


    void bitAnd(char const a[], char const b[], char s[], int const &len_a, int const &len_b, int &len, int max) {
        int len_k, i;
        if (len_a > len_b) {
            len_k = len_b;
        } else {
            len_k = len_a;
        }
        for (i = 0; i < len_k; i++) { // суммируем без битового знака и до разряда меньшего числа
            oneBitAnd(a[i], b[i], s[i]);
        }
        oneBitAnd(a[max - 1], b[max - 1], s[max - 1]); // считаем знак числа
        len = i;
    }

    BinVec smallIncludingAnd(BinVec const &num1, BinVec const &num2) {
        BinVec vec;
        bitAnd(num1.data, num2.data, vec.data, num1.length, num2.length, vec.length,
               BinVec::M); // суммируем биты + смотрим на переполнение
        return vec;
    }

    BinVec operator&(BinVec const &num1, BinVec const &num2) {
        return smallIncludingAnd(num1, num2);
    }

    void includingAnd() { /// tut
        std::string ch1, ch2;
        std::cout << "Введите первое число" << std::endl;
        if (!(std::cin >> ch1)) {
            std::cout << "error" << std::endl;
            return;
        }
        std::cout << "Введите второе число" << std::endl;
        if (!(std::cin >> ch2)) {
            std::cout << "error" << std::endl;
            return;
        }
        BinVec num;
        BinVec num1(ch1), num2(ch2);
        try {
            num = num1 & num2;
            std::cout << num;
        } catch (std::out_of_range const &err2) {
            std::cout << err2.what() << std::endl;
        }
    }


    void oneBitXOR(char const &a, char const &b, char &m) {
        if (a == '0' && b == '0') {
            m = '0';
        } else {
            if (a == '1' && b == '1') {
                m = '0';

            } else {
                m = '1';
            }
        }
    }

    void addXOR(char const a[], char const b[], char s[], int const &len, int &i, int max) noexcept {
        if (b[max - 1] == '0') { // во время суммирования смотрим на знак меньшего числа
            for (; i < len; i++) {
                oneBitXOR('0', a[i], s[i]);
            }
        } else {
            for (; i < len; i++) {
                oneBitXOR('1', a[i], s[i]);
            }
        }
    }


    void bitXOR(char const a[], char const b[], char s[], int const &len_a, int const &len_b, int &len, int max) {
        int len_k, i;
        if (len_a > len_b) { // тк когда 1 и 0 -> 1
            len_k = len_b;
        } else {
            len_k = len_a;
        }
        for (i = 0; i < len_k; i++) { // суммируем без битового знака и до разряда меньшего числа
            oneBitXOR(a[i], b[i], s[i]);
        }
        if (len_a > len_b) {
            addXOR(a, b, s, len_a, i, max);
        } else {
            addXOR(b, a, s, len_b, i, max); // расширение до одного разряда
        }
        oneBitXOR(a[max - 1], b[max - 1], s[max - 1]); // считаем знак числа
        len = i;
    }

    BinVec smallIncludingXOR(BinVec const &num1, BinVec const &num2) {
        BinVec vec;
        bitXOR(num1.data, num2.data, vec.data, num1.length, num2.length, vec.length,
               BinVec::M); // суммируем биты + смотрим на переполнение
        return vec;
    }

    BinVec operator^(BinVec const &num1, BinVec const &num2) {
        return smallIncludingXOR(num1, num2);
    }

    void includingXOR() { /// tut
        std::string ch1, ch2;
        std::cout << "Введите первое число" << std::endl;
        if (!(std::cin >> ch1)) {
            std::cout << "error" << std::endl;
            return;
        }
        std::cout << "Введите второе число" << std::endl;
        if (!(std::cin >> ch2)) {
            std::cout << "error" << std::endl;
            return;
        }
        BinVec num;
        BinVec num1(ch1), num2(ch2);
        try {
            num = num1 ^ num2;
            std::cout << num;
        } catch (std::out_of_range const &err2) {
            std::cout << err2.what() << std::endl;
        }
    }


    int BinVec::lengthNew(BinVec const &a) const {
        int s = 0;
        while (data[s] == '0') {
            s++;
        }
        return s;
    }

    void BinVec::output2(std::ostream &a) const noexcept {
        int s, k;
        k = lengthNew(*this);
        s = length - k;
        if (s != 0) {
            std::cout <<"New line: "<< std::endl;
            if (signum() == '1') {
                a << data[M - 1];
                for (int i = length - 1; i >= k; i--) {
                    a << data[i];
                }
                a << std::endl;
            }
            if (signum() == '0') {
                for (int i = length - 1; i >= k; i--) {
                    a << data[i];
                }
            }
        }
    }


    BinVec& BinVec::operator=(BinVec const &a) noexcept{
        if (this != &a){ // проверяем, не является ли это тем же самым
            copy(a.data, data, a.length, BinVec::M);
            length = a.length;
        }
        return *this;
    }

}