#include "StdAfx.h"
#include "FileSignature.h"
#include "FileUtility.h"

CFileSignature::CFileSignature(void)
{
    m_cKey[0] = -5;

    for (int i = 1; i < KEY_LENGTH; i++)
    {
        m_cKey[i] = 2*m_cKey[i - 1] - 3*i + 5;
    }

    m_hFile = INVALID_HANDLE_VALUE;
}

CFileSignature::~CFileSignature(void)
{

}

BOOL CFileSignature::Sign( LPCTSTR strFilePath )
{
    m_hFile = ::CreateFile(strFilePath, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
   
	BOOL bResult = TRUE;

    try
    {
        CFileUtility fileUtility;

        if (FALSE == fileUtility.GetFileSize(m_hFile, &m_ui64RealFileSize))
        {
            throw L"Fail to get file size\n";
        }

        if (m_ui64RealFileSize < KEY_LENGTH)
        {
            throw L"File size is too small\n";
        }

        if (FALSE == ReadThreeByteArrays())
        {
            throw L"Fail to read three byte arrays\n";
        }

        GenerateSignature();

        if (FALSE == WriteSignature())
        {
            throw L"Fail to write signature\n";
        }

    }
    catch (LPCTSTR strErrorMessage)
    {
        ::OutputDebugString(strErrorMessage);
        bResult = FALSE;
    }

    if (INVALID_HANDLE_VALUE != m_hFile)
    {
        ::CloseHandle(m_hFile);
        m_hFile = INVALID_HANDLE_VALUE;
    }

    return bResult;
}

BOOL CFileSignature::VerifySignature( LPCTSTR strFilePath )
{
    m_hFile = ::CreateFile(strFilePath, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    
	BOOL bResult = TRUE;

    try
    {
        CFileUtility fileUtility;
        unsigned __int64 ui64FileSize;

        if (FALSE == fileUtility.GetFileSize(m_hFile, &ui64FileSize))
        {
            throw L"Fail to get file size\n";
        }

        if (ui64FileSize < 2*KEY_LENGTH)
        {
            throw L"Invalid input\n";
        }

        m_ui64RealFileSize = ui64FileSize - KEY_LENGTH;

        if (FALSE == ReadThreeByteArrays())
        {
            throw L"Fail to read three byte arrays\n";
        }

        GenerateSignature();

        if (FALSE == CompareSignature())
        {
            bResult = FALSE;
        }

    }
    catch (LPCTSTR strErrorMessage)
    {
        ::OutputDebugString(strErrorMessage);
        bResult = FALSE;
    }

    if (INVALID_HANDLE_VALUE != m_hFile)
    {
        ::CloseHandle(m_hFile);
        m_hFile = INVALID_HANDLE_VALUE;
    }

    return bResult;
}

BOOL CFileSignature::ReadThreeByteArrays()
{

    if (INVALID_HANDLE_VALUE == m_hFile)
    {
        return FALSE;
    }

    LARGE_INTEGER liIndex;

	liIndex.QuadPart = 0;
    if (FALSE == ReadOneByteArray(m_hFile, &liIndex, m_cHeadBytes))
    {
        return FALSE;
    }

    liIndex.QuadPart = m_ui64RealFileSize/2 - KEY_LENGTH/2;
    if (FALSE == ReadOneByteArray(m_hFile, &liIndex, m_cMiddleBytes))
    {
        return FALSE;
    }

    liIndex.QuadPart = m_ui64RealFileSize - KEY_LENGTH;
    if (FALSE == ReadOneByteArray(m_hFile, &liIndex, m_cTailBytes))
    {
        return FALSE;
    }

    return TRUE;
}

BOOL CFileSignature::ReadOneByteArray( HANDLE hFile, LARGE_INTEGER *pliIndex, char* pcBuffer )
{
    if (FALSE == SetFilePointerEx(hFile, *pliIndex, NULL, FILE_BEGIN))
    {
        return FALSE;
    }

    DWORD dwBytesRead = 0;

    if (FALSE == ::ReadFile(hFile, pcBuffer, KEY_LENGTH, &dwBytesRead, NULL))
    {
        return FALSE;
    }

    if (dwBytesRead != KEY_LENGTH)
    {
        return FALSE;
    }

    return TRUE;
}

void CFileSignature::GenerateSignature()
{
    XorTwoByteArray(m_cMiddleBytes, m_cKey);
    XorTwoByteArray(m_cSignature, m_cHeadBytes);
    XorTwoByteArray(m_cSignature, m_cTailBytes);
}

void CFileSignature::XorTwoByteArray( char *pcFirstBuffer, char *pcSecondBuffer )
{
    for (int i = 0; i < KEY_LENGTH; i++)
    {
        m_cSignature[i] = pcFirstBuffer[i] ^ pcSecondBuffer[i];
    }
}

BOOL CFileSignature::WriteSignature()
{
    DWORD dwPtr = ::SetFilePointer(m_hFile, 0, NULL, FILE_END);

    if (INVALID_SET_FILE_POINTER == dwPtr && GetLastError() != NO_ERROR)
    {
        return FALSE;
    }

    DWORD dwBytesWritten = 0;

    if (FALSE == ::WriteFile(m_hFile, m_cSignature, KEY_LENGTH, &dwBytesWritten, NULL))
    {
        return FALSE;
    }

    if (dwBytesWritten != KEY_LENGTH)
    {
        return FALSE;
    }

    return TRUE;
}

BOOL CFileSignature::CompareSignature()
{
    DWORD dwBytesRead = 0;
    char cBuffer[KEY_LENGTH];

    LARGE_INTEGER liIndex;
    liIndex.QuadPart = m_ui64RealFileSize;

    if (FALSE == ReadOneByteArray(m_hFile, &liIndex, cBuffer))
    {
        return FALSE;
    }

    for (int i = 0; i < KEY_LENGTH; i++)
    {
        if (cBuffer[i] != m_cSignature[i])
        {
            return FALSE;
        }
    }

    return TRUE;
}
