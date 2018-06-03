#include "WindType.h"


/*Strings for type message formatting*/
static const char* WindType_STR_NONE = "None";
static const char* WindType_STR_BOOL = "Bool";
static const char* WindType_STR_NUMBER = "Number";
static const char* WindType_STR_ASSIGN = "Assign";
static const char* WindType_STR_NOT = "Not";
static const char* WindType_STR_PLUS = "Plus";
static const char* WindType_STR_SEP = "Separator";

const char* WindType_get_str(WindType type)
{
        switch(type)
        {
        case WindType_None: return WindType_STR_NONE;
        case WindType_Bool: return WindType_STR_BOOL;
        case WindType_Not: return WindType_STR_NOT;
        case WindType_Number: return WindType_STR_NUMBER;
        case WindType_Assign: return WindType_STR_ASSIGN;
        case WindType_Plus: return WindType_STR_PLUS;
        case WindType_Sep: return WindType_STR_SEP;
        }
}
