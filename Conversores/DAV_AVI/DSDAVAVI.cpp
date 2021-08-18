// DSDAVAVI.cpp : Este arquivo contém a função 'main'. A execução do programa começa e termina ali.
//

#include <iostream>
#include <Windows.h>
#include "AppSettings.h"
#include "cxxopts.hpp"
#include <io.h>

#define STREAME_FILE 1

#define BUF_VIDEO_SRC					1		// Video source buffer
#define BUF_AUDIO_SRC					2		// Audio source buffer
#define BUF_VIDEO_RENDER				3		// Video data buffer after decoding
#define BUF_AUDIO_RENDER				4		// Audio data buffer after decoding
#define BUF_VIDEO_ALL					5		// ALL Video data buffer(millisecond)


typedef enum
{
    DATA_RECORD_ORIGINAL = 0,     // Raw video stream
    DATA_RECORD_AVI,              // AVI
    DATA_RECORD_ASF,              // ASF   
    DATA_RECORD_ORIGINAL_SEGMENT, // Segment Raw video stream
    DATA_RECORD_RESIZE_AVI,       // Resolution Changed AVI, target width and height is needed. use PLAY_ResolutionScale.
    DATA_RECORD_MP4,              // MP4 
    DATA_RECORD_RESIZE_MP4,       // Resolution Changed MP4, target width and height is needed. use PLAY_ResolutionScale.
    DATA_RECORD_MP4_NOSEEK,       // No Seek MP4    
    DATA_RECORD_RESIZE_MP4_NOSEEK,// Resolution Changed No Seek MP4, target width and height is needed. use PLAY_ResolutionScale.
    DATA_RECORD_TS,
    DATA_RECORD_PS,               // PS
    DATA_RECORD_RESIZE_DAV,
    DATA_RECORD_DAV,
    DATA_RECORD_AAC,              // AAC(Raw Audio)
    DATA_RECORD_WAV,              // WAV(Raw Audio)
    DATA_RECORD_COUNT			  // record type count 
}DATA_RECORD_TYPE;

typedef BOOL(__stdcall* PLAY_SetStreamOpenMode)(LONG, DWORD);
typedef BOOL(__stdcall* PLAY_OpenStream)(LONG, PBYTE, DWORD, DWORD);
typedef BOOL(__stdcall* PLAY_CloseStream)(LONG);
typedef BOOL(__stdcall* PLAY_Play)(LONG, HWND);
typedef BOOL(__stdcall* PLAY_Stop)(LONG);
typedef void (__stdcall* fRecordDataCBFun)(LONG nPort, unsigned char* pData, int nDataLen, LONGLONG nOffset, void* pUserData);
typedef BOOL(__stdcall* PLAY_StartDataRecordEx)(LONG, char*, int, fRecordDataCBFun, void*);
typedef BOOL(__stdcall* PLAY_StopDataRecord)(LONG);
typedef BOOL(__stdcall* PLAY_InputData)(LONG, PBYTE, DWORD);
typedef DWORD(__stdcall* PLAY_GetBufferValue)(LONG, DWORD);
typedef DWORD(__stdcall* PLAY_GetSourceBufferRemain)(LONG);


void PrintHeader()
{
    printf("DAHUA DAV to AVI/MP4 Converter %s\nby Davi Santos\n\n", AppSettings::APPVERSION);
}

