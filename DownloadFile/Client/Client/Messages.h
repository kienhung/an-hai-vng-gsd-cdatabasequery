#pragma once
enum MESSAGE_TYPE {DOWNLOAD_FILE, FILE_NOT_FOUND, FILE_FOUND, FILE_SENDING_COMPLETED};

struct MESSAGE_HEADER {
	MESSAGE_TYPE iType;
	int iLength;
};

struct FILE_NAME_MESSAGE {
	TCHAR strFileName[MAX_PATH];
};