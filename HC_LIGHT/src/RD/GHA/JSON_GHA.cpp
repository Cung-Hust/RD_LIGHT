#include "../GHA/JSON/JSON_GHA.hpp"
#include "../AHG/JSON/JSON_AHG.hpp"

queue<string> queue_gha;

extern struct mosquitto *mosq;
template<typename T>
string toStringAA(const T& value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

char* ToCharAA(string s) {
	char *send = new char[s.length() + 1];
	strcpy(send, s.c_str());
	return send;
}

int JsonParseGw(struct mosquitto *mosq, char * jobj){
	string json = toStringAA(jobj);
	queue_gha.push(json);
	return 0;
}

void* GHA_MQTT(void *argv){
	while(true){
		int sizea = queue_gha.size();
		while(sizea != 0) {
			string item = queue_gha.front();
			char *jobj = ToCharAA(item);
			AdrGwToApp(mosq, jobj);
			TYPEDEVICE(mosq, jobj);
			queue_gha.pop();
			sizea = queue_gha.size();
		}
		sleep(1);
	}
	return 0;
}
