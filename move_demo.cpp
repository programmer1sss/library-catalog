#include <iostream>
#include <vector>
#include <string>
#include "TagList.h"

int main() {
    std::cout << "TagList move demo (крок 5)\n";
    std::cout << "Без reserve: 8 push_back у std::vector<TagList>\n\n";

    TagList::resetCounters();

    {
        std::vector<TagList> v;
        for (int i = 0; i < 8; ++i) {
            TagList t(2);
            t.add("tag" + std::to_string(i));
            v.push_back(std::move(t));
        }
        std::cout << "vector.size = " << v.size() << '\n';
    }

    std::cout << "copies = " << TagList::copies() << '\n';
    std::cout << "moves  = " << TagList::moves()  << '\n';
    return 0;
}