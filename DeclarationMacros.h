#ifndef CPPBIKES_DECLARATIONMACROS_H
#define CPPBIKES_DECLARATIONMACROS_H

#define CPPBIKES_DECL_CLONE(ClassName) ClassName* clone() const { return new ClassName(*this);}

#endif