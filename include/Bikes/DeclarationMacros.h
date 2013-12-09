#ifndef PREBIKES_DECLARATIONMACROS_H
#define PREBIKES_DECLARATIONMACROS_H

#define BIKES_DECL_CLONE(ClassName) ClassName* clone() const { return new ClassName(*this);}

#endif