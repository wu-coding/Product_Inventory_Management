#include <iostream>
#include <fstream>
#include <cstring>
#include "Product.h"

using std::cout;
using std::endl;
namespace AMA
{
void Product::name(const char *passName)
{
    if (passName == nullptr)
    {
        delete[] prodName;
    }
    else
    {
        delete[] prodName;
        prodName = new char[strlen(passName) + 1];
        strcpy(prodName, passName);
    }
}
const char *Product::name() const
{
    if (*prodName == '\0')
    {
        return nullptr;
    }
    else
    {
        return prodName;
    }
}
const char *Product::sku() const
{
    return prodSku;
}
const char *Product::unit() const
{
    return prodUnit;
}
bool Product::taxed() const
{
    return prodTax;
}
double Product::price() const
{
    return prodPrice;
}
double Product::cost() const
{
    double addon = 0;
    if (taxed())
    {
        addon = tax_rate * prodPrice;
    }
    return addon + prodPrice;
}

void Product::message(const char *passMessage)
{
    error.message(passMessage);
}

bool Product::isClear() const
{
    return (error.isClear()) ? true : false;
}

Product::Product(const char passChar)
{
    prodType = passChar;
    *prodSku = '\0';
    *prodUnit = '\0';
    prodName = nullptr;
    prodQuantity = 0;
    prodNeeded = 0;
    prodPrice = 0;
    prodTax = false;
}
Product::Product(const char *passprodSku, const char *passName, const char *passUnit,
                 int passQuantity, bool passprodTax, double passPrice, int passNeeded)
{
    strcpy(prodSku, passprodSku);
    prodName = new char[strlen(passName) + 1];
    strcpy(prodName, passName);
    strcpy(prodUnit, passUnit);
    prodQuantity = passQuantity;
    prodTax = passprodTax;
    prodPrice = passPrice;
    prodNeeded = passNeeded;
}
Product::Product(const Product &pass)
{
    prodType = pass.prodType;
    strcpy(prodSku, pass.prodSku);
    strcpy(prodUnit, pass.prodUnit);
    prodQuantity = pass.prodQuantity;
    prodNeeded = pass.prodNeeded;
    prodPrice = pass.prodPrice;
    prodTax = pass.prodTax;
    if (pass.prodName != nullptr)
    {
        prodName = new char[strlen(pass.prodName) + 1];
        strcpy(prodName, pass.prodName);
    }
    else
    {
        prodName = nullptr;
    }
}

Product &Product::operator=(const Product &pass)
{
    if (&pass != this)
    {
        prodType = pass.prodType;
        strcpy(prodSku, pass.prodSku);
        strcpy(prodUnit, pass.prodUnit);
        prodQuantity = pass.prodQuantity;
        prodNeeded = pass.prodNeeded;
        prodPrice = pass.prodPrice;
        prodTax = pass.prodTax;
        if (pass.prodName != nullptr)
        {
            delete[] prodName;
            prodName = new char[strlen(pass.prodName) + 1];
            strcpy(prodName, pass.prodName);
        }
    } 
 
    else
    {
        prodName = nullptr;
    }
    return *this;
}

Product::~Product()
{
    delete[] prodName;
    prodName = nullptr;
}
std::fstream &Product::store(std::fstream &file, bool newLine) const
{
    if (file.is_open())
    {
        file << prodType;
        file << prodSku;
        file << ',';
        file << prodUnit;
        file << ',';
        file << prodQuantity;
        file << ',';
        file << prodNeeded;
        file << ',';
        file << prodPrice;
        if (newLine)
        {
            file << endl;
        }
        else
        {
            cout << "Error opening file";
        }
    }
    return file;
}
std::fstream &Product::load(std::fstream &file)
{
    if (file.is_open())
    {
        Product tempProd;
        file >> tempProd.prodType;
        file >> tempProd.prodSku;
        file.ignore();
        file >> tempProd.prodUnit;
        file.ignore();
        file >> tempProd.prodQuantity;
        file.ignore();
        file >> tempProd.prodNeeded;
        file.ignore();
        file >> tempProd.prodPrice;
        *this = tempProd;
    }
    else
    {
        cout << "Error opening file";
    }
    return file;
}
std::ostream &Product::write(std::ostream &os, bool linear) const
{
    if (linear == true)
    {
        os.width(max_sku_length);
        os.setf(std::ios::left);
        os << prodSku;
        os << '|';

        os.width(20);
        os << prodName;
        os << '|';
        os.unsetf(std::ios::left);

        os.width(max_sku_length);
        os.setf(std::ios::fixed);
        os.precision(2);
        if (taxed())
        {
        os << prodPrice * (tax_rate + 1);
        }   else {
            os << prodPrice;
        }
        os << '|';

        os.width(4);
        os << prodQuantity;
        os << '|';

        
        os.width(10);
        os.setf(std::ios::left);
        os << prodUnit;
        os.unsetf(std::ios::left);
        os << '|';

        os.width(4);
        os  << prodNeeded;
        os << '|';
    }

    else
    {
        os.width(max_sku_length);
        os << " Sku: " << prodSku << endl;

        os.width(20);
        os << " Name: " << prodName << endl;

        os.width(10);

        double afterTax;
        if (taxed())
        {
            afterTax = prodPrice * (tax_rate + 1);
            os << " Price after tax: " << afterTax << endl;
        }
        else
        {
            os << " N/A" << endl;
        }

        os.width(4);
        os << " Quantity on hand: " << prodQuantity << endl;

        os.width(4);
        os << " Quantity needed: " << prodNeeded << endl;
    }
    return os;
}
std::istream &Product::read(std::istream &is)
{

    Product temp;
    char nameTemp[max_name_length];
    cout << " Sku: ";
    is >> temp.prodSku;

    cout << " Name (no spaces): ";
    is >> nameTemp;
    temp.name(nameTemp);

    cout << " Unit: ";
    is >> temp.prodUnit;

    char tempTax;
    cout << " Taxed? (y/n): ";
    is >> tempTax;
    if (tempTax == 'Y' || tempTax == 'y')
    {
        temp.prodTax = true;
    }
    else if (tempTax == 'N' || tempTax == 'n')
    {
        temp.prodTax = false;
    }
    else
    {
        is.setstate(std::ios::failbit);
        error.message("Taxed Only (Y)es or (N)o are acceptable");
        return is;
    }

    cout << " Price: ";
    is >> temp.prodPrice;
    if (is.fail())
    {
        error.message("Invalid Price Entry");
        return is;
    }

    cout << " Quantity on hand: ";
    is >> temp.prodQuantity;
    if (is.fail())
    {
        error.message("Invalid Quantity Entry");
        return is;
    }

    cout << " Quantity needed: ";
    is >> temp.prodNeeded;
    if (is.fail())
    {
        error.message("Invalid Quantity Needed Entry");
        return is;
    }
  
    if (!is.fail())
    {
        *this = temp;
    }
    return is;
}

bool Product::operator==(const char *passprodSku) const
{
     return (strcmp(prodSku, passprodSku) == 0) ? true : false;
}
double Product::total_cost() const
{
    double addon = 0;
    if (taxed())
    {
        addon = prodQuantity * prodPrice * tax_rate;
    }
    return prodQuantity * prodPrice + addon;
}
void Product::quantity(int passQuantity)
{
    prodQuantity = passQuantity;
}
bool Product::isEmpty() const
{
    if (
        *prodSku == '\0' &&
        *prodUnit == '\0' &&
        prodName == nullptr &&
        prodQuantity == 0 &&
        prodNeeded == 0 &&
        prodPrice == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}
int Product::qtyNeeded() const
{
    return prodNeeded;
}
int Product::quantity() const
{
    return prodQuantity;
}
bool Product::operator>(const char *passprodSku) const
{
    return strcmp(prodSku, passprodSku);
}

bool Product::operator>(const Product &passProd) const
{
    return strcmp(prodName, passProd.prodName);
}
int Product::operator+=(int passTotal)
{
    if (passTotal > 0)
    {
        prodQuantity += passTotal;
    }
    return prodQuantity;
}
 std::ostream &operator<<(std::ostream& os, const Product & passProd)
 {
     return passProd.write(os,true);
 }
 std::istream &operator>>(std::istream & is, Product & passProd)
 {
     return passProd.read(is);
 } 
double operator+=(double &passDouble, const Product &passProd)
{
     return passProd.total_cost() + passDouble;
}
} 