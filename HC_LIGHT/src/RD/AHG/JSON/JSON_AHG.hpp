/*
 * JSON_PARSE.hpp
 *
 *  Created on: Apr 10, 2021
 *      Author: trthang
 */

#ifndef RD_JSON_JSON_HPP_
#define RD_JSON_JSON_HPP_

#include "../../../RD/ShareData.hpp"

using namespace std;
using namespace rapidjson;

extern uint8_t transition;
extern uint16_t numScene;
extern uint8_t numDeviceLastScene;



char* ToChar(string s) ;
void* AHG_MQTT(void *argv);

/*-----------------------------------------------APP---------------------------------------------------------*/

//Parse Json APP
int JsonParseApp(struct mosquitto *mosq, char * jobj);

//Device
void Device(struct mosquitto *mosq, char* jobj);

//Delete Device
void DelDevice(struct mosquitto *mosq, char* jobj);

//Group
void Group(struct mosquitto *mosq, char* jobj);
	//Create Group + Device
	void CreateGroup(struct mosquitto *mosq, char* jobj);
	//Add Device
	void AddDeviceGroup(struct mosquitto *mosq, char* jobj);
	//Delete Device
	void DelDeviceGroup(struct mosquitto *mosq, char* jobj);
	//Delete Group
	void DelGroup(struct mosquitto *mosq, char* jobj);
	//Control Group
	void ControlGroup(struct mosquitto *mosq, char* jobj);

//Call Scene
void CallEventTrigger(struct mosquitto *mosq, char* jobj);

//EventTrigger
void EventTrigger(struct mosquitto *mosq, char* jobj);
	//Create Scene default
	void Create_Default_Scenes(struct mosquitto *mosq, char* jobj);
	//Create EventTrigger Scene
	void CreateScene(struct mosquitto *mosq, char* jobj);
	//Create EventTrigger Scene
	void EditScene(struct mosquitto *mosq, char* jobj);
	//Delete EventTrigger Scene
	void DelScene(struct mosquitto *mosq, char* jobj);

	//Create EventTrigger Rule
	void CreateRule(struct mosquitto *mosq, char* jobj);
		//rule for time
		void CreateRuleOutPut(struct mosquitto *mosq, char* jobj, string EVENT_TRIGGER_ID, string START_AT, string END_AT);
		//rule for input or
		void CreateRuleInput(struct mosquitto *mosq, char* jobj, string EVENT_TRIGGER_ID);
	//Create EventTrigger Rule
	void EditRule(struct mosquitto *mosq, char* jobj);
	//Delete EventTrigger Rule
	void DelRule(struct mosquitto *mosq, char* jobj);

//EventTriggerOutput
void EventOutput(struct mosquitto *mosq, char* jobj);
	//ADD
	void AddEventTriggerOuput(struct mosquitto *mosq, char* jobj);
	//DELETE
	void DeleteEventTriggerOuput(struct mosquitto *mosq, char* jobj);

//Scan/Stop
void ScanStop(struct mosquitto *mosq, char* jobj);

//EventTrigger InputSensor
void InputSensor(struct mosquitto *mosq, char* jobj);
	//Create
	void CreateSensor(struct mosquitto *mosq, char* jobj);
	//Delete
	void DelSensor(struct mosquitto *mosq, char* jobj);
//EventTrigger InputRemote
void InputRemote(struct mosquitto *mosq, char* jobj);
	//Create
	void CreateRemote(struct mosquitto *mosq, char* jobj);
	//Delete
	void DelRemote(struct mosquitto *mosq, char* jobj);

//EventTrigger InputSensor
void InputDoorSensor(struct mosquitto *mosq, char* jobj);
	//Create
	void CreateDoorSensor(struct mosquitto *mosq, char* jobj);
	//Delete
	void DelDoorSensor(struct mosquitto *mosq, char* jobj);

void InputIr(struct mosquitto *mosq, char* jobj);
	//Create
	void IrLearn(struct mosquitto *mosq, char* jobj);
	//Delete
	void IrDelete(struct mosquitto *mosq, char* jobj);
	void IrControl(struct mosquitto *mosq, char* jobj);

void InputAirConditionScan(struct mosquitto *mosq, char* jobj);
	//Scan
	void IrAirConditionerScan(struct mosquitto *mosq, char* jobj);

void CheckCountDown(struct mosquitto *mosq, char* jobj);


/*-----------------------------------------------GW---------------------------------------------------------*/



/*-----------------------------------------------DATABASE---------------------------------------------------------*/

int DBJSON(struct mosquitto *mosq,string control, string sql);

int DBCHECK(struct mosquitto *mosq,string control, string sql);

int DBSQL(struct mosquitto *mosq, string sql);

int DBSQLJSON(struct mosquitto *mosq, string sql);

/*-----------------------------------------------#---------------------------------------------------------*/

int createGroupId(struct mosquitto *mosq);

int createSceneId(struct mosquitto *mosq);

char* checkControl(struct mosquitto *mosq, int idControl);

char* checkControlEvent(struct mosquitto *mosq, int idControl);

int checkDeviceAttribute(struct mosquitto *mosq, string Code);

int SCENE_UNICAST_ID(string SCENE_ID);

int GROUP_UNICAST_ID(string GROUP_ID);

int DEVICE_UNICAST_ID(string DEVICE_ID);

int TYPE_DEVICE(string DEVICE_ID);


#endif /* RD_JSON_JSON_HPP_ */
