#include "Translation.h"

int Translate_src_command(const char** code, WindStream* ws, StreamState* state)
{
        while(**code)
        {
                switch(**code)
                {
                default:
                        return 0;
                }
        }
        return 1;
}


int Translate_src_sep(const char** code, WindStream* ws, StreamState* state)
{
        while(**code)
        {
                switch(**code)
                {
                case ' ':
                case '\n':
                case '\t':
                case '\v':
                        *code += 1; //white space
                        break;
                case '|':
                        // pipe sep found
                        *code += 1;
                        *state = StreamState_command;
                        return 1;
                case '-':
                        if((*code)[1] == '>')
                        {
                                *code += 2;
                                *state = StreamState_command;
                                return 1;
                        }
                        else
                        {
                                WindStream_write_err(ws, "Expected separator ->, found '-%c'", (*code)[1]);
                                return 0; // error
                        }
                default:
                        WindStream_write_err(ws, "Expected separator ->, found '%c'", (*code)[0]);
                        return 0;
                }
        }
        return 1;
}

void Translate_src_code(const char* code, WindStream* ws, StreamState* state)
{
        while(*code)
        {
                switch(*state)
                {
                case StreamState_sep:
                        break;
                case StreamState_command:
                        break;
                }
        }
}