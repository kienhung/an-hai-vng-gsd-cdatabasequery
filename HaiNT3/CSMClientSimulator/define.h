#pragma once

// String length
#define MIN_STR_LEN				16
#define TINY_STR_LEN			32
#define SMALL_STR_LEN			64
#define MEDIUM_STR_LEN			128
#define LARGE_STR_LEN			256
#define MAX_STR_LEN				512
#define KB						1024

// define commands receive from Server (in the Server Tracker csmstck.dll) 
#define	VST_TRACKER_MESSAGE			1200
#define VST_TRACK_APP_INFO			VST_TRACKER_MESSAGE + 1
#define VST_TRACKING_APP_ID			VST_TRACKER_MESSAGE + 2
#define VST_ASK_DOWN_FILE_MASTER	VST_TRACKER_MESSAGE + 3
#define	VST_ASK_UP_FILE_MASTER		VST_TRACKER_MESSAGE + 4
// if have a new command, continue define here (end value: VST_TRACKER_MESSAGE + 199)

// define commands send to Server (and will be processed in the Server Tracker csmstck.dll) 
#define	VCT_TRACKER_MESSAGE			2200
#define VCT_TRACKING_APP			VCT_TRACKER_MESSAGE + 1
#define VCT_RESPONSE_UPLOAD			VCT_TRACKER_MESSAGE + 2
#define VCT_WEB_HISTORY				VCT_TRACKER_MESSAGE + 3
// if have a new command, continue define here (end value: VCT_TRACKER_MESSAGE + 199)

// define file type	(use in the Server Tracker (csmstck.dll) and the Client Tracker (csmctck.dll))
#define TRACKAPP_FILE_TYPE			201
#define DATA_FILE_TYPE				202
#define	REPORT_FILE_TYPE			203

#define	TRACK_APP_FILE_NAME			_T("smtckapp.vcs")	// 201
