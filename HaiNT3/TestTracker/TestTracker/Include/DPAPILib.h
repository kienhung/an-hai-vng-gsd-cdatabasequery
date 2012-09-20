
#pragma once

typedef void (__cdecl* pfn_CreatePartitionProgressCallBack)(HWND hw, __int64 byteOffset, __int64 byteTotal);

/******************************************************************************
FUNCTION: DFInstallDriver
PURPOSE:
	Install disk recovery driver
PARAMETERS:
	lpDFDriverFilePath	- disk filter driver file path
	lpTCDriverFilePath	- true cryp partition driver file path
	lpFSDriverFilePath	- file system filter driver file path
	lpPassWord			- initialize password
	lpPartitionPath		- path to file contain virtual parttition
	lpDriveLetters		- init protected volumes
RETURN TYPE:
	TRUE	- If the function succeeds, the return value is TRUE.
	FALSE	- If the function fails, the return value is FALSE.
COMMENTS:
******************************************************************************/
 BOOL WINAPI DFInstallDriver(LPCTSTR lpDFDriverFilePath,
							LPCTSTR lpTCDriverFilePath,
							LPCTSTR lpFSDriverFilePath,
							LPCTSTR lpPartitionPath, 
							LPCTSTR lpPassWord, 
							const char lpDriveLetters[26] = NULL);

/******************************************************************************
FUNCTION: DFUnInstallDriver
PURPOSE:
	UnInstall disk recovery driver
PARAMETERS:
RETURN TYPE:
	TRUE	- If the function succeeds, the return value is TRUE.
	FALSE	- If the function fails, the return value is FALSE.
COMMENTS:
******************************************************************************/
 BOOL WINAPI DFUnInstallDriver();

/******************************************************************************
FUNCTION: DFDriverIsRuning
PURPOSE:
	Check whether the driver has been installed
PARAMETERS:
RETURN TYPE:
	TRUE	- installed
	FALSE	- not be installed
COMMENTS:
******************************************************************************/
BOOL WINAPI DFDriverIsRuning();

/******************************************************************************
FUNCTION: DFChangePassWord
PURPOSE:
	Change disk recovery driver's password
PARAMETERS:
	lpPassWord			- password
RETURN TYPE:
	TRUE	- If the function succeeds, the return value is TRUE.
	FALSE	- If the function fails, the return value is FALSE.
COMMENTS:
******************************************************************************/
 BOOL WINAPI DFChangePassWord(LPCTSTR lpOldPassWord, LPCTSTR lpNewPassWord);

/******************************************************************************
FUNCTION: DFGetProtectInfo
PURPOSE:
	Change disk recovery driver's password
PARAMETERS:
	lpPassWord			- password
RETURN TYPE:
	TRUE	- If the function succeeds, the return value is TRUE.
	FALSE	- If the function fails, the return value is FALSE.
COMMENTS:
******************************************************************************/
 BOOL WINAPI DFGetProtectInfo(LPCTSTR lpPassWord, char DriveLetters[26], TCHAR *pcCacheContainDrive = NULL);

/******************************************************************************
FUNCTION: DFSetProtectInfo
PURPOSE:
	Get all partition protection status.
PARAMETERS:
	lpPassWord		- password
	DriveLetters	- Each partition (A-Z) protection status. For example, C to be protected, DriveLetters[3]'s value is 1, Otherwise, value is 0
RETURN TYPE:
	TRUE	- If the function succeeds, the return value is TRUE.
	FALSE	- If the function fails, the return value is FALSE.
COMMENTS:
******************************************************************************/
 BOOL WINAPI DFSetProtectInfo(LPCTSTR lpPassWord, const char DriveLetters[26]);

/******************************************************************************
FUNCTION: DFLogin
PURPOSE:
	Password authentication
PARAMETERS:
	lpPassWord		- password
RETURN TYPE:
	TRUE	- If the function succeeds, the return value is TRUE.
	FALSE	- If the function fails, the return value is FALSE.
COMMENTS:
	For the one you want to save an operation of file(or files), perform this function, after the execution of all operations, call "DFLogout"
******************************************************************************/
 BOOL WINAPI DFLogin(LPCTSTR lpPassWord);

