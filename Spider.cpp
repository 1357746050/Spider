#include "Spider.h"

int main()
{

	cout << "*************************************************************" << endl;
	cout << "                 ��ӭʹ���˹�������������ϵͳ                     " << endl;
	cout << "*************************************************************" << endl;
	cout << "������һ��Ҫץȡ��URL����:" << endl;

	string url = "http://www.manzhan.com/wangzhi.html ";
	//cin >> url;
	//�����ļ��� windows API
	CreateDirectory(L"./image",NULL);

	//��ʼץȡ
	StartCatch(url);
	return 0;
}

bool StartCatch(string url)
{
	//����ϵͳԭ��
	queue < string > q;
	q.push(url);
	while (!q.empty())
	{
		//ץȡ
		//1��ȡurl-���ٽ���
		string currentUrl=q.front();
		q.pop();
		CHttp http;

		http.Init();
		//2������url
		http.AnalyseUrl(currentUrl);
		//���ӷ�����
		http.Connent();
		//��ȡ��ҳ
		string html;
		http.FetchhHtml(html);
		cout << html << endl;

	}
	return true;
}
bool CHttp::Init()
{
	WSADATA wd;
	if (0 != WSAStartup(MAKEWORD(2, 2), &wd))
		return false;
	if (LOBYTE(wd.wVersion) != 2 || HIBYTE(wd.wVersion) != 2)
		return false;

	//�����׽���
	//Э�飺TCP/UDP
	m_socket=socket(AF_INET, SOCK_STREAM,0);
	if (m_socket == INVALID_SOCKET)
		return false;
	return true;
}

bool CHttp::AnalyseUrl(string url){//����Url
	//�ַ�����Сдת����ȫת��Сд

	if (string::npos == url.find("http://"))
		return false;
	if (url.length() <= 7)
		return false;
	//����/
	int pos=url.find('/', 7);
	if (pos == string::npos)//�ҵ�������
	{
		m_host = url.substr(7);//7��ʾ�ӵ�7���ַ���ʼ��ȡ
		m_object = "/";
	}
	else//��Դ·��
	{
		m_host = url.substr(7, pos - 7);//�ڶ���������ʾҪ��ȡ���ٸ��ַ�
		m_object = url.substr(pos);
	}
	if (m_host.empty())
		return false;
	cout << "������:"<< m_host << "\t��Դ·��:" << m_object << endl;
	return true;
}

//���ӷ�����
//������
bool CHttp::Connent(){
	HOSTENT *p=gethostbyname(m_host.c_str());
	if (p == NULL)
		return false;
	//���ӷ�����
	sockaddr_in sa;
	memcpy(&sa.sin_addr, p->h_addr, 4);
	sa.sin_family = AF_INET;//ipv4
	sa.sin_port = htons(80);//web������Ĭ�϶˿ڣ�80
	//���ӷ�����
	if (SOCKET_ERROR == connect(m_socket, (sockaddr *)&sa, sizeof(sa)))
		return false;
	
	return true;
}
bool CHttp::FetchhHtml(string &html){//��ȡ��ҳ

	//HTTP
	//GET����
	//POST

	//����GET����
	string info;
	info = info + "GET " + m_object + " HTTP/1.1\r\n";
	info = info + "Host: " + m_host + "\r\n";
	info = info + "User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/70.0.3538.25 Safari/537.36 Core/1.70.3741.400 QQBrowser/10.5.3863.400\r\n";
	info = info + "Connection: Close\r\n\r\n";

	//����
	if (SOCKET_ERROR == send(m_socket, info.c_str(), info.length(), 0))
		return false;
	//����
	char ch = 0;
	int nrecv = 0;
	while ((nrecv=recv(m_socket, &ch, sizeof(ch), 0))>0)
	{
		html = html + ch;
	}
	return true;
}
bool CHttp::AnalyseHtml(){
	return true;
}

//������Դ
bool CHttp::Download(string url, string filename){
	return true;
}