#include "Spider.h"

int main()
{

	cout << "*************************************************************" << endl;
	cout << "                 欢迎使用人工智能网络爬虫系统                     " << endl;
	cout << "*************************************************************" << endl;
	cout << "请输入一个要抓取的URL链接:" << endl;

	string url = "http://www.manzhan.com/wangzhi.html ";
	//cin >> url;
	//创建文件夹 windows API
	CreateDirectory(L"./image",NULL);

	//开始抓取
	StartCatch(url);
	return 0;
}

bool StartCatch(string url)
{
	//爬虫系统原理
	queue < string > q;
	q.push(url);
	while (!q.empty())
	{
		//抓取
		//1、取url-》再解析
		string currentUrl=q.front();
		q.pop();
		CHttp http;

		http.Init();
		//2、解析url
		http.AnalyseUrl(currentUrl);
		//连接服务器
		http.Connent();
		//获取网页
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

	//创建套接字
	//协议：TCP/UDP
	m_socket=socket(AF_INET, SOCK_STREAM,0);
	if (m_socket == INVALID_SOCKET)
		return false;
	return true;
}

bool CHttp::AnalyseUrl(string url){//解析Url
	//字符串大小写转换，全转成小写

	if (string::npos == url.find("http://"))
		return false;
	if (url.length() <= 7)
		return false;
	//查找/
	int pos=url.find('/', 7);
	if (pos == string::npos)//找到主机名
	{
		m_host = url.substr(7);//7表示从第7个字符开始截取
		m_object = "/";
	}
	else//资源路劲
	{
		m_host = url.substr(7, pos - 7);//第二个参数表示要截取多少个字符
		m_object = url.substr(pos);
	}
	if (m_host.empty())
		return false;
	cout << "主机名:"<< m_host << "\t资源路径:" << m_object << endl;
	return true;
}

//连接服务器
//网络编程
bool CHttp::Connent(){
	HOSTENT *p=gethostbyname(m_host.c_str());
	if (p == NULL)
		return false;
	//连接服务器
	sockaddr_in sa;
	memcpy(&sa.sin_addr, p->h_addr, 4);
	sa.sin_family = AF_INET;//ipv4
	sa.sin_port = htons(80);//web服务器默认端口：80
	//连接服务器
	if (SOCKET_ERROR == connect(m_socket, (sockaddr *)&sa, sizeof(sa)))
		return false;
	
	return true;
}
bool CHttp::FetchhHtml(string &html){//获取网页

	//HTTP
	//GET请求
	//POST

	//发送GET请求
	string info;
	info = info + "GET " + m_object + " HTTP/1.1\r\n";
	info = info + "Host: " + m_host + "\r\n";
	info = info + "User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/70.0.3538.25 Safari/537.36 Core/1.70.3741.400 QQBrowser/10.5.3863.400\r\n";
	info = info + "Connection: Close\r\n\r\n";

	//发送
	if (SOCKET_ERROR == send(m_socket, info.c_str(), info.length(), 0))
		return false;
	//接收
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

//下载资源
bool CHttp::Download(string url, string filename){
	return true;
}