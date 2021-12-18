#include "Perishable.h"
#include <iostream>
#include <fstream>

namespace AMA {
Perishable::Perishable();
    std::fstream & Perishable::store(std::fstream &file, bool newLine = true) const
    std::fstream & Perishable::load(std::fstream &file)
    std::ostream & Perishable::write(std::ostream &os, bool linear) const
    std::istream & Perishable::read(std::istream &is)
    const Date & Perishable::expiry() const

}