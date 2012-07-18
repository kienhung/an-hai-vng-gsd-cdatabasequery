#pragma once

enum MESSAGE_TYPE {FILE_LIST_REQUEST, DOWNLOAD_FILE, DOWNLOAD_FOLDER};

struct MESSAGE_HEADER {
	int iType;
	size_t uiLength;
};