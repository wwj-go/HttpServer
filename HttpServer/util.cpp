#include <vector>
#include <stdlib.h>  
#include <string.h>  
#include <time.h>  
#include <string>

std::vector<std::string> split(std::string str, std::string pattern)
{
	std::string::size_type pos;
	std::vector<std::string> result;
	str += pattern;//扩展字符串以方便操作
	int size = str.size();

	for (int i = 0; i < size; i++)
	{
		pos = str.find(pattern, i);
		if (pos < size)
		{
			std::string s = str.substr(i, pos - i);
			result.push_back(s);
			i = pos + pattern.size() - 1;
		}
	}
	return result;
}


int getGmtTime(char* szGmtTime)
{
	if (szGmtTime == NULL)
	{
		return -1;
	}
	time_t rawTime;
	struct tm* timeInfo;
	char szTemp[30] = { 0 };
	time(&rawTime);
	timeInfo = gmtime(&rawTime);
	strftime(szTemp, sizeof(szTemp), "%a, %d %b %Y %H:%M:%S GMT", timeInfo);
	strcpy(szGmtTime, szTemp);
	return strlen(szGmtTime);
}

std::string getType(std::string ext) {

	if (ext == "jpg" || ext == "png" || ext == "jpeg")
	{
		return "image/jpeg";
	}
	if (ext == "html")
	{
		return "text/html;charset=utf-8";
	}
	if (ext == "css")
	{
		return "text/css;charset=utf-8";
	}
	if (ext == "js")
	{
		return "text/js;charset=utf-8";
	}
	if (ext == "mp4")
	{
		return "video/mpeg4";
	}
	if (ext == "mp3")
	{
		return "audio/mp3";
	}
	if (ext == "wav") 
	{
		return "audio/wav";
	}
	return "application/octet-stream";
}

