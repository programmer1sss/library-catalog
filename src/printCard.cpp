#include "printCard.h"

void printCard(std::ostream& os, const LibraryItem& item) {
    os << "─── Картка фонду ───\n"
       << "  Інвентарний ID: " << item.getInventoryId() << '\n'
       << "  Назва:          " << item.getTitle() << '\n'
       << "  Рік:            " << item.getYear() << '\n';
}