int main(int argc, char** argv)
{
    PrintHeader();

    std::string inputFile;
    std::string outputFile;
    int format = 0;
    bool showHelp = false;
    bool noInput = argc < 2;

    cxxopts::Options options("DSHDAVAVI", "");
    options.custom_help("{ -h | -i <input file.dav> -o <output file.avi> [-f <format>] }");
    options.add_options()
        ("h,help", "Show Help.")
        ("i,input", "Input H264 file", cxxopts::value<std::string>(), "file.dav")
        ("o,output", "Output file file.", cxxopts::value<std::string>(), "file.avi")
        ("f,format", "Output format: 0 (AVI), 1 (MP4). Default: 0 (AVI)", cxxopts::value<int>(), "number");
    auto result = options.parse(argc, argv);

    if (result.count("help") || noInput)
    {
        std::cout << options.help() << std::endl;
        return 0;
    }
    if (result.count("format"))
    {
        format = result["format"].as<int>();
    }
    if (result.count("input"))
    {
        inputFile = result["input"].as<std::string>();
    }
    if (result.count("output"))
    {
        outputFile = result["output"].as<std::string>();
    }

    if (showHelp || (inputFile.empty() || outputFile.empty()))
    {
        std::cout << options.help() << std::endl;
        return 0;
    }

    int fd = _dup(1);
    FILE* pStream = 0;
    if(fopen_s(&pStream, "log.txt", "w") != 0)
    {
        printf("Error creating log file\n");
        return -1;
    }
    _dup2(_fileno(pStream), 1);
    HINSTANCE dll = LoadLibraryA("./dhplay.dll");
    fflush(stdout);
    fclose(pStream);
    _dup2(fd, 1);

    if (dll == 0)
    {
        printf("Unable to load the dhplay.dll library!");
        return -1;
    }

    PLAY_SetStreamOpenMode SetStreamOpenMode = (PLAY_SetStreamOpenMode)GetProcAddress(HMODULE(dll), "PLAY_SetStreamOpenMode");
    PLAY_OpenStream OpenStream = (PLAY_OpenStream)GetProcAddress(HMODULE(dll), "PLAY_OpenStream");
    PLAY_CloseStream CloseStream = (PLAY_CloseStream)GetProcAddress(HMODULE(dll), "PLAY_CloseStream");
    PLAY_Play Play = (PLAY_Play)GetProcAddress(HMODULE(dll), "PLAY_Play");
    PLAY_Stop Stop = (PLAY_Stop)GetProcAddress(HMODULE(dll), "PLAY_Stop");
    PLAY_StartDataRecordEx StartDataRecordEx = (PLAY_StartDataRecordEx)GetProcAddress(HMODULE(dll), "PLAY_StartDataRecordEx");
    PLAY_InputData InputData = (PLAY_InputData)GetProcAddress(HMODULE(dll), "PLAY_InputData");
    PLAY_GetBufferValue GetBufferValue = (PLAY_GetBufferValue)GetProcAddress(HMODULE(dll), "PLAY_GetBufferValue");
    PLAY_GetSourceBufferRemain GetSourceBufferRemain = (PLAY_GetSourceBufferRemain)GetProcAddress(HMODULE(dll), "PLAY_GetSourceBufferRemain");
    PLAY_StopDataRecord StopDataRecord = (PLAY_StopDataRecord)GetProcAddress(HMODULE(dll), "PLAY_StopDataRecord");

    printf("Converting \"%s\" to \"%s\"\n", inputFile.c_str(), outputFile.c_str());

    FILE* pFile = 0;
    if (fopen_s(&pFile, inputFile.c_str(), "rb") != 0) {
        printf("Error opening\n");
        return 0;
    }

    fseek(pFile, 0, SEEK_END);
    long fileSize = ftell(pFile);
    fseek(pFile, 0, SEEK_SET);

    SetStreamOpenMode(0, STREAME_FILE);
    OpenStream(0, NULL, 0, 500 * 1024);
    Play(0, NULL);

    if (!StartDataRecordEx(0, (char*) outputFile.c_str(),  (format == 0)? DATA_RECORD_TYPE::DATA_RECORD_AVI: DATA_RECORD_TYPE::DATA_RECORD_MP4, NULL, NULL))
    {
        printf("Error converting\n");
        Stop(0);
        CloseStream(0);
        return 0;
    }

    unsigned long long readPos = 0;
    const int readlen = 8 * 1024;
    BYTE readBuf[readlen];
    while (1)
    {
        size_t readed = fread_s(readBuf, readlen, sizeof(BYTE), readlen, pFile);
        if (readed <= 0) break;

        while (!InputData(0, readBuf, readlen))
        {
            Sleep(10);
        }
        readPos += readed;
        printf("\rProgress: %0.2f", ((double)readPos / (double)fileSize)*100.0);
    }

    while ((GetBufferValue(0, BUF_VIDEO_RENDER) + GetSourceBufferRemain(0)) > 0)
    {
        Sleep(5);
    }

    StopDataRecord(0);
    Stop(0);
    CloseStream(0);
    printf("\nDone!\n");

    fclose(pFile);
    pFile = 0;
    FreeLibrary(dll);
    return 0;
}
