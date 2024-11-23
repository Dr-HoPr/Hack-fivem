#include "memory.h"
#include <iostream>
#include "skStr.h"
#include <conio.h> // para usar getch()
#include <fstream>
#include <string>
#include <windows.h>
#include <iostream>
#include <thread>
#include <fstream>
#include <string>

#include <direct.h>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

i_memory& i_memory::reeq()
{
	static i_memory ins;
	return ins;
}

// Función para ocultar la contraseña
std::string getHiddenInput()
{
    std::string input;
    char ch;
    while (true)
    {
        ch = _getch(); // Obtener el siguiente carácter sin mostrarlo
        if (ch == '\r') // Si es la tecla Enter, terminar la entrada
        {
            std::cout << std::endl;
            break;
        }
        else if (ch == '\b') // Si es la tecla de retroceso, borrar el último carácter
        {
            if (!input.empty())
            {
                input.pop_back();
                std::cout << "\b \b"; // Borrar el carácter en la pantalla
            }
        }
        else
        {
            input += ch;
            std::cout << '*'; // Mostrar un asterisco en lugar del carácter
        }
    }
    return input;
}

void logo()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    // Cambiar el color del texto a rosa
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY);

    // Texto del logotipo
    const char* logoText[] = {
    " -------------------- ",


    "| github.com |",
    "   --------------------  ",
    "",
    "" };

    // Obtener el tamaño de la consola
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    int consoleWidth = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    // Encontrar la longitud de la línea más larga
    int maxLength = 0;
    for (int i = 0; i < sizeof(logoText) / sizeof(logoText[0]); ++i) {
        int length = strlen(logoText[i]);
        if (length > maxLength) {
            maxLength = length;
        }
    }

    // Imprimir el logotipo centrado
    for (int i = 0; i < sizeof(logoText) / sizeof(logoText[0]); ++i) {
        int length = strlen(logoText[i]);
        int padding = (consoleWidth - length) / 2;
        for (int j = 0; j < padding; ++j) {
            std::cout << " ";
        }
        std::cout << logoText[i] << std::endl;
    }
}


void saveCredentialsToJson(const std::string& username, const std::string& password) {
    std::string ruta = "C:/FiveMLabs";

    int resultado = _mkdir(ruta.c_str());
    json credentials;
    credentials["username"] = username;
    credentials["password"] = password;

    std::ofstream file("C:/FiveMLabs/logincheat.json");
    file << credentials.dump(4);  // dump(4) para formatear el JSON con sangrías
    file.close();
}

bool loadCredentialsFromJson(std::string& username, std::string& password) {
    std::ifstream file("C:/FiveMLabs/logincheat.json");
    if (!file.is_open()) {
        return false;  // El archivo JSON no existe
    }

    json credentials;
    file >> credentials;
    file.close();

    if (!credentials["username"].is_null() && !credentials["password"].is_null()) {
        username = credentials["username"];
        password = credentials["password"];
        return true;  // Credenciales cargadas con éxito desde el archivo JSON
    }

    return false;  // El archivo JSON no contiene las credenciales adecuadas
}

void openurl()
{
            const char* url = "https://github.com/";

        #if defined(_WIN32)
        const char* command = "start ";
        #elif defined(__APPLE__) || defined(__MACH__)
        const char* command = "open ";
        #else
        const char* command = "xdg-open ";
        #endif

        std::string openCommand = std::string(command) + std::string(url);
        int result = system(openCommand.c_str());

        if (result == 0) {
            //Success
        } else {
            //Error
        }

}

void i_memory::initialize()
{
    using namespace KeyAuth;
    std::string name = ""; //change
    std::string ownerid = ""; //change
    std::string secret = ""; //change
    std::string version = ""; //change
    std::string url = skCrypt("").decrypt(); // change
    api KeyAuthApp(name, ownerid, secret, version, url);
    KeyAuthApp.init();
    logo();
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    std::cout << skCrypt("\n\n Please Login\n");


    std::string username;
    std::string password;

    // Intentar cargar credenciales desde el archivo JSON
    if (loadCredentialsFromJson(username, password)) {
     KeyAuthApp.login(username, password);
    } else {
        openurl();
        std::cout << "[+] Enter Your Username :"; 
        std::cin >> username;

        std::cout << "[+] Enter Your Password :";
        password = getHiddenInput(); // Utilizar la función para ocultar la contraseña
        KeyAuthApp.login(username, password);
    }
    Sleep(1000);
    system("cls");

    if (!KeyAuthApp.data.success)
    {
        MessageBox(NULL, "Invalid user/pass", "Error", MB_OK);
        std::cout << skCrypt("\nLogin failed ");
        Sleep(1500);
        exit(0);
    }
    else
    {
        // Guardar las credenciales en el archivo JSON
        saveCredentialsToJson(username, password);
        window = FindWindowA("grcWindow", 0);
        if (!window)
        {
            logo();
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            std::cout << "Fivem not Found!";
            Sleep(2000);
        }
        logo();
        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        GetWindowThreadProcessId(window, &pid);
        hProcess = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
    }
}

bool i_memory::find_build(const wchar_t* processName) {

    bool exists = false;
    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

    if (Process32First(snapshot, &entry)) {
        do {
            std::wstring exeFileName(entry.szExeFile, entry.szExeFile + strlen(entry.szExeFile));
            if (!_wcsicmp(exeFileName.c_str(), processName)) {
                exists = true;
                break;
            }
        } while (Process32Next(snapshot, &entry));
    }

    CloseHandle(snapshot);
    return exists;
}




uintptr_t i_memory::get_base_address(std::string a1)
{
    std::wstring pname = std::wstring(a1.begin(), a1.end());
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, pid);
    if (hSnap == INVALID_HANDLE_VALUE)
        return 0;
    MODULEENTRY32 ent;
    ent.dwSize = sizeof(ent);
    if (Module32First(hSnap, &ent))
    {
        do
        {
            if (!_stricmp(ent.szModule, a1.c_str())) 
            {
                std::cout << "Version: " << ent.szModule << std::endl;
                CloseHandle(hSnap);
                return (uintptr_t)ent.modBaseAddr;
            }
        } while (Module32Next(hSnap, &ent));
    }
    CloseHandle(hSnap);
    return 0;
}



HWND i_memory::get_process_wnd(uint32_t pid)
{
	std::pair<HWND, uint32_t> params = { 0, pid };
	BOOL bResult = EnumWindows([](HWND hwnd, LPARAM lParam) -> BOOL {
		auto pParams = (std::pair<HWND, uint32_t>*)(lParam);
	uint32_t processId = 0;

	if (GetWindowThreadProcessId(hwnd, reinterpret_cast<LPDWORD>(&processId)) && processId == pParams->second) {
		SetLastError((uint32_t)-1);
		pParams->first = hwnd;
		return FALSE;
	}

	return TRUE;

		}, (LPARAM)&params);

	if (!bResult && GetLastError() == -1 && params.first)
		return params.first;

	return NULL;
}
