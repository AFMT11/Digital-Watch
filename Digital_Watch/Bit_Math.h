#ifndef BIT_MATH_H_INCLUDED
#define BIT_MATH_H_INCLUDED


#define Set_Bit(var,bit)     (var |= (1<<bit))
#define Toggle_Bit(var,bit)  (var ^= (1<< bit))
#define Clear_Bit(var,bit)   (var &=~ (1<< bit))
#define Get_Bit(var,bit)     ((var>>bit)&1)

#endif // BIT_MATH_H_INCLUDED
