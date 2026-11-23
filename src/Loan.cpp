#include "Loan.h"
#include <iomanip>
#include <stdexcept>
#include <utility>

Loan::Loan(std::string readerCard,
           const LibraryItem* item,
           std::string issueDate,
           std::string returnDate)
    : readerCard_(std::move(readerCard)),
      item_(item),
      issueDate_(std::move(issueDate)),
      returnDate_(std::move(returnDate))
{
    if (readerCard_.empty())
        throw std::invalid_argument("Loan: empty reader card");
    if (item_ == nullptr)
        throw std::invalid_argument("Loan: null item");
    if (issueDate_.empty())
        throw std::invalid_argument("Loan: empty issue date");
}

std::ostream& operator<<(std::ostream& os, const Loan& l) {
    const auto saved = os.flags();
    os << l.getReaderCard() << ' '
       << (l.getItem() ? l.getItem()->getInventoryId() : std::string("(none)")) << ' '
       << std::quoted(l.getIssueDate()) << ' '
       << std::quoted(l.getReturnDate());
    os.flags(saved);
    return os;
}