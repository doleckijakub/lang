#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define eprintf(format, ...) fprintf(stderr, format, ##__VA_ARGS__)
#define eprintfln(format, ...) fprintf(stderr, format "\n", ##__VA_ARGS__)
#define dief(format, ...) (eprintfln("Error: " format, ##__VA_ARGS__), exit(1))

#define MAX_INPUTS 16

#define next_arg() (assert(argc), --argc, *argv++)

int main(int argc, const char **argv) {
    if (argc == 0) dief("No arguments provided");

    const char *compiler_exe = next_arg();

    const char *inputs[MAX_INPUTS] = { 0 };
    size_t inputs_count = 0;

    const char *output = NULL;

    while (argc) {
        const char *flag = next_arg();

        if (strcmp(flag, "-o") == 0) {
            if (argc) {
                output = next_arg();
            } else {
                dief("-o flag requires an argument of an output name");
            }
        } else {
            if (inputs_count < MAX_INPUTS) {
                inputs[inputs_count++] = flag;
            } else {
                dief("Too many input files. Maximum allowed is %d", MAX_INPUTS);
            }
        }
    }

    if (!inputs_count) {
	dief("No input files");
    }

    if (!output) {
        output = "a.out";
    }

    eprintfln("Output: %s", output);

    eprintf("Inputs: %s", inputs[0]);
    for (size_t i = 1; i < inputs_count; i++) {
        eprintf(", %s", inputs[i]);
    }

    return 0;
}
#undef next_arg

