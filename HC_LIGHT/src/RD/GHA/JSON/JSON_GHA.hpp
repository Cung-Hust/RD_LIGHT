/*
 * JSON_GHA.hpp
 *
 *  Created on: Apr 10, 2021
 *      Author: trthang
 */

#ifndef RD_JSON_JSON_GHA_HPP_
#define RD_JSON_JSON_GHA_HPP_

#include "../../../RD/ShareData.hpp"

using namespace std;
using namespace rapidjson;



void* GHA_MQTT(void *argv);

/*-----------------------------------------------GW-------------------------------------------------------------*/
void checkTimeoutAddGroup(string groupId);
void checkTimeoutDelGroup(string groupId);
void checkTimeoutAddScene(string eventtrigger);

int JsonParseGw(struct mosquitto *mosq, char * jobj);

void AdrGwToApp(struct mosquitto *mosq, char* jobj);

void TYPEDEVICE(struct mosquitto *mosq, char* jobj);

char* checkControlCode(struct mosquitto *mosq, int idControl);

string getGUID(struct mosquitto *mosq, int adr);

int getUnicast(struct mosquitto *mosq, string control);

int checkType(struct mosquitto *mosq, string Code);

int setDay();
int setTime();

string getGUID(struct mosquitto *mosq, int adr);

int getUnicast(struct mosquitto *mosq, string control);

//#
void ONOFF(struct mosquitto *mosq, char* jobj);
void CCT(struct mosquitto *mosq, char* jobj);
void DIM(struct mosquitto *mosq, char* jobj);
void HSL(struct mosquitto *mosq, char* jobj);
void ADDGROUP(struct mosquitto *mosq, char* jobj);
void DELGROUP(struct mosquitto *mosq, char* jobj);
void AddScene(struct mosquitto* mosq, char *jobj);
void CALLSCENE(struct mosquitto *mosq, char* jobj);
void ADDSCENE(struct mosquitto *mosq, char* jobj);
void DELSCENE(struct mosquitto *mosq, char* jobj);
void LUX(struct mosquitto *mosq, char* jobj);
void PIR(struct mosquitto *mosq, char* jobj);
void POWER(struct mosquitto *mosq, char* jobj);
void REMOTE_STATUS(struct mosquitto *mosq, char * jobj);
void SMOKE_STATUS(struct mosquitto* mosq, char * jobj);
void DOOR_STATUS(struct mosquitto* mosq, char * jobj);
void PM_STATUS(struct mosquitto* mosq, char * jobj);
void TEMP_HUM(struct mosquitto* mosq, char * jobj);
void RESETNODE(struct mosquitto *mosq, char* jobj);
void SetSceneRemote(struct mosquitto *mosq, char* jobj);
void DELSCENEFORREMOTE(struct mosquitto *mosq, char* jobj);

void SETSCENE_LIGHT_PIR(struct mosquitto *mosq, char* jobj);
void DELSCENE_LIGHT_PIR(struct mosquitto *mosq, char* jobj);

#endif /* RD_JSON_JSON_GHA_HPP_ */
