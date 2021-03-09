#include <iostream>
#include <Windows.h>

void Entersauebern();
using namespace std;

int main()
{
	int intToWrite = 1000;
	char arrCharToWrite[128] = "anderer Text beim Char";
	string stringToWrite = "Kein String";
	cout << "PID eingeben: ";
	int pid;
	cin >> pid;

	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);

	if (hProcess == NULL)
	{
		cout << "OpenProcess fehlgeschlagen. GetLastError: " << GetLastError() << " " << endl;
		Entersauebern();
		getchar();
		EXIT_FAILURE;
	}
	else
	{
		uintptr_t memoryAddress = 0x0;
		uintptr_t memoryAddressChar = 0x0;
		uintptr_t memoryAddressString = 0x0;
		cout << "Speicheradresse von varInt eingeben: 0x";
		cin >> hex >> memoryAddress;
		bool CheckWrite = WriteProcessMemory(hProcess, (LPVOID)memoryAddress, &intToWrite, sizeof(int), NULL);
		cout << "Speicheradresse von arrChar eingeben: 0x";
		cin >> hex >> memoryAddressChar;
		bool CheckWrite2 = WriteProcessMemory(hProcess, (LPVOID)memoryAddressChar, &arrCharToWrite, sizeof(char[128]), NULL);
		cout << "Speicheradresse von varString eingeben: 0x";
		cin >> hex >> memoryAddressString;
		bool CheckWrite3 = WriteProcessMemory(hProcess, (LPVOID)memoryAddressString, &stringToWrite, sizeof(string), NULL);
		if (CheckWrite == false || CheckWrite2 == false || CheckWrite3 == false)
		{
			cout << "WriteProcessMemory fehlgeschlagen. GetLastError: " << GetLastError() << " " << endl;
			CloseHandle(hProcess);
			Entersauebern();
			getchar();
			EXIT_FAILURE;
		}
		else
		{
			cout << endl;
			cout << "CheckWrite  - Check\n";
			Sleep(0670);
			cout << "CheckWrite2 - Check\n";
			Sleep(0670);
			cout << "CheckWrite3 - Check\n";
			Sleep(0670);
			cout << endl;
			cout << "ERFOLGREICH\n";
			cout << "Druecke ENTER im Dummy Programm!\n";
			Entersauebern();
			getchar();
			CloseHandle(hProcess);
			EXIT_SUCCESS;
		}
	}
}

void Entersauebern()
{
	cin.ignore(cin.rdbuf()->in_avail());
}
