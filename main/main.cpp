#include <iostream>
#include "../lib/Prog3.h"
using namespace Static;

int main()
{
    int rc;
    BinVec binVec;
    std::string n;
    std::cout << "Введите число:" << std::endl;
    std::cin >> n;
    binVec = BinVec(n);
    std::cout << binVec; // перегруженный оператор вывода
    std::cout << binVec.additionalCode();
    binVec.output2(std::cout);

    const char* msgs[] = { "0 - exit", "1 - Включающее или", "2 - Включающее и", "3 - XOR"};
    const int NMsgs = sizeof(msgs) / sizeof(msgs[0]);
    void(*fptr[])() = { NULL,includingOr, includingAnd, includingXOR};
    while (rc = dialog(msgs, NMsgs))
    {
        fptr[rc]();
    }

    std::cout << "That's all. Bye!\n";

    return 0;
}