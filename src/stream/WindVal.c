#include "WindVal.h"

int WindVal_copy(unsigned char** dest, unsigned char** src, int amnt)
{
        unsigned char* writer = *dest;
        unsigned char* reader = *src;
        while(amnt--)
        {
                switch(*reader)
                {
                case WindType_Bool:
                        *writer++ = *reader++;
                        *writer++ = *reader++;
                        break;
                // single byte wind values
                case WindType_None:
                case WindType_Sep:
                case WindType_Not:
                        *writer++ = *reader++;
                        break;
                default:
                        *dest = writer;
                        return 0; // error
                }
        }
        *dest = writer;
        *src = reader;
        return 1;
}

int WindVal_apply_not(unsigned char* item)
{
        switch(*item)
        {
        case WindType_Bool:
                item[1] = !(item[1]);
                return 1;
        default:
                // If type is not bool, writes a false boolean. may change this.
                *item++ = WindType_Bool;
                *item++ = 0;
                return 1;
        }
}

int WindVal_move(unsigned char** item, int amnt)
{
        while(amnt--)
        {
                switch(**item)
                {
                case WindType_Not:
                case WindType_Sep:
                case WindType_None:
                        *item += 1;
                        return 1;
                case WindType_Bool:
                        *item += 2;
                        return 1;
                default:
                        // error
                        return 0;
                }
        }
        return 1;
}
