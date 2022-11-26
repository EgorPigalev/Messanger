#define SIZE_BUFFER 140

#include <stdio.h>
#include <Windows.h>

int main()
{
	system("chcp 1251");
	HANDLE hNamePipe;
	LPSTR lpszPipiName = "gff";
	DWORD size_buffer = SIZE_BUFFER;
	LPWSTR buffer = (CHAR*)calloc(size_buffer, sizeof(CHAR));
	char message[SIZE_BUFFER];
	BOOL Connected;
	DWORD actual_readen;
	BOOL SeccessRead;
	while (TRUE)
	{
		hNamePipe = CreateNamedPipe(
			lpszPipiName,
			PIPE_ACCESS_DUPLEX,
			PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
			PIPE_UNLIMITED_INSTANCES,
			SIZE_BUFFER,
			SIZE_BUFFER,
			INFINITE,
			NULL);
		Connected = ConnectNamedPipe(hNamePipe, buffer, size_buffer, &actual_readen, NULL);
		if (Connected)
		{
			SeccessRead = ReadFile(hNamePipe, buffer, size_buffer, &actual_readen, NULL);
			if (SeccessRead)
			{
				printf("Клиент пишет: ");
				printf(buffer);
				printf("\n");
				printf("\nВведите сообщение для клиента: \n");
				gets(message);
				buffer = &message;
				WriteFile(hNamePipe, buffer, size_buffer, &actual_readen, NULL);
			}
		}
		else
		{
			printf("\nКлиент отключился от сервера\n");
		}
		CloseHandle(hNamePipe);
	}
}