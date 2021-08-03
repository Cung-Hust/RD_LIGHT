#ifndef SHAREDATA_HPP_
#define SHAREDATA_HPP_

#include <queue>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <sqlite3.h>
#include <string>
#include <mosquitto.h>
#include <iostream>
#include <sstream>
#include <pthread.h>
#include <ctime>

#include "rapidjson/document.h"
#include "rapidjson/prettywriter.h"

using namespace std;
using namespace rapidjson;

extern string groupID;
extern int groupIdAHG;
extern bool isDelGroup ;
extern int numDeviceDelGroup ;

extern int deviceAddGroup[100];

extern int numDeviceAddGroup;
extern bool isAddGroup;

extern int timeAt;
extern int adrRsp[100];
extern string sceneString;
extern int deviceAddScene[100];
extern int numDeviceAddScene;
extern int numDeviceDelScene;
extern bool isAddScene;
extern bool isDelScene;

extern int indexRsp;

void ResetDataGroup();
void ResetDataScene();

#endif
