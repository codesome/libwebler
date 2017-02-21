#include <iostream>
#include <regex>
#include <string>
#include <thread>
#include <web/Channel.hpp>
#include <web/DepthHandler.hpp>
using namespace std;

// TODO: update with proper regex to test
void DH_function(web::Channel<web::channel_data> *chanGet,web::Channel<web::channel_data> *chanPut) {
	web::DepthHandler DH(
		string("(.*?)"),
		chanGet,
		chanPut,
		true
	);

	DH.start();
}

int main () {

	web::Channel<web::channel_data> *chan_get = new web::Channel<web::channel_data>;
	web::Channel<web::channel_data> *chan_put = new web::Channel<web::channel_data>;
	
	web::channel_data c_get_data, c_res_data;
	
	c_get_data.links.push_back(string("http://timesofindia.indiatimes.com/2016/1/1/archivelist/year-2016,month-1,starttime-42370.cms"));
	chan_get->add(c_get_data);

	thread t = thread(DH_function,chan_get,chan_put);
	
	bool closed;
	cout << "Waiting to retrieve ..." << endl;
	c_res_data = chan_put->retrieve(&closed);
	chan_get->close();
	cout << "Retrieved ..." << endl;

	for(vector<string>::iterator it=c_res_data.links.begin(); it!=c_res_data.links.end(); ++it ) {
   		cout << *it << endl;
	}

	t.join();
	cout << "DepthHandler test is over" << endl;

	return 0;
}