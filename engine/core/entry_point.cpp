#include "entry_point.hpp"
#include "application.hpp"

int main()
{
    Application *app = createApplication();
    app->run();
    delete app;
}
