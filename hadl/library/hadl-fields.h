
#ifndef __HADL_FIELDS__
#define __HADL_FIELDS__

template<class D, class F>
F HADL_Field_getValue(D data, int r[][3], int n, int shift, int right, int rot, int arith);

template<class D, class F>
void HADL_Field_setValue(D* target, F data, int r[][3], int n);

// Include .cpp for template instantiation
#include "hadl-fields.cpp"

#endif

