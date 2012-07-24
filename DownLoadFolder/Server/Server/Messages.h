#pragma once

enum MESSAGE_TYPE {FILE_LIST_REQUEST, DOWNLOAD_FILE};

struct MESSAGE_HEADER {
	int iType;
	int uiLength;
};