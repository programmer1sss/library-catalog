#pragma once

#include <ostream>
#include "LibraryItem.h"

// Друкує "картку" будь-якої одиниці фонду.
void printCard(std::ostream& os, const LibraryItem& item);

// Діагностика: демонстрація object slicing.
// Приймає об'єкт ЗА ЗНАЧЕННЯМ — створюється копія типу LibraryItem,
// усі поля похідного класу "зрізаються".
void byValue(LibraryItem item);