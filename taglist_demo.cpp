#include <iostream>
#include <cassert>
#include "TagList.h"


void printTags(TagList copy) {   // навмисно за значенням — тепер має працювати
    std::cout << "printTags: size = " << copy.size() << '\n';
}

int main() {
    std::cout << "TagList demo (крок 3: глибока копія)\n";

    TagList tags(4);
    tags.add("fiction");
    tags.add("non-fiction");

    std::cout << "tags.size = " << tags.size() << '\n';

    // 1) Виклик за значенням — раніше давав double-free, тепер має бути чисто
    printTags(tags);
    std::cout << "printTags(tags) відпрацював без ASan-помилок\n";

    // 2) Явне копіювання + перевірка незалежності
    TagList copy = tags;             // викликається TagList(const TagList&)
    assert(copy.size() == tags.size());
    assert(copy.at(0) == "fiction");
    assert(copy.at(1) == "non-fiction");

    // 3) Змінюємо оригінал — копія не повинна змінитися
    //    (add не перезаписує наявні елементи, тож змінюємо через новий add)
    tags.add("poetry");
    assert(tags.size() == 3);
    assert(copy.size() == 2);         // ← ключова перевірка: копія незалежна
    assert(copy.at(0) == "fiction");  // вміст копії не змінився
    assert(copy.at(1) == "non-fiction");

    std::cout << "Після tags.add(\"poetry\"): tags.size = " << tags.size()
              << ", copy.size = " << copy.size() << " (копія незалежна)\n";

    std::cout << "Готово: ASan має мовчати.\n";
    return 0;
}