/******************************************************************************
FUNCTION: DFLogout
PURPOSE:
	Password authentication
PARAMETERS:
	lpPassWord		- password
RETURN TYPE:
	TRUE	- If the function succeeds, the return value is TRUE.
	FALSE	- If the function fails, the return value is FALSE.
COMMENTS:
	For the one you want to save an operation of file(or files), perform this function, after the execution of all operations, call "DFLogout"
******************************************************************************/
 BOOL WINAPI DFLogout(LPCTSTR lpPassWord);

/******************************************************************************
FUNCTION: DFCreateFile
PURPOSE:
	If we need to save the file operations, must call this function to create file handle. 
PARAMETERS:
	The same as WINAPI: CreateFile
RETURN TYPE:
	The same as WINAPI: CreateFile
COMMENTS:
******************************************************************************/
 HANDLE WINAPI DFCreateFile(LPCTSTR lpFileName,
								   DWORD dwDesiredAccess,
								   DWORD dwShareMode,
								   LPSECURITY_ATTRIBUTES lpSecurityAttributes,
								   DWORD dwCreationDisposition,
								   DWORD dwFlagsAndAttributes,
								   HANDLE hTemplateFile);

/******************************************************************************
FUNCTION: DFDeleteFile
PURPOSE:
	If we need to save the file operations, must call this function to delete file. 
PARAMETERS:
	The same as WINAPI: DeleteFile
RETURN TYPE:
	The same as WINAPI: DeleteFile
COMMENTS:
******************************************************************************/
 BOOL WINAPI DFDeleteFile(LPCTSTR lpFileName);

/******************************************************************************
FUNCTION: DFCreateDirectory
PURPOSE:
	If we need to save the file operations, must call this function to create directory.
PARAMETERS:
	The same as WINAPI: CreateDirectory
RETURN TYPE:
	The same as WINAPI: CreateDirectory
COMMENTS:
******************************************************************************/
 BOOL WINAPI DFCreateDirectory(LPCTSTR lpPathName, LPSECURITY_ATTRIBUTES lpSecurityAttributes);

/******************************************************************************
FUNCTION: DFRemoveDirectory
PURPOSE:
	If we need to save the file operations, must call this function to remove directory.
PARAMETERS:
	The same as WINAPI: RemoveDirectory
RETURN TYPE:
	The same as WINAPI: RemoveDirectory
COMMENTS:
******************************************************************************/
 BOOL WINAPI DFRemoveDirectory(LPCTSTR lpPathName);

 BOOL WINAPI DFVerifyPassWord(LPCTSTR lpPassWord);
 BOOL WINAPI DFCopyFile(LPCTSTR lpExistingFileName, LPCTSTR lpNewFileName, BOOL bFailIfExists);
 BOOL WINAPI DFMoveFile(LPCTSTR lpExistingFileName, LPCTSTR lpNewFileName);
 BOOL WINAPI DFMoveFileEx(LPCTSTR lpExistingFileName, LPCTSTR lpNewFileName, DWORD dwFlags);

/*
FUNCTION: DFFlushShadowDeviceBuffers
PURPOSE:
	If we need to save the operation by DFCopyFile\DFMoveFile, you can call this function after all operation finished, To ensure all of the data has been written.
PARAMETERS:
	lpDriverLetter	- drive, for example: C:\\
RETURN TYPE:
	TRUE		- success
	FALSE		- failure
COMMENTS:
*/
 BOOL WINAPI DFFlushShadowDeviceBuffers(LPCTSTR lpDriverLetter);

 BOOL WINAPI DFRefreshVolume(LPCTSTR lpDriverLetter);

/*
FUNCTION: DFLogin_Once
PURPOSE:
	If you want the file(create by DFCreateFile) appear immediately in the explorer, you can call DFLogin_Once to replace DFLogin.
	Note, for safety, this function will cause partition dismount before call DFLogout_Once. So that, you can't call this function on system partition.
PARAMETERS:
	lpRootPathName	- for example: D:\\
RETURN TYPE:
	TRUE		- success
	FALSE		- failure
COMMENTS:
*/
 BOOL WINAPI DFLogin_Once(LPCTSTR lpPassWord, LPCTSTR lpRootPathName);
 BOOL WINAPI DFLogout_Once(LPCTSTR lpPassWord, LPCTSTR lpRootPathName);
 BOOL WINAPI DFIsShadowDeviceFile(LPCTSTR lpFileName);

