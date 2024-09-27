#include <M5StickCPlus2.h>
#include <submenu.h>
#include "gestorMenus.h"
#include "const.h"

const char *MENU_PRINCIPAL_ITEMS[] = {"RELOJ", "BLUETOOTH", "CRONOMETRO", "SENSORES"};
int idx = 0;

itemMenu menu[] = {
    {"RELOJ", RELOJ},
    {"BLUETOOTH", BLUETOOTH},
    {"CRONOMETRO", CRONOMETRO},
    {"SENSORES", MENU_SENSORES}};

void mainMenu()
{
    displayMenu(menu, idx, 4);
    while (modulo == MENU_INICIAL)
    {
        if (M5.BtnB.wasPressed())
        {
            idx = (idx + 1) % 4;
            displayMenu(menu, idx, 4);
        }
        if (M5.BtnA.wasPressed())
        {
            modulo = menu[idx].modulo;
        }
        M5.update();
    }
}