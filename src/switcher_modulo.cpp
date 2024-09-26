#include <const.h>
#include <gestorMenus.h>

void enrutador()
{
    switch (modulo)
    {
    case (MENU_INICIAL):
        mainMenu();
        break;
    default:
        mainMenu();
        break;
    }
}