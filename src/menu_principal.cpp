#include <M5StickCPlus2.h>
#include <submenu.h>
#include <const.h>
#include <gestorMenus.h>

const char *MENU_PRINCIPAL_ITEMS[] = {"RELOJ", "BLUETOOTH", "CRONOMETRO", "SENSORES"};
int idx = 0;

itemMenu menu[] = {
    {"RELOJ", RELOJ},
    {"BLUETOOTH", BLUETOOTH},
    {"CRONOMETRO", CRONOMETRO},
    {"SENSORES", MENU_SENSORES}
};

void mainMenu()
{
    while (modulo == MENU_INICIAL)
    {
        if (M5.BtnB.wasPressed())
        {
            idx = (idx + 1) % 3;
            displayMenu(menu, idx, 3);
        }
        if (M5.BtnA.wasPressed())
        {
            // if (capa < 2)
            // {
            //     capa++;
            // }
            // selectOption();
            modulo
        }
    }
}