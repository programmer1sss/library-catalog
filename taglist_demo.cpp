#include <iostream>
#include "TagList.h"

int main() {
    std::cout << "TagList demo (крок 1: без деструктора)\n";

    TagList tags(4);
    tags.add("cpp");
    tags.add("raii");

    std::cout << "size = " << tags.size() << '\n';
    std::cout << "Готово. ASan має повідомити про витік пам'яті.\n";
    return 0;
}