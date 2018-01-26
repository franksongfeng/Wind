#ifndef WIND_OBJECT_H
#define WIND_OBJECT_H

#include <stdlib.h>

// Object base struct for common casting.
#define WindObject_BASE \
        WindType type; \
        struct WindObject* next; \
        struct WindObject* prev;

// Macro for connecting objects.
#define WindObject_CONNECT(obj1, obj2) do { \
                obj1->next = obj2; \
                obj2->prev = obj1; \
} while(0)

// Macro for disconnecting objects
#define WindObject_DISCONNECT(obj1, obj2) do { \
                obj1->next = NULL; \
                obj2->prev = NULL; \
} while(0)

#define WindObject_BEGIN(wobj) while(wobj->prev != NULL) wobj = wobj->prev

#define WindObject_END(wobj) while(wobj->next != NULL) wobj = wobj->next

// Macro to determine if two objects have the same type
#define WindObject_SAME_T(obj1, obj2) (obj1->type == obj2->type)

#define WindObject_NULLIFY(obj) \
        obj->next = NULL; \
        obj->prev = NULL;

// Type to denote information about an object
typedef enum
{
        WindType_None,
        WindType_Bool
} WindType;


// Wind Object
// This is the pure, base Type for the Wind Language.
struct WindObject
{
        WindObject_BASE
};

typedef struct WindObject WindObject;

#endif // WIND_OBJECT_H
