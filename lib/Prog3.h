

#ifndef UNTITLED8_PROG3_H
#define UNTITLED8_PROG3_H

#include <iostream>

namespace Static {

    class BinVec {
    public:
        int lengthNew(BinVec const &a) const;

        char signum() const;
        BinVec() noexcept; // пустой конструктор инициализации экземпляров и массивов экземпляров класса по умолчанию
        BinVec (BinVec  const &a) noexcept; // конструктор копирования
        BinVec (BinVec  && a) noexcept; // перемещающийся конструктор
        std::string &output(std::string &str) const;
        void output(std::ostream &a) const noexcept; // вывод в поток
        void output2(std::ostream &a) const noexcept;
        BinVec additionalCode() const; // доп код (дополнение)

        BinVec(int a);

        BinVec(std::string const &a); // конструктор копирования?

        BinVec& operator=(BinVec && a) noexcept;
        BinVec& operator=(BinVec const &a) noexcept;



        friend BinVec smallIncludingOr(BinVec const &num1, BinVec const &num2);  /// убрать (нужно для б варианта)
        friend BinVec smallIncludingAnd(BinVec const &num1, BinVec const &num2);
        friend BinVec smallIncludingXOR(BinVec const &num1, BinVec const &num2);
    private:
        static int const M = 100; // количество элементов в векторе
        int length;
        char data[100]; // храню число в обратном порядке
    };

    void transferToBin(int &a, char* data, int &length, int M);
    std::ostream &operator<<(std::ostream &a, BinVec const &number) noexcept;
    std::ostream &operator<<(BinVec const &number, std::ostream &a);
    void oneBitSum(char const &a, char const &b, char &m, int &flag);
    void oneBitAnd(char const &a, char const &b, char &m);
    void oneBitXOR(char const &a, char const &b, char &m);
    void add(char const a[], char const b[], char s[],int const &len, int &i, int max, int &flag) noexcept;
    void addXOR(char const a[], char const b[], char s[],int const &len, int &i, int max) noexcept;
    void bitSum(char const a[], char const b[], char s[], int const &len_a, int const &len_b, int &len, int max);
    void bitAnd(char const a[], char const b[], char s[], int const &len_a, int const &len_b, int &len, int max);
    void bitXOR(char const a[], char const b[], char s[], int const &len_a, int const &len_b, int &len, int max);

    void includingOr();
    void includingAnd();
    void includingXOR();

    void addition(char const a[], char b[], int len, int max);



    BinVec operator&(BinVec const &num1, BinVec const &num2);
    BinVec operator^(BinVec const &num1, BinVec const &num2);
    BinVec operator+(BinVec const &num1, BinVec const &num2);

    bool correctGetInt(int &a);
    int getNum();

    int dialog(const char* msgs[], int N);



}
#endif