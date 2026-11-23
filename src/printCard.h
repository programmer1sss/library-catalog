#pragma once

#include <ostream>
#include "LibraryItem.h"

// Друкує "картку" будь-якої одиниці фонду.
// Приймає посилання на базовий клас — поліморфізм у дії.
void printCard(std::ostream& os, const LibraryItem& item);