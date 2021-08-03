#include "JSON_AHG.hpp"
#include "../../MQTT/MQTT.hpp"
#include <sqlite3.h>
#include <unistd.h>

// Convert between data types
template<typename T>
string toString(const T& value)
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

// Check CMD

void CheckCmd(struct mosquitto *mosq, char* jobj){
	Document document;
	try {
		document.Parse(jobj);
		StringBuffer sendToApp;
		Writer<StringBuffer> json(sendToApp);
	}
	catch (int n) {
		cout << "----------------------------------------------" << endl;
		cout << "                   JSON error                 " << endl;
		cout << "----------------------------------------------" << endl;
	}

	string rqi 		= document["RQI"].GetString();
	string typcmd 	= document["TYPCMD"].GetString();

	
	if(typcmd.compare("Ping") == 0){
		Ping(mosq, jobj);
	}
	else if(typcmd.compare("NetInfor") == 0){
		NetInfor(mosq,jobj);
	}
	else if(typcmd.compare("NewDevice") == 0){
		NewDevice(mosq,jobj);
	}
	else if(typcmd.compare("DeviceStatus") == 0){
		DeviceStatus(mosq,jobj);
	}
	else if(typcmd.compare("DeviceReport") == 0){
		DeviceReport(mosq, jobj);
	}
	else {
		cout << "----------------------------------------------" << endl;
		cout << "                    CMD error                 " << endl;
		cout << "----------------------------------------------" << endl;
	}
}

// ==========================================================================================================================================
// ==========================================================================================================================================

void Ping(const char *mosq, jobj) {
	Document document;
	document.Parse(jobj);
	StringBuffer sendToApp;
	Writer<StringBuffer> json(down_message);
	const Value& DATA = document["DATA"];
	int deviceUnicast = DATA["DEVICE_UNICAST_ID"].GetInt();
}

// ==========================================================================================================================================
// ==========================================================================================================================================

void NetInfor(const char *mosq, jobj) {
	
}

// ==========================================================================================================================================
// ==========================================================================================================================================

void NewDevice(const char *mosq, jobj) {
	
}

// ==========================================================================================================================================
// ==========================================================================================================================================

void DeviceStatus(const char *mosq, jobj) {
	
}