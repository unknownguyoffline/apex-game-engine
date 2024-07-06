#include "entry_point.hpp"
#include "application.hpp"

void *operator new(unsigned long size)
{
    void *pointer = malloc(size);
    // printf("memory allocated: %p size: %lu\n", pointer, size);
    return pointer;
}
void operator delete(void *pointer) noexcept
{
    // printf("delete memory: %p\n", pointer);
    free(pointer);
}
int main()
{
    Application *app = createApplication();
    app->run();
    delete app;
}
