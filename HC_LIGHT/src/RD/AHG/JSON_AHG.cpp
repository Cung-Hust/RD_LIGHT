#include "../AHG/JSON/JSON_AHG.hpp"

/*-----------------------------------------------convert-------------------------------------------------------*/

queue<string> queue_ahg;
extern struct mosquitto *mosq;
template<typename T>
string ToString(const T& value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

char* ToChar(string s) {
	char *send = new char[s.length() + 1];
	strcpy(send, s.c_str());
	return send;
}

//convert data json from APP

int JsonParseApp(struct mosquitto *mosq, char * jobj){
	string json = ToString(jobj);
	queue_ahg.push(json);
	return 0;
}

void* AHG_MQTT(void *argv){
	while(true){
		int size = queue_ahg.size();
		while(size != 0) {
			string item = queue_ahg.front();
			char * jobj = ToChar(item);
			CheckCmd(mosq, jobj);
			queue_ahg.pop();
			size = queue_ahg.size();
		}
		sleep(1);
	}
	return 0;
}
