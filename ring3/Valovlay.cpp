// Valovlay.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "stdafx.h"
#include "game.h"

bool CheckDriverStatus() {
    std::cout << "Checking Driver Status ..." << std::endl;

    uintptr_t BaseAddr = driver::GetBaseAddress(driver::currentProcessId);
    std::cout << "-> BaseAddr :: " << BaseAddr << std::endl;
    if (BaseAddr == 0)
    {
        return false;
    }

    int icheck = 29;
    NTSTATUS status = 0;
    int checked = driver::read<int>(driver::currentProcessId, (uintptr_t) &icheck, &status);
    std::cout << "-> checked :: " << checked << std::endl;
    std::cout << "-> icheck :: " << icheck << std::endl;
    if (checked != icheck)
    {
        return false;
    }

    return true;
}

int main(int argc, char* argv[])
{
    std::cout << "Welcome To Valorant Overlay! :: Ring3" << std::endl;
    std::cout << "Efi :: Bifeldy-Driver :: Ring0" << std::endl;
    std::cout << "Last Build @ Bifeldy :: 26-08-2021" << std::endl;
    std::cout << "Good Luck & Have Fun~" << std::endl;

    bool ready = false;
    if (driver::initialize())
    {
        if (CheckDriverStatus())
        {
            ready = true;
        }
        else
        {
            wchar_t VarName[] = { 'B','i','f','e','l','d','y','-','D','r','i','v','e','r','\0' };
            UNICODE_STRING FVariableName = UNICODE_STRING();
            FVariableName.Buffer = VarName;
            FVariableName.Length = 28;
            FVariableName.MaximumLength = 30;
            // UNICODE_STRING VariableName = RTL_CONSTANT_STRING(VARIABLE_NAME);
            driver::myNtSetSystemEnvironmentValueEx(&FVariableName, &driver::DummyGuid, 0, 0, ATTRIBUTES);
            memset(VarName, 0, sizeof(VarName));
            // memset(VariableName.Buffer, 0, VariableName.Length);
            // VariableName.Length = 0;
            Beep(1250, 1000);
            std::cout << "No EFI Driver Found ..." << std::endl;
        }
    }
    else
    {
        std::cout << "Failed To Communicate With The Driver ..." << std::endl;
        Beep(1250, 500);
    }

    if (ready)
    {
        Beep(1250, 250);
        game::run();
    }

    std::cout << "Good Bye~" << std::endl;
    system("pause");
    return 0;
}