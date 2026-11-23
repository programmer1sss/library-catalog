#include "printCard.h"
#include <iostream>

void printCard(std::ostream& os, const LibraryItem& item) {
    os << "─── Картка фонду ───\n"
       << "  Інвентарний ID: " << item.getInventoryId() << '\n'
       << "  Назва:          " << item.getTitle() << '\n'
       << "  Рік:            " << item.getYear() << '\n';
}

void byValue(LibraryItem item) {
    std::cout << "[byValue] title = " << item.getTitle()
              << ", year = " << item.getYear()
              << ", invId = " << item.getInventoryId() << '\n';
    // Спроба звернутися до специфічного поля Book тут НЕМОЖЛИВА:
    // item.getAuthor() — помилка компіляції, бо тип LibraryItem.
}