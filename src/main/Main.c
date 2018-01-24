#include <stdio.h>
#include "WindNone.h"
#include "Evaluate.h"

int main(int argc, char const *argv[]) {
        WindNone* none = WindNone_new();
        WindNone* none2 = WindNone_new();
        WindStream* stream = WindStream_new();
        WindStream_push(stream, (WindObject*)none);
        WindStream_push(stream, (WindObject*)none2);
        WindStream_push_left(stream, (WindObject*)WindNone_new());

        EvalState state = EvalState_Command;
        const char* coding = "   \n\nout ->";
        Evaluate_command(stream, &coding, &state);
        puts(coding);
        WindStream_del(stream);
        return 0;

}
