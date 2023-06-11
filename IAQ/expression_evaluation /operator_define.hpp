// #ifndef _H_OPERATOR_DEFS_INCLUDED__
// #define _H_OPERATOR_DEFS_INCLUDED__
#ifndef DECLARE_OPERATOR
#define DECLARE_OPERATOR(short_name, full_name,operator_type,priority, fn)
#define DO_UNDEF_DECLARE_OPERATOR
#endif
//operator fullname priority function
DECLARE_OPERATOR('+',"",1,plus)
DECLARE_OPERATOR('-',"",1,subtract)
DECLARE_OPERATOR('*',"",2,multiply)
DECLARE_OPERATOR('/',"",2,divide)
DECLARE_OPERATOR('^',"",2,power)
DECLARE_OPERATOR('S',"sqrt",2,sqrt)
DECLARE_OPERATOR('s',"sin",2,sin)
DECLARE_OPERATOR('c',"cos",2,cos)
DECLARE_OPERATOR('t',"tan",2,tan)
DECLARE_OPERATOR('m',"myfunction",2,myfunction)

#ifdef DO_UNDEF_DECLARE_OPERATOR
#undef DECLARE_OPERATOR
#endif

// #endif // _H_OPERATOR_DEFS_INCLUDED__