#include "WindBuf.h"

WindBuf* WindBuf_new(size_t size)
{
        WindBuf* newbuf = malloc(sizeof(WindBuf) + (sizeof(unsigned char) * size));
        newbuf->len = 0;
        newbuf->cap = size;
        newbuf->head = newbuf->data;
        return newbuf;
}

void WindBuf_check(WindBuf** wb, size_t size, size_t add)
{
        if(((*wb)->cap - (*wb)->len) < size)
        {
                (*wb)->cap += size + add;
                *wb = realloc(*wb, sizeof(WindBuf) + (*wb)->cap);
        }
}

unsigned char* WindBuf_get(WindBuf* wb, size_t index)
{
        // needs moving to windval header
        unsigned char* startPtr = wb->data;
        unsigned char* endPtr = wb->data + wb->len;
        while(startPtr != endPtr && index--)
        {
                // Advances pointer based on type and it's offset.
                switch(*startPtr)
                {
                case WindType_None:
                        startPtr++;
                        break;
                // needs more types handled.
                default:
                        return NULL;
                }
        }
        if(index) return NULL;
        else return startPtr;
}

unsigned char* WindBuf_place(WindBuf* wb, void* item, size_t size)
{
        WindBuf_CHECK(wb, size, size + 5);
        unsigned char* reader = item;
        unsigned char* placed = wb->data + wb->len;
        for(size_t i = 0; i < size; i++) wb->data[wb->len++] = reader[i];
        return placed;
}




void WindBuf_equalize(WindBuf* wb, WindBuf** other)
{
        (*other)->len = wb->len;
        if(wb->cap > (*other)->cap)
        {
                size_t newCap = wb->cap + WindBuf_EQ_SPACE;
                WindBuf_EXPAND((*other), newCap);
        }
}

void WindBuf_equalize_cap(WindBuf* wb, WindBuf** other)
{
        if(wb->cap > (*other)->cap)
        {
                size_t newCap = wb->cap + WindBuf_EQ_SPACE;
                WindBuf_EXPAND((*other), newCap);
        }
}

// Never throws.
void WindBuf_write(WindBuf** wb, void* item, size_t size)
{
        WindBuf_check(wb, size, size + 30);
        memcpy((*wb)->data + (*wb)->len, item, size);
        (*wb)->len += size;
}

void WindBuf_write_begin(WindBuf* wb, void* item, size_t size)
{
        wb->len = size;
        WindBuf_CHECK(wb, size, size + 30);
        memcpy(wb->data, item, size);
}

// never throws.
void WindBuf_write_mark(WindBuf* wb, unsigned char mark, void* item, size_t size)
{
        WindBuf_CHECK(wb, (size + sizeof(unsigned char)), size + 30);
        wb->data[wb->len++] = mark;
        memcpy(wb->data + wb->len, item, size);
        wb->len += size;
}
