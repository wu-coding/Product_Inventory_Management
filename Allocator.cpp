#include "Product.h"
#include "Perishable.h"

namespace AMA {

	iProduct* CreateProduct() {
		return new Product();
	}

	iProduct* CreatePerishable() {
		return new Perishable();
	}
}