#include <stdio.h>
#include <stdlib.h>

static FILE* fp;
int g_count;
#if 0
#define DUMP(desp , func, call) \
    fprintf(fp ,"%s:%p:%p\n", desp , func , __builtin_return_address(1))
#endif

void __attribute__((__no_instrument_function__))
dump(char* desp , void* func)
{
    fprintf(fp , "%d %s:%p\n", g_count++ , desp , func);
    fflush(fp);
}

/* Constructor and Destructor Prototypes */

void main_constructor(void)
__attribute__((no_instrument_function, constructor));

void main_destructor(void)
__attribute__((no_instrument_function, destructor));

/* Output trace file pointer */


void
main_constructor(void)

{
    fp = fopen("trace.txt", "w");

    if (fp == NULL) {
        exit(-1);
    }

    g_count = 0;
}

void
main_deconstructor(void)
{
    fclose(fp);
}


void __attribute__((__no_instrument_function__))
__cyg_profile_func_enter(void* this_func, void* call_site)
{
    dump("enter", this_func);
}

void __attribute__((__no_instrument_function__))
__cyg_profile_func_exit(void* this_func, void* call_site)
{
    dump("leave", this_func);
}

void func1();
void func2();
void func3();
void func4();

void func2() {
}

void func1() {
    func2();
    func3();
}

void func3() {
    func4();

}

void func4(){
}

int
main( int argc, char **argv )
{

    func1();
    func3();
    
    return 0;
}

