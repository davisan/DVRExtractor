#include <iostream>
#include <cstdio>
#include <windows.h>
#include "cxxopts.hpp"
#include "AppSettings.h"

typedef void (__stdcall *CoverFileCallBack) (DWORD CurrentPos, DWORD TotalPos, long dwUser);
typedef DWORD (__stdcall *H264_PLAY_GetSdkVersion)();
typedef BOOL  (__stdcall *H264_PLAY_GetPort)(LONG*);
typedef BOOL  (__stdcall * H264_PLAY_FreePort)(LONG);
typedef int  (__stdcall * H264_PLAY_ConvertFile)(const char*, const char*, LONG, CoverFileCallBack, DWORD);

volatile int done = 0;
void __stdcall MyCallback(DWORD p, DWORD total, long port)
{
	printf("\rProgress: %0.2f%%", (p/(float) total)*100.0f);
	if (p >= total) 
	{
		done++;
	}
}

void PrintHeader()
{
	printf("WFS .H264 to AVI Converter %s\nby Davi Santos - %s\n\n", AppSettings::APPVERSION, AppSettings::ContactEmail);
}

void PrintHelp()
{
	printf("Usage:\n");
	printf("\t-h\t\tShow help\n");
	printf("\t--input/-i inputfile.H264\n");
	printf("\t--output/-o outputfile.avi\n");
}

int main(int argc, char* argv[])
{
	PrintHeader();

	std::string inputFile;
	std::string outputFile;
	DWORD waitTime = 1000;
	bool showHelp = false;
	bool useH265 = false;
	bool noInput = argc < 2;

	cxxopts::Options options("DSH264AVI", "");
	options.custom_help("{ -h | -i <input file.h264> -o <output file.avi> [-w <wait time>] }");
	options.add_options()
		("h,help", "Show Help.")
		("i,input", "Input H264 file", cxxopts::value<std::string>(), "file.h264")
		("o,output", "Output AVI file.", cxxopts::value<std::string>(), "file.avi")
		("x,hevc", "Use with H265 video stream.")
		("w,wait", "Wait time after conversion in miliseconds. Optional", cxxopts::value<int>(), "miliseconds");
	auto result = options.parse(argc, argv);
	if (result.count("help") || noInput)
	{
		std::cout << options.help() << std::endl;
		return 0;
	}
	if (result.count("wait"))
	{
		waitTime = result["wait"].as<int>();
	}
	if (result.count("input"))
	{
		inputFile = result["input"].as<std::string>();
	}
	if (result.count("output"))
	{
		outputFile = result["output"].as<std::string>();
	}
	if (result.count("hevc"))
	{
		useH265 = true;
	}
	if (showHelp || (inputFile.empty() || outputFile.empty()))
	{
		std::cout << options.help() << std::endl;
		return 0;
	}

	HINSTANCE dll = LoadLibraryA("./H264Play.dll"); 
	if (dll == 0)
	{
		printf("Unable to load the H264Play.dll library!");
		return -1;
	}
	H264_PLAY_GetSdkVersion GetSDK = (H264_PLAY_GetSdkVersion)GetProcAddress(HMODULE(dll), "H264_PLAY_GetSdkVersion");
	H264_PLAY_GetPort GetPort = (H264_PLAY_GetPort)GetProcAddress(HMODULE(dll), "H264_PLAY_GetPort");
	H264_PLAY_FreePort FreePort = (H264_PLAY_FreePort)GetProcAddress(HMODULE(dll), "H264_PLAY_FreePort");
	H264_PLAY_ConvertFile ConverFile = (H264_PLAY_ConvertFile)GetProcAddress(HMODULE(dll), "H264_PLAY_ConvertFile");

	printf("Converting \"%s\" to \"%s\"\n", inputFile.c_str(), outputFile.c_str());

	long port = 0;
	GetPort(&port);
	done = false;
	ConverFile(inputFile.c_str(), outputFile.c_str(), 2, &MyCallback, port);
	while (1) 
	{  
		if (done == 2) { break; }
	}
	Sleep(waitTime);
	FreePort(port);
	FreeLibrary(dll);
	if (useH265)
	{
		FILE* pFile = 0;
		if (fopen_s(&pFile, outputFile.c_str(), "r+b") == 0)
		{
			unsigned char H265[] = { 'H', 'E', 'V', 'C' };
			fseek(pFile, 0x70, SEEK_SET);
			fwrite(H265, sizeof(unsigned char), 4, pFile);
			fseek(pFile, 0xBC, SEEK_SET);
			fwrite(H265, sizeof(unsigned char), 4, pFile);
			fclose(pFile);
		}
	}
	
	printf("\nDone!\n");
	
	return 0;
}
