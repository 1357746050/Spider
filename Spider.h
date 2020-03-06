#include<iostream>
#include <string>
#include <Windows.h>
#include <queue>
//#include<WinSock2.h>
using namespace std;
#pragma comment(lib,"ws2_32.lib")
//开始抓取
bool StartCatch(string url);

//http操作
class CHttp
{
public:
	bool AnalyseUrl(string url);					//解析网页
	bool Connent();						//连接服务器
	bool FetchhHtml(string &html);//获取网页
	bool AnalyseHtml();					//解析网页
	bool Download(string url, string filename);//下载资源
	bool Init();//初始化网络

private:
	string m_host;//主机名
	string m_object;//资源路径
	SOCKET m_socket;

};