/******************************************************************************
FUNCTION: DFSetPIDReadWriteThrough
PURPOSE:
	Call this function to set read/write through redirect for a process 
PARAMETERS:
	ULONG ulProcessId
RETURN TYPE:
	BOOL
COMMENTS:
******************************************************************************/
 BOOL WINAPI DFSetPIDReadWriteThrough(ULONG ulProcessId);

/******************************************************************************
FUNCTION: DFClearPIDReadWriteThrough
PURPOSE:
	Call this function to clear read/write through redirect for a process 
PARAMETERS:
	ULONG ulProcessId
RETURN TYPE:
	BOOL
COMMENTS:
******************************************************************************/
 BOOL WINAPI DFClearPIDReadWriteThrough(ULONG ulProcessId);

/******************************************************************************
FUNCTION: DFSetPIDReadWriteThroughAll
PURPOSE:
	Call this function to set read/write through all for a process 
PARAMETERS:
	ULONG ulProcessId
RETURN TYPE:
	BOOL
COMMENTS:
******************************************************************************/
#if 0
 BOOL WINAPI DFSetPIDReadWriteThroughAll(ULONG ulProcessId);
#else
 BOOL WINAPI DFSetPIDReadWriteThroughAll();
#endif

/******************************************************************************
FUNCTION: DFClearPIDReadWriteThroughAll
PURPOSE:
	Call this function to clear read/write through all for a process 
PARAMETERS:
	ULONG ulProcessId
RETURN TYPE:
	BOOL
COMMENTS:
******************************************************************************/
 #if 0
 BOOL WINAPI DFClearPIDReadWriteThroughAll(ULONG ulProcessId);
#else
BOOL WINAPI DFClearPIDReadWriteThroughAll();
#endif

/******************************************************************************
FUNCTION: DFCreateVPRT
PURPOSE:
Create virtual partition
PARAMETERS:
lpFilePath		- the path to file which contains partition
lpPassword		- initialize password
iFileSysType	- File system Type (NTFS, FAT, ...)
usSizeInGb		- size of partition in GB
hwCBParam		- param for calback funtion
fnCreatePartitionProressCB	- callback funtion to show progress
RETURN TYPE:
TRUE	- If the function succeeds, the return value is TRUE.
FALSE	- If the function fails, the return value is FALSE.
COMMENTS:
******************************************************************************/
BOOL WINAPI DFCreateVPRT(	LPCTSTR lpFilePath, 
					   LPCTSTR lpPassword,
					   int iFileSysType, 
					   unsigned short usSizeInGb, 
					   HWND hwCBParam, 
					   pfn_CreatePartitionProgressCallBack fnCreatePartitionProressCB);

/******************************************************************************
FUNCTION: DFUnmountVPRT
PURPOSE:
Unmount virtual partition
PARAMETERS:
RETURN TYPE:
TRUE	- If the function succeeds, the return value is TRUE.
FALSE	- If the function fails, the return value is FALSE.
COMMENTS:
******************************************************************************/
BOOL WINAPI DFUnmountVPRT(int nDosCacheDrive);

 /******************************************************************************
 FUNCTION: DFPathFileExist
 PURPOSE:
 Check to know a file is exist or read or write or not
 PARAMETERS:
 None
 RETURN TYPE:
 BOOL
 COMMENTS:
 ******************************************************************************/
 BOOL WINAPI DFPathFileExists(LPCTSTR lpFilePath);
 
 /******************************************************************************
 FUNCTION: DFCopyFileFromVirtualToReal
 PURPOSE:
 Check to know a file is exist or read or write or not
 PARAMETERS:
 None
 RETURN TYPE:
 BOOL
 COMMENTS:
 ******************************************************************************/
 BOOL WINAPI DFCopyFileFromVirtualToReal(LPCTSTR lpExistingVirFileName, LPCTSTR lpNewRealFileName, BOOL bFailIfExists);
 
 /******************************************************************************
 FUNCTION: DFCopyFileFromRealToVirtual
 PURPOSE:
 Check to know a file is exist or read or write or not
 PARAMETERS:
 None
 RETURN TYPE:
 BOOL
 COMMENTS:
 ******************************************************************************/
 BOOL WINAPI DFCopyFileFromRealToVirtual(LPCTSTR lpExistingRealFileName, LPCTSTR lpNewVirFileName, BOOL bFailIfExists);
 
 
 int WINAPI DFutime32(LPCTSTR lpExistingRealFileName,  struct __utimbuf32 *put);
