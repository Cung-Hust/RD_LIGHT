/*
 * TIMER_PARES.cpp
 *
 *  Created on: Apr 14, 2021
 *      Author: trthang
 */




#include "TIMER_PARES.hpp"
#include "../AHG/JSON/JSON_AHG.hpp"
#include "../../RD/MQTT/MQTT.hpp"
//#include <stack>


template<typename T>
string toString(const T& value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

char* ToCharTimer(string s) {
	char *sendChar = new char[s.length() + 1];
	strcpy(sendChar, s.c_str());
	return sendChar;
}

int TimerOver;
string weekDayss;

//---------------------------

int *arrStart;
int *arrEnd;
int *arr;
int lengtStart;
int lengtEnd;

char * cEndAt;
char * cStartAt;
int LOGIC_RULE_ID = 3;
int UNICAST = 0;
int value_input = -1;
int FlagCheckRuleAnd = false;
bool HasButtonInRule = false;
int NumberOfButtonInRuleAnd = 0;

StringBuffer sendGW;
Writer<StringBuffer> jsonS(sendGW);

char* CheckType;
int ADRTIMER;

int NumberOfRuleInputAnd = 0;

int thayDoi;


//stack <int> Device;
//stack <int> Group;


/*-----------------------------------------------DATABASE---------------------------------------------------------*/
static int RULEDEVICE(void *data, int argc, char **argv, char **azColName){

	// cout << "INTO RULEDEVICE"<<endl;
	if((const char*) argv[0] != NULL) {
		int times = atoi((const char*) argv[3]);
		int type_run = atoi((const char*) argv[4]);
		// cout << "----" + toString(type_run) + "----" + toString(times) + "----";
		StringBuffer sendGW;
		Writer<StringBuffer> jsonS(sendGW);
		char* control = checkControl(mosq, atoi((const char*) argv[1]));
		jsonS.StartObject();
		int adr = atoi((const char*) argv[0]);
		if(toString(control).compare("CCT") == 0){
			adr ++;
		}
		jsonS.Key("ADR");
		jsonS.Int(adr);
		jsonS.Key(control);
		jsonS.Int(atoi((const char*) argv[2]));
		if(times > 0 && toString(control).compare("CCT") != 0){
			jsonS.Key("TIME");
			jsonS.Int(times);
		}
		jsonS.EndObject();

		string s = sendGW.GetString();
		cout<< s <<endl;
		char * sendT = new char[s.length()+1];
		strcpy(sendT, s.c_str());
		MqttSend(mosq, sendT);
	}
	return 0;
}

static int RULE_IR_DEVICE(void *data, int argc, char **argv, char **azColName){

	// cout << "INTO RULE IR DEVICE"<< endl;
	string DeviceId 			= toString((const char*) argv[0]);
	int DeviceAttributeId		= atoi((const char*) argv[1]);
	int DeviceAttributeValue	= atoi((const char*) argv[2]);
	// if((const char*) argv[3] != NULL) {
	// 	int DeviceAttributeValueMAX = atoi((const char*) argv[3]);
	// }
	int IrDeviceUnicastId		= atoi((const char*) argv[3]);
	// cout << IrDeviceUnicastId << endl;
	int type_run				= atoi((const char*) argv[4]);
	// int DeviceUnicastId			= atoi((const char*) argv[5]);
	// cout << "----" + toString(type_run) << endl;

	StringBuffer sendIrRuleGW;
	Writer<StringBuffer> jsonS(sendIrRuleGW);
	jsonS.StartObject();
		jsonS.Key("CMD");
		jsonS.String("IR_FAN_TV");
		jsonS.Key("TYPE");
		jsonS.String("CONTROL");
		jsonS.Key("DATA");
			jsonS.StartObject();
				// jsonS.Key("DEVICE_UNICAST_ID");
				// jsonS.Int(DeviceUnicastId);
				jsonS.Key("IR_DEVICE_UNICAST_ID");
				jsonS.Int(IrDeviceUnicastId);
				jsonS.Key("DEVICE_ATTRIBUTE_ID");
				jsonS.Int(DeviceAttributeId);
				jsonS.Key("IR_DEVICE_ATTRIBUTE_VALUE");
				jsonS.Int(DeviceAttributeValue);
			jsonS.EndObject();
	jsonS.EndObject();

	string s = sendIrRuleGW.GetString();
	cout<< s << endl;
	char * sendIrT = new char[s.length()+1];
	strcpy(sendIrT, s.c_str());
	MqttSend(mosq, sendIrT);
	return 0;
}

static int RULEGROUP(void *data, int argc, char **argv, char **azColName){

	// cout << "into Rule Group" << endl;
	int times = atoi((const char*) argv[3]);
	StringBuffer sendGW;
	Writer<StringBuffer> jsonS(sendGW);
	char* control = checkControl(mosq, atoi((const char*) argv[1]));
	jsonS.StartObject();
	int adr = atoi((const char*) argv[0]);
	jsonS.Key("ADR");
	jsonS.Int(adr);
	jsonS.Key(control);
	jsonS.Int(atoi((const char*) argv[2]));
	if(times > 0 && toString(control).compare("CCT") != 0){
		jsonS.Key("TIME");
		jsonS.Int(times);
	}
	jsonS.EndObject();

	string s = sendGW.GetString();
	cout<<s<<endl;
	char * sendT = new char[s.length()+1];
	strcpy(sendT, s.c_str());
	MqttSend(mosq, sendT);
	return 0;
}

static int RULESCENE(void *data, int argc, char **argv, char **azColName){

	StringBuffer sendGW;
	Writer<StringBuffer> jsonS(sendGW);
	jsonS.StartObject();
	int adr = atoi((const char*) argv[0]);
	int times = atoi((const char*) argv[1]);
	cout<<adr<<"vvvv"<<times<<endl;
	jsonS.Key("CALLSCENE");
	jsonS.Int(adr);
	if(times > 0){
		jsonS.Key("TIME");
		jsonS.Int(times);
	}
	else
	{
		jsonS.Key("TIME");
		jsonS.Int(0);
	}
	jsonS.EndObject();

	string s = sendGW.GetString();
	cout<<s<<endl;
	char * sendT = new char[s.length()+1];
	strcpy(sendT, s.c_str());
	MqttSend(mosq, sendT);
	return 0;
}

static int CHECK_SCENE(void *data, int argc, char **argv, char **azColName){

	int a = atoi((const char*) argv[0]);
	StringBuffer sendGW;
	Writer<StringBuffer> jsonS(sendGW);
	jsonS.StartObject();
	jsonS.Key("CALLSCENE");
	jsonS.Int(a);
	jsonS.Key("TIME");
	jsonS.Int(0);
	jsonS.EndObject();

	string s = sendGW.GetString();
	cout<<s<<endl;
	char * sendT = new char[s.length()+1];
	strcpy(sendT, s.c_str());
	MqttSend(mosq, sendT);
	return 0;
}

static int CHECK_RULE(void *data, int argc, char **argv, char **azColName){
	string a = toString((const char*) argv[0]);
	cout << "CALL EVENT: "<< a << endl;
	string DEVICE = "SELECT EventTriggerOutputDeviceSetupValue.DeviceUnicastId, EventTriggerOutputDeviceSetupValue.DeviceAttributeId, EventTriggerOutputDeviceSetupValue.DeviceAttributeValue, EventTrigger.FADE_IN, EventTriggerOutputDeviceSetupValue.typerun"
			" FROM EventTriggerOutputDeviceSetupValue INNER JOIN EventTrigger"
			" ON EventTrigger.EventTriggerId = EventTriggerOutputDeviceSetupValue.EventTriggerId"
			" WHERE EventTriggerOutputDeviceSetupValue.EventTriggerId = '"+a+"' AND EventTriggerOutputDeviceSetupValue.Time = '" + parthTime(TimerOver) + "' ORDER BY EventTriggerOutputDeviceSetupValue.DeviceAttributeId;";
	// cout << DEVICE << endl;
	DBContext(mosq, "RULEDEVICE", DEVICE);
	// cout << "RULE DEVICE "<< endl;
	string GROUPING = "SELECT EventTriggerOutputGroupingSetupValue.GroupUnicastId, EventTriggerOutputGroupingSetupValue.DeviceAttributeId, EventTriggerOutputGroupingSetupValue.DeviceAttributeValue, EventTrigger.FADE_IN, EventTriggerOutputGroupingSetupValue.typerun"
			" FROM EventTriggerOutputGroupingSetupValue INNER JOIN EventTrigger"
			" ON EventTrigger.EventTriggerId = EventTriggerOutputGroupingSetupValue.EventTriggerId"
			" WHERE EventTriggerOutputGroupingSetupValue.EventTriggerId = '"+a+"' AND EventTriggerOutputGroupingSetupValue.Time = '" + parthTime(TimerOver) + "' ORDER BY EventTriggerOutputGroupingSetupValue.DeviceAttributeId DESC;";
	DBContext(mosq, "RULEGROUP", GROUPING);
	// cout << "RULEGROUP: " << endl;
	string SCENE = "SELECT EventTriggerOutputSceneMapping.SceneUnicastID, EventTrigger.FADE_IN, EventTriggerOutputSceneMapping.typerun FROM EventTriggerOutputSceneMapping INNER JOIN EventTrigger "
			"ON EventTrigger.EventTriggerId = EventTriggerOutputSceneMapping.EventTriggerId "
			"WHERE EventTriggerOutputSceneMapping.EventTriggerId = '"+a+"' AND EventTriggerOutputSceneMapping.Time = '" + parthTime(TimerOver) + "';";
	DBContext(mosq, "RULESCENE", SCENE);
	
	string IR_DEVICE = "SELECT EventTriggerOutputDeviceSetupValue.DeviceId, EventTriggerOutputDeviceSetupValue.DeviceAttributeId, EventTriggerOutputDeviceSetupValue.DeviceAttributeValue, EventTriggerOutputDeviceSetupValue.IrDeviceUnicastId, EventTriggerOutputDeviceSetupValue.typerun"
			" FROM EventTriggerOutputDeviceSetupValue INNER JOIN EventTrigger"
			" ON EventTrigger.EventTriggerId = EventTriggerOutputDeviceSetupValue.EventTriggerId"
			" WHERE EventTriggerOutputDeviceSetupValue.EventTriggerId = '" + a + "' AND EventTriggerOutputDeviceSetupValue.Time = '" + parthTime(TimerOver) + "' AND EventTriggerOutputDeviceSetupValue.IrDeviceUnicastId IS NOT NULL ORDER BY EventTriggerOutputDeviceSetupValue.DeviceAttributeId;";
	// cout << IR_DEVICE << endl;
	DBContext(mosq, "RULE_IR_DEVICE", IR_DEVICE);
	// cout<<"Check rule finish !!!"<<endl;

	return 0;
}

static int CHECK_RULE_ID(void *data, int argc, char **argv, char **azColName){
	string EventTriggerId = toString((const char*) argv[0]);
	//string EventTriggerId = toString(sizeof(argv));
	cout << "------" +EventTriggerId +"-------"<< endl;
	int att = atoi((const char *) argv[3]);
	string sqlcheck = "SELECT Code FROM EventTriggerType INNER JOIN EventTrigger ON EventTriggerType.EventTriggerTypeId = EventTrigger.EventTriggerTypeId"
						" WHERE EventTrigger.EventTriggerId = '"+EventTriggerId+"';";
	CheckType = "";
	DBContext(mosq, "CHECKTYPE", sqlcheck);

	if(toString(CheckType).compare("RULE") == 0){
		int tpye_compare = atoi((const char *) argv[4]);
		int value = atoi((const char *) argv[5]);
		int value1 = 0;
		if(tpye_compare == 7){
			value1 = atoi((const char *) argv[6]);
		}
		cout<< "value1: "<<value << " value2: "<< value1<< " type_compare: "<<tpye_compare<< endl;
		if((tpye_compare == 1 && value == value_input) || (tpye_compare == 3 && value_input < value) ||
				(tpye_compare == 5 && value_input > value) || (tpye_compare == 7 && value_input > value && value_input < value1)){
			LOGIC_RULE_ID = 3;
			string RULE = "SELECT EventTriggerId,LogicalOperatorID FROM EventTrigger WHERE EventTriggerId = '"+EventTriggerId+"';";
			if(att == 11 || att == 12 || att == 13 || att == 14 || att == 15 || att == 16){
				HasButtonInRule = true;
			}
			cout << RULE <<endl;
			DBContext(mosq, "LOGIC_RULE", RULE);
		}
	}
	return 0;
}

static int LOGIC_RULE(void *data, int argc, char **argv, char **azColName){
	cout << "into logic rule"<< endl;
	LOGIC_RULE_ID = atoi((const char*) argv[1]);
	string RULE_ID = toString((const char*) argv[0]);
	cout<< RULE_ID<< endl;
	if(LOGIC_RULE_ID == 0){
		string DEVICE = "SELECT EventTriggerOutputDeviceSetupValue.DeviceUnicastId, EventTriggerOutputDeviceSetupValue.DeviceAttributeId, EventTriggerOutputDeviceSetupValue.DeviceAttributeValue, EventTrigger.FADE_IN, EventTriggerOutputDeviceSetupValue.typerun"
				" FROM EventTriggerOutputDeviceSetupValue INNER JOIN EventTrigger"
				" ON EventTrigger.EventTriggerId = EventTriggerOutputDeviceSetupValue.EventTriggerId"
				" WHERE EventTriggerOutputDeviceSetupValue.EventTriggerId = '"+RULE_ID+"' ORDER BY EventTriggerOutputDeviceSetupValue.DeviceAttributeId;";
		cout << DEVICE << endl;
		DBContext(mosq, "RULEDEVICE", DEVICE);
		cout << "RULE DEVICE "<< endl;
		string GROUPING = "SELECT EventTriggerOutputGroupingSetupValue.GroupUnicastId, EventTriggerOutputGroupingSetupValue.DeviceAttributeId, EventTriggerOutputGroupingSetupValue.DeviceAttributeValue, EventTrigger.FADE_IN, EventTriggerOutputGroupingSetupValue.typerun"
				" FROM EventTriggerOutputGroupingSetupValue INNER JOIN EventTrigger"
				" ON EventTrigger.EventTriggerId = EventTriggerOutputGroupingSetupValue.EventTriggerId"
				" WHERE EventTriggerOutputGroupingSetupValue.EventTriggerId = '"+RULE_ID+"' ORDER BY EventTriggerOutputGroupingSetupValue.DeviceAttributeId DESC;";
		cout << "RULEGROUP: " <<GROUPING<< endl;
		DBContext(mosq, "RULEGROUP", GROUPING);

		string SCENE = "SELECT EventTriggerOutputSceneMapping.SceneUnicastID, EventTrigger.FADE_IN, EventTriggerOutputSceneMapping.typerun FROM EventTriggerOutputSceneMapping INNER JOIN EventTrigger "
				"ON EventTrigger.EventTriggerId = EventTriggerOutputSceneMapping.EventTriggerId "
				"WHERE EventTriggerOutputSceneMapping.EventTriggerId = '"+RULE_ID+"';";
		cout << "RULESCENE: " <<SCENE<< endl;
		DBContext(mosq, "RULESCENE", SCENE);
		HasButtonInRule = false;
	}
	else if(LOGIC_RULE_ID == 1){
		string CHECK_RULE = "SELECT EventTriggerInputDeviceSetupValue.EventTriggerId, EventTriggerInputDeviceSetupValue.ComparisonOperatorId, EventTriggerInputDeviceSetupValue.DeviceAttributeValue, EventTriggerInputDeviceSetupValue.DeviceAttributeValueMAX, DeviceAttributeValue.Value"
				" FROM EventTriggerInputDeviceSetupValue INNER JOIN DeviceAttributeValue"
				" ON EventTriggerInputDeviceSetupValue.DeviceUnicastId = DeviceAttributeValue.DeviceUnicastId AND EventTriggerInputDeviceSetupValue.DeviceAttributeId = DeviceAttributeValue.DeviceAttributeId"
				" WHERE EventTriggerInputDeviceSetupValue.EventTriggerId = '" + RULE_ID + "' AND EventTriggerInputDeviceSetupValue.DeviceAttributeValue IS NOT NULL ;";
		cout << "CHECKRULE: " + CHECK_RULE << endl;
		DBContext(mosq, "RULE_INPUT_AND", CHECK_RULE);
		
		string CHECK_BUTTON_IN_RULE = "SELECT * from EventTriggerInputDeviceSetupValue INNER JOIN Device ON EventTriggerInputDeviceSetupValue.DeviceId =  EventTriggerId WHERE EventTriggerId = '" + RULE_ID + "'AND Device.CategoryId IN (23001, 23002) " + ";";
		NumberOfButtonInRuleAnd = 0;
		DBContext(mosq, "CHECK_BUTTON_IN_RULE", CHECK_BUTTON_IN_RULE);

		/*
		 * kiem tra cac dieu khien cua rule co thoa man hay khong neu tat ca thoa man thi kich hoat rule
		 */

		if(FlagCheckRuleAnd == NumberOfRuleInputAnd && NumberOfButtonInRuleAnd == 1 && HasButtonInRule == true){
			string DEVICE = "SELECT EventTriggerOutputDeviceSetupValue.DeviceUnicastId, EventTriggerOutputDeviceSetupValue.DeviceAttributeId, EventTriggerOutputDeviceSetupValue.DeviceAttributeValue, EventTrigger.FADE_IN, EventTriggerOutputDeviceSetupValue.typerun"
					" FROM EventTriggerOutputDeviceSetupValue INNER JOIN EventTrigger"
					" ON EventTrigger.EventTriggerId = EventTriggerOutputDeviceSetupValue.EventTriggerId"
					" WHERE EventTriggerOutputDeviceSetupValue.EventTriggerId = '"+RULE_ID+"' ORDER BY EventTriggerOutputDeviceSetupValue.DeviceAttributeId;";
			cout << DEVICE << endl;
			DBContext(mosq, "RULEDEVICE", DEVICE);
			cout << "RULE DEVICE "<< endl;
			string GROUPING = "SELECT EventTriggerOutputGroupingSetupValue.GroupUnicastId, EventTriggerOutputGroupingSetupValue.DeviceAttributeId, EventTriggerOutputGroupingSetupValue.DeviceAttributeValue, EventTrigger.FADE_IN, EventTriggerOutputGroupingSetupValue.typerun"
					" FROM EventTriggerOutputGroupingSetupValue INNER JOIN EventTrigger"
					" ON EventTrigger.EventTriggerId = EventTriggerOutputGroupingSetupValue.EventTriggerId"
					" WHERE EventTriggerOutputGroupingSetupValue.EventTriggerId = '"+RULE_ID+"' ORDER BY EventTriggerOutputGroupingSetupValue.DeviceAttributeId DESC;";
			cout << "RULEGROUP: " <<GROUPING<< endl;
			DBContext(mosq, "RULEGROUP", GROUPING);

			string SCENE = "SELECT EventTriggerOutputSceneMapping.SceneUnicastID, EventTrigger.FADE_IN, EventTriggerOutputSceneMapping.typerun FROM EventTriggerOutputSceneMapping INNER JOIN EventTrigger "
					"ON EventTrigger.EventTriggerId = EventTriggerOutputSceneMapping.EventTriggerId "
					"WHERE EventTriggerOutputSceneMapping.EventTriggerId = '"+RULE_ID+"';";
			cout << "RULESCENE: " <<SCENE<< endl;
			DBContext(mosq, "RULESCENE", SCENE);
			HasButtonInRule = false;
		}
		else if(FlagCheckRuleAnd == NumberOfRuleInputAnd && NumberOfButtonInRuleAnd == 0){
			string DEVICE = "SELECT EventTriggerOutputDeviceSetupValue.DeviceUnicastId, EventTriggerOutputDeviceSetupValue.DeviceAttributeId, EventTriggerOutputDeviceSetupValue.DeviceAttributeValue, EventTrigger.FADE_IN, EventTriggerOutputDeviceSetupValue.typerun"
					" FROM EventTriggerOutputDeviceSetupValue INNER JOIN EventTrigger"
					" ON EventTrigger.EventTriggerId = EventTriggerOutputDeviceSetupValue.EventTriggerId"
					" WHERE EventTriggerOutputDeviceSetupValue.EventTriggerId = '"+RULE_ID+"' ORDER BY EventTriggerOutputDeviceSetupValue.DeviceAttributeId;";
			cout << DEVICE << endl;
			DBContext(mosq, "RULEDEVICE", DEVICE);
			cout << "RULE DEVICE "<< endl;
			string GROUPING = "SELECT EventTriggerOutputGroupingSetupValue.GroupUnicastId, EventTriggerOutputGroupingSetupValue.DeviceAttributeId, EventTriggerOutputGroupingSetupValue.DeviceAttributeValue, EventTrigger.FADE_IN, EventTriggerOutputGroupingSetupValue.typerun"
					" FROM EventTriggerOutputGroupingSetupValue INNER JOIN EventTrigger"
					" ON EventTrigger.EventTriggerId = EventTriggerOutputGroupingSetupValue.EventTriggerId"
					" WHERE EventTriggerOutputGroupingSetupValue.EventTriggerId = '"+RULE_ID+"' ORDER BY EventTriggerOutputGroupingSetupValue.DeviceAttributeId DESC;";
			cout << "RULEGROUP: " <<GROUPING<< endl;
			DBContext(mosq, "RULEGROUP", GROUPING);

			string SCENE = "SELECT EventTriggerOutputSceneMapping.SceneUnicastID, EventTrigger.FADE_IN, EventTriggerOutputSceneMapping.typerun FROM EventTriggerOutputSceneMapping INNER JOIN EventTrigger "
					"ON EventTrigger.EventTriggerId = EventTriggerOutputSceneMapping.EventTriggerId "
					"WHERE EventTriggerOutputSceneMapping.EventTriggerId = '"+RULE_ID+"';";
			cout << "RULESCENE: " <<SCENE<< endl;
			DBContext(mosq, "RULESCENE", SCENE);
			HasButtonInRule = false;
		}
	}
	return 0;
}
static int CHECK_BUTTON_IN_RULE(void *data, int argc, char **argv, char **azColName){
	NumberOfButtonInRuleAnd ++;
	return 0;
}

static int RULE_INPUT_AND(void *data, int argc, char **argv, char **azColName){
	NumberOfRuleInputAnd ++;
	int type_compare = atoi((const char *) argv[1]);
	int value = atoi((const char *) argv[2]);
	int value1 = 0;
	int value2 = atoi((const char *) argv[4]);
	if(type_compare == 7){
		value1 = atoi((const char *) argv[3]);
	}
	if((type_compare == 1 && value == value2) || (type_compare == 3 && value2 < value) ||
			(type_compare == 5 && value2 > value) || (type_compare == 7 && value2 > value && value2 < value1)){
		FlagCheckRuleAnd ++;
	}
	return 0;
}

/*
 * ham duoc goi khi rule time duoc kich hoat
 */
extern bool check_countdown;
extern string event_trigger_id_countdown;

static int CallRULE(void *data, int argc, char **argv, char **azColName){
	for(int i = 0; i<argc; i++){
		string a;
		a = toString((const char*) argv[i]);

		if(a.compare("SCENE") == 0){
			ADRTIMER=-1;
			string sqlID = "SELECT SceneUnicastID FROM EventTrigger WHERE StartAt = '"+ parthTime(TimerOver) + "' AND EventTriggerTypeId = 1;";
			DBContext(mosq, "CHECK_SCENE", sqlID);

			cout<<sqlID<<endl;
		}else if(a.compare("RULE") == 0){
			cout << "CHECK COUNTDOWN -------- " << check_countdown << endl;
			string sql = "SELECT EventTriggerId FROM EventTrigger "\
					"WHERE EventTriggerId <> '" + event_trigger_id_countdown + "' AND (EventTrigger.StartAt = '" + parthTime(TimerOver) + "' OR EventTrigger.EndAt = '" + parthTime(TimerOver) + "') AND EventTriggerTypeId = 2;";
			cout<<sql<<endl;
			DBContext(mosq, "CHECK_RULE", sql);
			cout<<"Check Rule Finish"<<endl;
		}
	}
	return 0;
}

static int CallbackSQLStart(void *data, int argc, char **argv, char **azColName){
	string a;
	for(int i = 0; i<argc; i++){
		a = toString(argv[i]);
		if(!a.compare("") == 0){
			jsonS.Int(tachTimer(ToCharTimer(a)));
		}
	}
	return 0;
}

static int CallbackSQLEnd(void *data, int argc, char **argv, char **azColName){
	string a;
	for(int i = 0; i<argc; i++){
		a = toString(argv[i]);
		if(!a.compare("") == 0){
			jsonS.Int(tachTimer(ToCharTimer(a)));
		}
	}
	return 0;
}

static int CallbackSQL(void *data, int argc, char **argv, char **azColName){
	for(int i = 0; i<argc; i++){
		string a = toString((const char*) argv[i]);
		CheckType = ToCharTimer(a);
	}
	return 0;
}

static int CallbackSQLID(void *data, int argc, char **argv, char **azColName){
	for(int i = 0; i<argc; i++){
		ADRTIMER = atoi((const char*) argv[i]);
	}
	return 0;
}

int DBContext(struct mosquitto *mosq, string control, string sql) {
	sqlite3* DB;
	int exit = 0;
	do {
			exit = sqlite3_open("/root/rd.Sqlite", &DB);
		} while (exit != SQLITE_OK);
	char* messaggeError;


	if(control == "STARTAT"){
		cStartAt = "";
		jsonS.Reset(sendGW);
		sendGW.Clear();
		//add timer join Json
		jsonS.StartObject();
		jsonS.Key("STARTAT");
		jsonS.StartArray();

		while(exit = sqlite3_exec(DB, sql.c_str(), CallbackSQLStart, 0, &messaggeError)!= 0){}

		jsonS.EndArray();
		jsonS.EndObject();

		string Start = sendGW.GetString();
		cStartAt = new char[Start.length()+1];
		//cout<<Start<<endl;
		strcpy(cStartAt, Start.c_str());
	}else if(control == "ENDAT") {
		cEndAt = "";
		jsonS.Reset(sendGW);
		sendGW.Clear();
		//add timer join Json
		jsonS.StartObject();
		jsonS.Key("ENDAT");
		jsonS.StartArray();

		while(exit =sqlite3_exec(DB, sql.c_str(), CallbackSQLEnd, 0, &messaggeError)!=0){}

		jsonS.EndArray();
		jsonS.EndObject();

		string End = sendGW.GetString();
		cEndAt = new char[End.length()+1];
		strcpy(cEndAt, End.c_str());
	}else if(control == "CHECKTYPE") {
		while(exit =sqlite3_exec(DB, sql.c_str(), CallbackSQL, 0, &messaggeError)!=0 ){}
	}else if(control == "ADR") {
		while(exit =sqlite3_exec(DB, sql.c_str(), CallbackSQLID, 0, &messaggeError)!=0 ){}
	}else if(control == "CALLRULE") {
		while((exit = sqlite3_exec(DB, sql.c_str(), CallRULE, 0, &messaggeError))!=0 ){}
	}else if(control == "CHECK_SCENE") {
		while((exit =sqlite3_exec(DB, sql.c_str(), CHECK_SCENE, 0, &messaggeError))!=0 ){}
	}else if(control == "CHECK_RULE") {
		while((exit =sqlite3_exec(DB, sql.c_str(), CHECK_RULE, 0, &messaggeError))!=0 ){}
	}else if(control == "RULEDEVICE") {
		// cout<< "chuan bi vao rule device"<<endl;
		while((exit = sqlite3_exec(DB, sql.c_str(), RULEDEVICE, 0, &messaggeError))!=0 ){}
	}else if(control == "RULE_IR_DEVICE") {
		// cout<< "Chuan bi vao rule IR device"<<endl;
		while((exit = sqlite3_exec(DB, sql.c_str(), RULE_IR_DEVICE, 0, &messaggeError))!=0 ){}
	}else if(control == "RULEGROUP") {
		while(exit = sqlite3_exec(DB, sql.c_str(), RULEGROUP, 0, &messaggeError)!=0 ){}
	}else if(control == "RULESCENE") {
		while(exit = sqlite3_exec(DB, sql.c_str(), RULESCENE, 0, &messaggeError)!=0 ){}
	}
//	else if (control == "LUXPIR") {
//		while(exit =sqlite3_exec(DB, sql.c_str(), LUXPIR, 0, &messaggeError)!=0 ){}
//	}
	else if (control == "CHECK_RULE_ID") {
		while(exit =sqlite3_exec(DB, sql.c_str(), CHECK_RULE_ID, 0, &messaggeError)!=0 ){}
	}else if (control == "LOGIC_RULE") {
		while(exit =sqlite3_exec(DB, sql.c_str(), LOGIC_RULE, 0, &messaggeError)!=0 ){}
	}else if (control == "RULE_INPUT_AND") {
		while(exit =sqlite3_exec(DB, sql.c_str(), RULE_INPUT_AND, 0, &messaggeError)!=0 ){}
	}else if (control == "CHECK_BUTTON_IN_RULE") {
		while(exit =sqlite3_exec(DB, sql.c_str(), CHECK_BUTTON_IN_RULE, 0, &messaggeError)!=0 ){}
	}


	if (exit != SQLITE_OK) {
		sqlite3_free(messaggeError);
	}
	else
		sqlite3_close(DB);

	return (0);
}


//---------------------------------------------CALL EVENT------------------------------------------

pthread_t threadTimer = pthread_self();
int Timer_AHG(struct mosquitto *mosq, char * jobj){ // @suppress("No return")
	cout<<"RESET"<<endl;
	sleep(1);
	pthread_cancel(threadTimer);
	pthread_create(&threadTimer, NULL, CallEvent, NULL);

	return 0;
}

int Event(struct mosquitto *mosq, char * jobj){ // @suppress("No return")
	Document document;
	document.Parse(jobj);

	if(document.HasMember("CMD")){
		string cmd = document["CMD"].GetString();
		if (cmd.compare("REMOTE") == 0) {
			UNICAST = 0;
			const Value& DATA = document["DATA"];
			UNICAST = DATA["DEVICE_UNICAST_ID"].GetInt();
			string BUTTONID = DATA["BUTTON_VALUE"].GetString();
			value_input = DATA["MODE_VALUE"].GetInt();
	//		int SRGBID = document["SRGBID"].GetInt();
			int att = checkTypeAtt(mosq, BUTTONID);
			string sql = "SELECT * FROM EventTriggerInputDeviceSetupValue WHERE DeviceUnicastId = "+toString(UNICAST)+" AND DeviceAttributeId = "+toString(att)+";";
			DBContext(mosq, "CHECK_RULE_ID", sql);
		}
		if(cmd.compare("LIGHT_SENSOR")==0){
			const Value& DATA = document["DATA"];
			UNICAST = 0;
			UNICAST = DATA["DEVICE_UNICAST_ID"].GetInt();
			value_input = DATA["LUX_VALUE"].GetInt();
			string CHECK_EVENT = "SELECT * FROM EventTriggerInputDeviceSetupValue WHERE DeviceUnicastId = "+toString(UNICAST)+" AND DeviceAttributeId = 9;";
			DBContext(mosq, "CHECK_RULE_ID", CHECK_EVENT);
		}

		if(cmd.compare("DOOR_SENSOR")==0){
			const Value& DATA = document["DATA"];
			UNICAST = 0;
			UNICAST = DATA["DEVICE_UNICAST_ID"].GetInt();
			value_input = DATA["DOOR_VALUE"].GetInt();
			string CHECK_EVENT = "SELECT * FROM EventTriggerInputDeviceSetupValue WHERE DeviceUnicastId = "+toString(UNICAST)+" AND DeviceAttributeId = 0;";
			DBContext(mosq, "CHECK_RULE_ID", CHECK_EVENT);
		}

		if(cmd.compare("SMOKE_SENSOR")==0){
			const Value& DATA = document["DATA"];
			UNICAST = 0;
			UNICAST = DATA["DEVICE_UNICAST_ID"].GetInt();
			value_input = DATA["SMOKE_VALUE"].GetInt();
			string CHECK_EVENT = "SELECT * FROM EventTriggerInputDeviceSetupValue WHERE DeviceUnicastId = "+toString(UNICAST)+" AND DeviceAttributeId = 0;";
			DBContext(mosq, "CHECK_RULE_ID", CHECK_EVENT);
		}

		if(cmd.compare("POWER_STATUS")==0){
			const Value& DATA = document["DATA"];
			UNICAST = 0;
			UNICAST = DATA["DEVICE_UNICAST_ID"].GetInt();
			value_input = DATA["POWER"].GetInt();
			string CHECK_EVENT = "SELECT * FROM EventTriggerInputDeviceSetupValue WHERE DeviceUnicastId = "+toString(UNICAST)+" AND DeviceAttributeId = 8;";
			DBContext(mosq, "CHECK_RULE_ID", CHECK_EVENT);
		}

		if(cmd.compare("TEMPERATURE_HUMIDITY")==0){
			const Value& DATA = document["DATA"];
			UNICAST = 0;
			UNICAST = DATA["DEVICE_UNICAST_ID"].GetInt();
			value_input = DATA["TEMPERATURE_VALUE"].GetInt();
			string CHECK_EVENT = "SELECT * FROM EventTriggerInputDeviceSetupValue WHERE DeviceUnicastId = "+toString(UNICAST)+" AND DeviceAttributeId = 21 OR DeviceAttributeId = 22 LIMIT 1;";
			DBContext(mosq, "CHECK_RULE_ID", CHECK_EVENT);
		}

//		if(cmd.compare("PM_SENSOR")==0){
//			const Value& DATA = document["DATA"];
//			UNICAST = 0;
//			UNICAST = DATA["DEVICE_UNICAST_ID"].GetInt();
//			int value_input = DATA["PM_VALUE"].GetInt();
//			string CHECK_EVENT = "SELECT * FROM EventTriggerInputDeviceSetupValue WHERE DeviceUnicastId = "+toString(UNICAST)+" AND DeviceAttributeId = 22;";
//			DBContext(mosq, "CHECK_RULE_ID", CHECK_EVENT);
//		}
	return 0;
	}
}


// extern bool check_countdown;
// extern string event_trigger_id_countdown;

void* CallEvent(void *argv){
	cout<<"Bắt đầu !"<<endl;
	sleep(1);
	while(true){
		//set Time Now
		TimerOver = 0;
		weekDayss = setDayTimer();

		string sqlStart = "SELECT StartAt FROM EventTrigger WHERE LogicalOperatorID = -1;";
		DBContext(mosq, "STARTAT", sqlStart);
		string sqlEnd = "SELECT EndAt FROM EventTrigger WHERE LogicalOperatorID = -1;";
		DBContext(mosq, "ENDAT", sqlEnd);

		//Add luồng Start và End vào arr
		readJson(cStartAt);
		readJson(cEndAt);

		XoaCacPhanTuTrungNhau(arrStart,lengtStart);
		XoaCacPhanTuTrungNhau(arrEnd,lengtEnd);
		int lengtArr = lengtStart + lengtEnd;
		gopArr(arrStart, arrEnd, lengtStart, lengtEnd);

		TimerOver = setTimer();

		// cout << lengtArr << endl << TimerOver << endl << arr[lengtArr - 1] << endl;

		if(lengtArr > 0 && TimerOver < arr[lengtArr - 1]){
			TimerOver = setTimer();
			cout<<"Today:  "<< weekDayss<<endl;
			// cout<<"Mảng có :" << lengtArr << endl;
			// sleep(1);
			for(int i = 0; i< lengtArr; i++){
				TimerOver = setTimer();
				if(TimerOver <= arr[i]){
					while (TimerOver < arr[i]){
						cout << "Countdown : " << arr[i] - TimerOver <<"s" << endl;
						sleep(1);
						TimerOver = setTimer();
						// cout <<"Thay doi : "<< thayDoi <<endl;
						if(thayDoi == 1){
							thayDoi = 0;
							//pthread_cancel(tmp_thread);
							//return NULL;
						}
					}
					TimerOver = arr[i];
					string sql = "SELECT EventTriggerType.code FROM EventTriggerType INNER JOIN EventTrigger "\
						"ON EventTriggerType.EventTriggerTypeId = EventTrigger.EventTriggerTypeId "\
						"WHERE EventTrigger.StartAt = '" + parthTime(arr[i]) + "' OR EventTrigger.EndAt = '" + parthTime(arr[i]) + "';";
					// cout << sql << endl;
					DBContext(mosq, "CALLRULE", sql);				
				}
			}
		}
		else if(lengtArr > 0 && TimerOver > arr[lengtArr - 1]){
			while(TimerOver > arr[lengtArr - 1]){
				sleep(1);
			}
		}
		sleep(2);
	}
	return NULL;
}

int tachTimer(char* a){
	int dem = 0;
	char h[23] = {0};
	char m[23] = {0};

	int timer;

	for(int i = 0; i < (int)strlen(a); i++){
		if(dem == 0){
			for(int j =0; j < (int)strlen(a); j++){
				if(a[j] == ':'){
					dem ++;
					i = j;
					break;
				}else{
					h[j] = a[j];
				}
			}
		}else if(dem == 1){
			for(int k = 0; k < (int)strlen(a); k++){
				if(a[k+i] == '\0'){
					i = strlen(a);
					break;
				}else{
					m[k] = a[k + i];
				}
			}
		}
	}

	timer = atoi(h)* 3600 + atoi(m)* 60;

	return timer;
}

string parthTime(int a){
	int h = a/3600;
	int m = (a%3600)/60;
	string timerCheck = toString(h) + ":" + toString(m);

	return timerCheck;
}

void sapXepArr(int arr[], int lengt){
	for (int i = 0; i < lengt; i++) {
		for (int j = i + 1; j < lengt; j++) {
			if (arr[i] > arr[j]) {
				// Nếu arr[i] > arr[j] thì hoán đổi giá trị của arr[i] và arr[j]
				int temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
}

void readJson(char* s){
	Document document;
	document.Parse(s);
	if(document.HasMember("STARTAT")){
		const Value& data = document["STARTAT"];
		if(lengtStart > 0){
			delete[] arrStart;
		}
		lengtStart = data.Size();
		arrStart = new int[data.Size()];
		for (rapidjson::SizeType i = 0; i < data.Size(); i++){
			arrStart[i] = data[i].GetInt();
		}
		sapXepArr(arrStart, data.Size());
	}
	else if(document.HasMember("ENDAT")){
		const Value& data = document["ENDAT"];
		delete[] arrEnd;
		lengtEnd = data.Size();
		arrEnd = new int[data.Size()];
		for (rapidjson::SizeType i = 0; i < data.Size(); i++){
			arrEnd[i] = data[i].GetInt();
		}
		sapXepArr(arrEnd, data.Size());
	}
}

void gopArr(int arrS[], int arrE[], int n, int m){
	arr = new int[n + m];
	for(int i = 0; i < (n + m); i++){
		if(i < n){
			arr[i] = arrS[i];
		}else {
			arr[i] = arrE[i-n];
		}
	}
	sapXepArr(arr, n + m);
}

int setTimer(){
	int timeNow;
	time_t now = time(0);
	tm *ltm = localtime(&now);
	//gán biến
	int h = ltm->tm_hour;
	int m = ltm->tm_min;
	int s = 1 + ltm->tm_sec;
	//setup Time
	if(m == 60){
		h ++;
		m = m - 60;
	}else if( s == 60 ){
		m ++;
		s = s - 60;
	}
	timeNow = h * 3600 + m * 60 + s;
	return timeNow;
}


string setDayTimer(){
	string weekDays;

	time_t now = time(0);
	tm *ltm = localtime(&now);

	int w = 1 + ltm->tm_wday;
	//Day in Week
	switch(w){
		case 1:
			weekDays = "Sunday";
			break;
		case 2:
			weekDays = "Monday";
			break;
		case 3:
			weekDays = "Tuesday";
			break;
		case 4:
			weekDays = "Wednesday";
			break;
		case 5:
			weekDays = "Thursday";
			break;
		case 6:
			weekDays = "Friday";
			break;
		case 7:
			weekDays = "Saturday";
			break;
		default:
			break;
	}
	return weekDays;
}

void Xoa1PhanTu(int a[], int &n, int ViTriXoa){
    for(int i = ViTriXoa; i < n; i++){
        a[i] = a[i + 1];
    }
    n--;
}

void XoaCacPhanTuTrungNhau(int a[], int &n)
{
    for(int i = 0; i < n; i++){
        for(int j = i + 1; j < n; j++){
            if(a[i] == a[j]){
                Xoa1PhanTu(a, n, j);
                j--;
            }
        }
    }
}

char* checkControlTimer(struct mosquitto *mosq, int idControl){
	string sql = "SELECT Code FROM DeviceAttribute WHERE DeviceAttributeId = " + toString(idControl) +";";
	DBContext(mosq, "CHECKTYPE", sql);
	string a = toString(CheckType);
	char * control = new char[a.length()+1];
	strcpy(control, a.c_str());

	return control;
}

int checkTypeAtt(struct mosquitto *mosq, string Code){
	int typeId;
	ADRTIMER = -1;
	string sql = "select DeviceAttributeID from DeviceAttribute where Code ='"+Code+"';";
	DBContext(mosq, "ADR", sql);
	typeId = ADRTIMER;
	return typeId;
}
