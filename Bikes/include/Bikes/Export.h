#ifndef INCLUDE_BIKES_EXPORT_H
#define INCLUDE_BIKES_EXPORT_H

#ifdef _MSC_VER
#	define BIKES_DECL_EXPORT __declspec(dllexport)
#	define BIKES_DECL_IMPORT __declspec(dllimport)
#else
#	define BIKES_DECL_EXPORT  // or(?) __attribute__((visibility("default"))) 
#	define BIKES_DECL_IMPORT  // or(?) __attribute__((visibility("default"))) 
#endif

#if defined(BIKES_SHAREDLIB)
#	define BIKES_EXPORT	BIKES_DECL_EXPORT
#elif defined(BIKES_STATICLIB)
#	define BIKES_EXPORT
#else
#	define BIKES_EXPORT BIKES_DECL_IMPORT
#endif

#endif // <- INCLUDE_BIKES_EXPORT_H
