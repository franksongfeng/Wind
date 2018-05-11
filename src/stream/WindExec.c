#include "WindExec.h"

int WindExec_out(WindStream* ws, BufKey bkey)
{
        WindBuf* sbuf;
        WindStream_GET_BUF(ws, sbuf, bkey);
        printf("[ ");
        for(size_t i = 0; i < sbuf->len; i++)
        {
                switch(sbuf->data[i])
                {
                case WindType_None:
                        printf("None ");
                        break;
                case WindType_Bool:
                        i++;
                        printf(sbuf->data[i] ? "True " : "False ");
                        break;
                case WindType_Not:
                        printf("! ");
                        break;
                case WindType_Sep:
                        printf("| ");
                        break;
                default:
                        WindStream_write_err(ws, "Cannot recognize item with byte %u", sbuf->data[i]);
                        return 0;
                }
        }
        puts("]");
        return 1;
}

int WindExec_push(WindStream* ws)
{
        size_t pushLen = ws->loadBuf->len;
        WindStream_put_ptr(ws, BufKey_active, ws->loadBuf->data, pushLen);
        return 1;
}

int WindExec_clr(WindStream* ws)
{
        WindStream_reset(ws, BufKey_active);
        return 1;
}

int WindExec_map(WindStream* ws)
{
        WindBuf_equalize(ws->activeBuf, &(ws->altBuf));
        // Clears altbuf to allow for new stream result.
        WinfBuf_RESET(ws->altBuf);
        // Traversing Pointers
        unsigned char* loadPtr;
        unsigned char* loadEnd;

        unsigned char* activePtr = ws->activeBuf->data;
        unsigned char* activeEnd = activePtr + ws->activeBuf->len;

        while(activePtr != activeEnd)
        {
                // These are restarted each loop since entire map seq
                // is applied to one value at a time.
                loadPtr = ws->loadBuf->data;
                loadEnd = loadPtr + ws->loadBuf->len;
                while(loadPtr != loadEnd)
                {
                        switch(*loadPtr)
                        {
                        case WindType_Not:
                                loadPtr++;
                                // WindMap_not( const unsigned char* src, unsigned char* ins);
                                break;
                        default:
                                WindStream_write_err(ws, "Unrecognized map argument %u", *loadPtr);
                                return 0;
                        }
                }
        }
        WindStream_swap_buf(ws);

        return 1;
}
