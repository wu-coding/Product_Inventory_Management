#ifndef PRODUCT_H
#define PRODUCT_H
#include <iostream>
#include "ErrorState.h"
#include "iProduct.h"

namespace AMA
{
const int max_sku_length = 7;
const int max_unit_length = 10;
const int max_name_length = 75;
const double tax_rate = .13;

class Product : public iProduct
{
  char prodType;
  char prodSku[max_sku_length + 1];
  char prodUnit[max_unit_length + 1]; 
  char *prodName;
  int prodQuantity;
  int prodNeeded;
  double prodPrice;
  bool prodTax;
  ErrorState error;

protected:
  void name(const char *);
  const char *name() const;
  const char *sku() const;
  const char *unit() const;
  bool taxed() const;
  double price() const;
  double cost() const;
  void message(const char *);
  bool isClear() const;

public:
  Product(const char = 'N');
  Product(const char *, const char *, const char *, int = 0, bool = true, double = 0, int = 0);
  Product(const Product &pass);
  Product &operator=(const Product &);
  ~Product();
  std::fstream &store(std::fstream &file, bool newLine = true) const;
  std::fstream &load(std::fstream &file);
  std::ostream &write(std::ostream &os, bool linear) const;
  std::istream &read(std::istream &is);
  bool operator==(const char *) const;
  double total_cost() const;
  void quantity(int);
  bool isEmpty() const;
  int qtyNeeded() const;
  int quantity() const;
  bool operator>(const char *) const;
  bool operator>(const Product &) const;
  int operator+=(int);

  friend std::ostream &operator<<(std::ostream &, const Product &);
  friend std::istream &operator>>(std::istream &, Product &);
  friend double operator+=(double &, const Product &);
};
} 

#endif