#include "../RD/ShareData.hpp"

int timeAt = 0;
string groupID;
int groupIdAHG = 0;
int deviceAddGroup[100] = {0};
int adrRsp[100] = {0};
int numDeviceAddGroup = 0;
bool isAddGroup = false;


bool isDelGroup = false;
int numDeviceDelGroup = 0;

string sceneString;
int deviceAddScene[100] = {0};
int numDeviceAddScene = 0;
int numDeviceDelScene = 0;
bool isAddScene = false;
bool isDelScene = false;

int indexRsp = 0;

void ResetDataGroup(){
	isAddGroup = false;
	isDelGroup = false;
	for(int i=0;i<100;i++){
		deviceAddGroup[i] = 0;
	}
	timeAt = 0;
	groupID = "";
	numDeviceAddGroup = 0;
	numDeviceDelGroup = 0;
}
void ResetDataScene(){
	isAddScene = false;
	isDelScene = false;
	timeAt = 0;
	sceneString = "";
	numDeviceAddScene = 0;
	numDeviceDelScene = 0;
}
