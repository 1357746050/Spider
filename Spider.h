#include<iostream>
#include <string>
#include <Windows.h>
#include <queue>
//#include<WinSock2.h>
using namespace std;
#pragma comment(lib,"ws2_32.lib")
//��ʼץȡ
bool StartCatch(string url);

//http����
class CHttp
{
public:
	bool AnalyseUrl(string url);					//������ҳ
	bool Connent();						//���ӷ�����
	bool FetchhHtml(string &html);//��ȡ��ҳ
	bool AnalyseHtml();					//������ҳ
	bool Download(string url, string filename);//������Դ
	bool Init();//��ʼ������

private:
	string m_host;//������
	string m_object;//��Դ·��
	SOCKET m_socket;

};

