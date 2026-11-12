#include <iostream>
#include "TagList.h"

void printTags(TagList copy) {   // навмисно за значенням
    std::cout << copy.size() << '\n';
}

int main() {
    std::cout << "TagList demo (крок 2: деструктор + навмисна копія)\n";

    TagList tags(4);
    tags.add("fiction");
    tags.add("non-fiction");

    std::cout << "tags.size = " << tags.size() << '\n';
    std::cout << "Виклик printTags(tags) — очікуємо double-free/heap-use-after-free\n";

    printTags(tags);   

    std::cout << "Готово (якщо дійшли сюди без краху — ASan ще не спрацював)\n";
    return 0;
}