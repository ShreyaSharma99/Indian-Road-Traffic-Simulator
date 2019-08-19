#include <bits/stdc++.h> 
#include <string> 
#include<fstream>
using namespace std;



int findLaneNumber(int index, int** laneCarIndex, int lanes){
	
	int i=0;


	for(i=0; i< lanes; i++){
		
		int j=0;
		
		for(; j<10; j++){
			
			if(laneCarIndex[i][j] == index) break;
			
		}
		
		if(laneCarIndex[i][j] == index) break;
			
	}
	if(i==lanes) {cout<< "The Vehicle is not present anywhere"; return -1;}
	
	return i;
	
}

int findLaneIndex(int index, int** laneCarIndex, int lanes){
	
	
	int i=0;
	int j =0;
	for(i=0; i< lanes; i++){
		
		for(j=0; j<10; j++){

			if(laneCarIndex[i][j] == index) break;
			
		}
		//cout<<laneCarIndex[i][j]<<endl;
		if(j<10) {if(laneCarIndex[i][j] == index) break;}
	}
	 
	if(j==10) {cout<< "The Vehicle is not present anywhere"; return -1;}
	
	return j;
	
}

int findIndexOfStr(string* Vehicle, string VehicleInside, int len){
		
		int i=0;
		
		for(; i<len; i++){
			
			string tempVeh = Vehicle[i];
		   // cout<<tempVeh<<endl;
			if(strcmp(VehicleInside.c_str(), tempVeh.c_str())==0) break;
		
		}
		
		if(i==len) {
			//cout<< "Vehicle "<< VehicleInside <<endl;;
		//	cerr << "Invalid Call" << '\n';  
			return -1;
			
		}
		
		return i;
	}


int topLeftX(int posX, int posY, string* Vehicle, string VehicleInside, int len, string* Vehicle_Length){
		
		int index = findIndexOfStr(Vehicle,VehicleInside,len);
		
		
		return (posX - atoi(Vehicle_Length[index].c_str()) +1);
		
	}


// COMMENT: position of the top left point
int topLeftY(int posX, int posY,  string* Vehicle, string VehicleInside, int len,string* Vehicle_Width){
	
		int index = findIndexOfStr(Vehicle,VehicleInside,len);
		
		
		return (posY - atoi(Vehicle_Width[index].c_str()) +1);
		
		
	}



bool aboutToCollide(int** laneCarIndex, int index, int carLaneNumber, int carLaneIndex, int* Vf, int* A, int* PosX, int* PosY, int len, string* Vehicle, string* VehicleInside, string* Vehicle_Length){

	
	
	if(carLaneIndex==0) return false;
	else{
		
		int topLeft = topLeftX(PosX[(laneCarIndex[carLaneNumber][carLaneIndex-1])], PosY[(laneCarIndex[carLaneNumber][carLaneIndex-1])], Vehicle, VehicleInside[(laneCarIndex[carLaneNumber][carLaneIndex-1])], len, Vehicle_Length);
		
	  	if((topLeft - PosX[index]) <=1){
			
			if((Vf[(laneCarIndex[carLaneNumber][carLaneIndex-1])]) >= (Vf[(laneCarIndex[carLaneNumber][carLaneIndex])]))  return false;
				else return true;
			
		}
		
		else{
			
			return false;
		}
	}
		
	
}

int smallestAhead(int P, int pos, int* PosX, int** laneCarIndex){
	
	int j = 0;
	
	for(; j<10; j++){
		
		if(laneCarIndex[P][j]==0) break;	
		else{
			
			if(PosX[(laneCarIndex[P][j])] <= pos) continue;
			else break;
		}
		
	}
	
	if((j==10) || (laneCarIndex[P][j]==0)) return -1; 	// Means that there is no one ahead of the car here!
	else return PosX[(laneCarIndex[P][j])];
}


int largestBehind(int P, int pos, int* PosX, int** laneCarIndex){
	
	int j = 0;
	
	for(; j<10; j++){
		
		if(laneCarIndex[P][j]==0) break;	
		else{
			
			if(PosX[(laneCarIndex[P][j])] > pos) continue;
			else break;
		}
		
	}
	
	if((j==10) || (laneCarIndex[P][j]==0)) return -1; 	// Means that there is no one ahead of the car here!
	else return j;
}


int isAnyNearby0(int P, int pos, int* PosX, int** laneCarIndex, int Road_Length, string* VehicleInside, int index, string* Vehicle, string* Vehicle_Length, int len){
	
	int temp = 0;	// 0 means that there is Empty space. So NO for nearby!
	
	int SmallestAhead = smallestAhead(P,pos,PosX, laneCarIndex);
	int LargestBehind = largestBehind(P,pos,PosX, laneCarIndex);
	
	int ans[2];   // 0 for Vehicle Index to be constrained; 1 for the constrain
	
	if((SmallestAhead==-1) && (LargestBehind==-1)) 
	{
		ans[1] = -1;	// The whole road is Empty. Easy to overtake.
		ans[0] = -1;	// No Vehicle to be constrained
		
		return ans[0];
	}	
	else if(LargestBehind==-1){		// There is no one behind this Vehicle
		
		int vehSize = atoi(Vehicle_Length[findIndexOfStr(Vehicle,VehicleInside[(laneCarIndex[P][SmallestAhead])],len)].c_str());

		if(PosX[(laneCarIndex[P][SmallestAhead])] - pos <= vehSize) {
			
			ans[1] = 1; 	//There is no space in this lane
			ans[0] = -1; 	// No use of constraint

			return ans[0];
		}
		else {
			
			ans[0] = -1;	// Still no constraints since there is no Vehicle behind it
			ans[1] = 0;		// Overtake but with constraints 
			
			return ans[0];
		}
		
	}
	
	else if(SmallestAhead==-1){		// There is no one Ahead this Vehicle
		
		int vehSize = atoi(Vehicle_Length[findIndexOfStr(Vehicle,VehicleInside[index],len)].c_str());

		if(-PosX[(laneCarIndex[P][LargestBehind])] + pos <= vehSize + max(5,Road_Length/10)) { 	
		
			ans[1] = 1;	//There is no space in this lane ('5' is randomly deffined.)
			ans[0] = -1; 	// No use of constraint

			return ans[0];
			
		}
		else {

			ans[0] = laneCarIndex[P][LargestBehind];	// The Vehicle Behind it will now be constrained
			ans[1] = 0;		// Overtake but with constraints 
			
			return ans[0];
	
			
			
		}
		
	}
	
	else{		// There is a vehicle ahead as well as a Vehicle Behind.
		
		int vehSize = atoi(Vehicle_Length[findIndexOfStr(Vehicle,VehicleInside[index],len)].c_str());
		int vehSize1 = atoi(Vehicle_Length[findIndexOfStr(Vehicle,VehicleInside[(laneCarIndex[P][SmallestAhead])],len)].c_str());

		
		if((-PosX[(laneCarIndex[P][LargestBehind])] + pos <= vehSize + max(5,Road_Length/10)) || (PosX[(laneCarIndex[P][SmallestAhead])] - pos <= vehSize1)){
			
			ans[1] = 1;	//There is no space in this lane ('5' is randomly deffined.)
			ans[0] = -1; 	// No use of constraint

			return ans[0];
			
			
		}
		
		else{
			
			ans[0] = laneCarIndex[P][LargestBehind];	// The Vehicle Behind it will now be constrained
			ans[1] = 0;		// Overtake but with constraints 
			
			return ans[0];
	
			
		}
		
	}
	
}

int isAnyNearby1(int P, int pos, int* PosX, int** laneCarIndex, int Road_Length, string* VehicleInside, int index, string* Vehicle, string* Vehicle_Length, int len){
	
	int temp = 0;	// 0 means that there is Empty space. So NO for nearby!
	
	int SmallestAhead = smallestAhead(P,pos,PosX, laneCarIndex);
	int LargestBehind = largestBehind(P,pos,PosX, laneCarIndex);
	
	int ans[2];   // 0 for Vehicle Index to be constrained; 1 for the constrain
	
	if((SmallestAhead==-1) && (LargestBehind==-1)) 
	{
		ans[1] = -1;	// The whole road is Empty. Easy to overtake.
		ans[0] = -1;	// No Vehicle to be constrained
		
		return ans[1];
	}	
	else if(LargestBehind==-1){		// There is no one behind this Vehicle
		
		int vehSize = atoi(Vehicle_Length[findIndexOfStr(Vehicle,VehicleInside[(laneCarIndex[P][SmallestAhead])],len)].c_str());

		if(PosX[(laneCarIndex[P][SmallestAhead])] - pos <= vehSize) {
			
			ans[1] = 1; 	//There is no space in this lane
			ans[0] = -1; 	// No use of constraint

			return ans[1];
		}
		else {
			
			ans[0] = -1;	// Still no constraints since there is no Vehicle behind it
			ans[1] = 0;		// Overtake but with constraints 
			
			return ans[1];
		}
		
	}
	
	else if(SmallestAhead==-1){		// There is no one Ahead this Vehicle
		
		int vehSize = atoi(Vehicle_Length[findIndexOfStr(Vehicle,VehicleInside[index],len)].c_str());

		if(-PosX[(laneCarIndex[P][LargestBehind])] + pos <= vehSize + max(5,Road_Length/10)) { 	
		
			ans[1] = 1;	//There is no space in this lane ('5' is randomly deffined.)
			ans[0] = -1; 	// No use of constraint

			return ans[1];
			
		}
		else {

			ans[0] = laneCarIndex[P][LargestBehind];	// The Vehicle Behind it will now be constrained
			ans[1] = 0;		// Overtake but with constraints 
			
			return ans[1];
	
			
			
		}
		
	}
	
	else{		// There is a vehicle ahead as well as a Vehicle Behind.
		
		int vehSize = atoi(Vehicle_Length[findIndexOfStr(Vehicle,VehicleInside[index],len)].c_str());
		int vehSize1 = atoi(Vehicle_Length[findIndexOfStr(Vehicle,VehicleInside[(laneCarIndex[P][SmallestAhead])],len)].c_str());

		
		if((-PosX[(laneCarIndex[P][LargestBehind])] + pos <= vehSize + max(5,Road_Length/10)) || (PosX[(laneCarIndex[P][SmallestAhead])] - pos <= vehSize1)){
			
			ans[1] = 1;	//There is no space in this lane ('5' is randomly deffined.)
			ans[0] = -1; 	// No use of constraint

			return ans[1];
			
			
		}
		
		else{
			
			ans[0] = laneCarIndex[P][LargestBehind];	// The Vehicle Behind it will now be constrained
			ans[1] = 0;		// Overtake but with constraints 
			
			return ans[1];
	
			
		}
		
	}
	
}



int findEmptyNeighbour0(int** laneCarIndex, int carLaneNumber, int lanes, int index, int* PosX, int Road_Length, string* VehicleInside, string* Vehicle, string* Vehicle_Length, int len){
	
	int P1,P2 = -1;
	int ans[3];	// 0 -> LaneNumber, 1 -> Vehicle to be constrained, 2 -> Constraint level
	
	if(carLaneNumber==0) {
		
		P2 =1;
		int pos1 = PosX[index];
		
		int temp0 =  isAnyNearby0(P2, pos1, PosX, laneCarIndex, Road_Length, VehicleInside, index, Vehicle, Vehicle_Length, len);
		int temp1 =  isAnyNearby1(P2, pos1, PosX, laneCarIndex, Road_Length, VehicleInside, index, Vehicle, Vehicle_Length, len);
	    ans[0] = P2;
		ans[1] = temp0;
		ans[2] = temp1;
		return ans[0];
	
	}
	
	else if(carLaneNumber==lanes) {
		
		
		P1 = lanes-1;
		int pos1 = PosX[index];
		
		
		int temp0 =  isAnyNearby0(P2, pos1, PosX, laneCarIndex, Road_Length, VehicleInside, index, Vehicle, Vehicle_Length, len);
		int temp1 =  isAnyNearby1(P2, pos1, PosX, laneCarIndex, Road_Length, VehicleInside, index, Vehicle, Vehicle_Length, len);
	    ans[0] = P2;
		ans[1] = temp0;
		ans[2] = temp1;
		
		return ans[0];
	
	
	
	}
	else{
		
		P1 = carLaneNumber-1; 
		P2 = carLaneNumber+1;
		
		int pos1 = PosX[index];
		
		
		int temp0 =  isAnyNearby0(P2, pos1, PosX, laneCarIndex, Road_Length, VehicleInside, index, Vehicle, Vehicle_Length, len);
		int temp1 =  isAnyNearby1(P2, pos1, PosX, laneCarIndex, Road_Length, VehicleInside, index, Vehicle, Vehicle_Length, len);
	    
		
		if(temp1==1){
			
			int temp10 =  isAnyNearby0(P2, pos1, PosX, laneCarIndex, Road_Length, VehicleInside, index, Vehicle, Vehicle_Length, len);
			int temp11 =  isAnyNearby1(P2, pos1, PosX, laneCarIndex, Road_Length, VehicleInside, index, Vehicle, Vehicle_Length, len);
			
			
			if(temp11==1){
				
				
				// Random impossible values to set the constraint that no overtaking is possible
				ans[0] = lanes;
				ans[1] = 0;
				ans[2] = 1;
				
				return ans[0];
			} 
			
			else{
				
				ans[0] = P2;
				ans[1] = temp10;
				ans[2] = temp11;
				
				return ans[0];
				
			}
			
		}
		
		else{
			
			ans[0] = P1;
			ans[1] = temp0;	
			ans[2] = temp1;
			return ans[0];
	
			
		
		}
	
	}
	
	
	
	
	
	
}

int findEmptyNeighbour1(int** laneCarIndex, int carLaneNumber, int lanes, int index, int* PosX, int Road_Length, string* VehicleInside, string* Vehicle, string* Vehicle_Length, int len){
	
	int P1,P2 = -1;
	int ans[3];	// 0 -> LaneNumber, 1 -> Vehicle to be constrained, 2 -> Constraint level
	
	if(carLaneNumber==0) {
		
		P2 =1;
		int pos1 = PosX[index];
		
		int temp0 =  isAnyNearby0(P2, pos1, PosX, laneCarIndex, Road_Length, VehicleInside, index, Vehicle, Vehicle_Length, len);
		int temp1 =  isAnyNearby1(P2, pos1, PosX, laneCarIndex, Road_Length, VehicleInside, index, Vehicle, Vehicle_Length, len);
	    ans[0] = P2;
		ans[1] = temp0;
		ans[2] = temp1;
		return ans[1];
	
	}
	else if(carLaneNumber==lanes) {
		
		
		P1 = lanes-1;
		int pos1 = PosX[index];
		
		
		int temp0 =  isAnyNearby0(P2, pos1, PosX, laneCarIndex, Road_Length, VehicleInside, index, Vehicle, Vehicle_Length, len);
		int temp1 =  isAnyNearby1(P2, pos1, PosX, laneCarIndex, Road_Length, VehicleInside, index, Vehicle, Vehicle_Length, len);
	    ans[0] = P2;
		ans[1] = temp0;
		ans[2] = temp1;
		
		return ans[1];
	
	
	
	}
	else{
		
		P1 = carLaneNumber-1; 
		P2 = carLaneNumber+1;
		
		int pos1 = PosX[index];
		
		
		int temp0 =  isAnyNearby0(P2, pos1, PosX, laneCarIndex, Road_Length, VehicleInside, index, Vehicle, Vehicle_Length, len);
		int temp1 =  isAnyNearby1(P2, pos1, PosX, laneCarIndex, Road_Length, VehicleInside, index, Vehicle, Vehicle_Length, len);
	    
		
		if(temp1==1){
			
			int temp10 =  isAnyNearby0(P2, pos1, PosX, laneCarIndex, Road_Length, VehicleInside, index, Vehicle, Vehicle_Length, len);
			int temp11 =  isAnyNearby1(P2, pos1, PosX, laneCarIndex, Road_Length, VehicleInside, index, Vehicle, Vehicle_Length, len);
			
			
			if(temp11==1){
				
				
				// Random impossible values to set the constraint that no overtaking is possible
				ans[0] = lanes;
				ans[1] = 0;
				ans[2] = 1;
				
				return ans[1];
			} 
			
			else{
				
				ans[0] = P2;
				ans[1] = temp10;
				ans[2] = temp11;
				
				return ans[1];
				
			}
			
		}
		
		else{
			
			ans[0] = P1;
			ans[1] = temp0;	
			ans[2] = temp1;
			return ans[1];
	
			
		
		}
	
	}
	
	
	
	
	
	
}

int findEmptyNeighbour2(int** laneCarIndex, int carLaneNumber, int lanes, int index, int* PosX, int Road_Length, string* VehicleInside, string* Vehicle, string* Vehicle_Length, int len){
	
	int P1,P2 = -1;
	int ans[3];	// 0 -> LaneNumber, 1 -> Vehicle to be constrained, 2 -> Constraint level
	
	if(carLaneNumber==0) {
		
		P2 =1;
		int pos1 = PosX[index];
		
		int temp0 =  isAnyNearby0(P2, pos1, PosX, laneCarIndex, Road_Length, VehicleInside, index, Vehicle, Vehicle_Length, len);
		int temp1 =  isAnyNearby1(P2, pos1, PosX, laneCarIndex, Road_Length, VehicleInside, index, Vehicle, Vehicle_Length, len);
	    ans[0] = P2;
		ans[1] = temp0;
		ans[2] = temp1;
		return ans[2];
	
	}
	else if(carLaneNumber==lanes) {
		
		
		P1 = lanes-1;
		int pos1 = PosX[index];
		
		
		int temp0 =  isAnyNearby0(P2, pos1, PosX, laneCarIndex, Road_Length, VehicleInside, index, Vehicle, Vehicle_Length, len);
		int temp1 =  isAnyNearby1(P2, pos1, PosX, laneCarIndex, Road_Length, VehicleInside, index, Vehicle, Vehicle_Length, len);
	    ans[0] = P2;
		ans[1] = temp0;
		ans[2] = temp1;
		
		return ans[2];
	
	
	
	}
	else{
		
		P1 = carLaneNumber-1; 
		P2 = carLaneNumber+1;
		
		int pos1 = PosX[index];
		
		
		int temp0 =  isAnyNearby0(P2, pos1, PosX, laneCarIndex, Road_Length, VehicleInside, index, Vehicle, Vehicle_Length, len);
		int temp1 =  isAnyNearby1(P2, pos1, PosX, laneCarIndex, Road_Length, VehicleInside, index, Vehicle, Vehicle_Length, len);
	    
		
		if(temp1==1){
			
			int temp10 =  isAnyNearby0(P2, pos1, PosX, laneCarIndex, Road_Length, VehicleInside, index, Vehicle, Vehicle_Length, len);
			int temp11 =  isAnyNearby1(P2, pos1, PosX, laneCarIndex, Road_Length, VehicleInside, index, Vehicle, Vehicle_Length, len);
			
			
			if(temp11==1){
				
				
				// Random impossible values to set the constraint that no overtaking is possible
				ans[0] = lanes;
				ans[1] = 0;
				ans[2] = 1;
				
				return ans[2];
			} 
			
			else{
				
				ans[0] = P2;
				ans[1] = temp10;
				ans[2] = temp11;
				
				return ans[2];
				
			}
			
		}
		
		else{
			
			ans[0] = P1;
			ans[1] = temp0;	
			ans[2] = temp1;
			return ans[2];
	
			
		
		}
	
	}
	
	
	
	
	
	
}



void addInLayer(int** laneCarIndex, int lanes, int changingLane, int index, int* PosX){
	
	int i=0;
	
	for(; i<10; i++){
		
		if(laneCarIndex[changingLane][i]==0) break;
		else{
			
			int val = PosX[(laneCarIndex[changingLane][i])];
			
			if(val < PosX[index]) break;
			
			
		}
	}
	
	if(i!=10){
		
		for(int j=9 ; j>i ;j++){
			
		if(laneCarIndex[changingLane][j]==0) continue;
		else{
			
				laneCarIndex[changingLane][j] = laneCarIndex[changingLane][j-1];
			
		}

			
		}
		
		laneCarIndex[changingLane][i] = index;
		return;
	}
	
	return;
}

void removeFromLayer(int** laneCarIndex, int lanes, int carLaneNumber, int carLaneIndex, int index, int PosX){
	
	for(int i=carLaneIndex; i<10; i++){
		
		if(laneCarIndex[carLaneNumber][i]==0) break;
		else{
			
			laneCarIndex[carLaneNumber][i] = laneCarIndex[carLaneNumber][i+1];
			
		}
		
	}
	return;
}

// COMMENT: Kinematics and constraints!
int positionUpdate(int index, int* V, int* Vf , int* A, int* Ret, int* LaneChange, char*** Road, int t, int* Start_Time, int* PosX, int* PosY, char* ColorInside, string* VehicleInside, bool RG, int** laneCarIndex, int** laneInfo, int lanes, int Road_Length, int Road_Width, string* Vehicle, string* Vehicle_Length, string* Vehicle_Width, int len, bool* isOvertaking, string* Vehicle_LaneChange, int* overtakeLayer, int vehAmount, string* Default, int* laneStopPosition){
	
if(ColorInside[index]!=' '){ 
	
   if(RG){
	//cout << "hi" << endl;
	// GREEN: So no red light BT!
	
     if(VehicleInside[index] != "Human"){
    
       if(PosX[index]>=0){		// Already in motion
	
    if(!isOvertaking[index]){
 	

    //	cout << "Rewached" << endl;

     int carLaneNumber = findLaneNumber(index, laneCarIndex, lanes);
	 int carLaneIndex = findLaneIndex(index, laneCarIndex, lanes);
	 
    
	 if((carLaneNumber == lanes) || (carLaneIndex==10)) return -1;
	 
	 bool collision = aboutToCollide(laneCarIndex, index, carLaneNumber, carLaneIndex, Vf, A, PosX, PosY, len, Vehicle, VehicleInside,Vehicle_Length);

		if(collision==false) {
		 
 	// ABBA
			//cout << "At time t: " << t << " the diff is " <<  t-Start_Time[index] << " For the index: " << ColorInside[index] << endl;


			if((PosX[index] >= laneStopPosition[index] -1) || (PosX[index] >= atoi(Default[6].c_str())-1)) {   V[index] = 1;}

		int X = PosX[index] + V[index] + floor((1/2) * (A[index]) * (2*(t-Start_Time[index]) -1));
	 
		int Y = PosY[index];
	 	//cout << X << "For index: " << ColorInside[index] << "at t " << t << endl;
	 	//cout << PosX[index] << "For index: " << ColorInside[index] << "at t " << t << endl;
		PosX[index] = X;
		PosY[index] = Y;
		Vf[index] = V[index] + A[index] * (t-Start_Time[index]);
		}
     	 
		else{
			

			//0 -> LaneNumber, 1 -> Vehicle to be constrained, 2 -> Constraint level
			
			int neighbour[3];

         		neighbour[0] = findEmptyNeighbour0(laneCarIndex, carLaneNumber,lanes, index, PosX, Road_Length, VehicleInside, Vehicle, Vehicle_Length, len);	// 0 -> Lane; 1 -> Constraint
				neighbour[1] = findEmptyNeighbour1(laneCarIndex, carLaneNumber,lanes, index, PosX, Road_Length, VehicleInside, Vehicle, Vehicle_Length, len);	// 0 -> Lane; 1 -> Constraint
				neighbour[2] = findEmptyNeighbour2(laneCarIndex, carLaneNumber,lanes, index, PosX, Road_Length, VehicleInside, Vehicle, Vehicle_Length, len);	// 0 -> Lane; 1 -> Constraint
			
			if (neighbour[2] == 1){
				
				// No place available
				
				Vf[(laneCarIndex[carLaneNumber][carLaneIndex])] = Vf[(laneCarIndex[carLaneNumber][carLaneIndex-1])]; // Retardation effect
				
				PosX[index] = topLeftX(PosX[index], PosY[index],Vehicle, VehicleInside[(laneCarIndex[carLaneNumber][carLaneIndex-1])], len, Vehicle_Length) -1;
				
			}
			
			else if(neighbour[2] == -1){
				
				// No constrain
				
				int changingLane = neighbour[0];
				isOvertaking[index] = true;
				overtakeLayer[index] = changingLane;
				
				if(carLaneNumber < changingLane){
					
					// Goes down now
					
						LaneChange[index] =  -atoi(Vehicle_LaneChange[(findIndexOfStr(Vehicle,VehicleInside[index],len))].c_str());
						PosY[index] = PosY[index] + LaneChange[index];
						
						Vf[(laneCarIndex[carLaneNumber][carLaneIndex])] = Vf[(laneCarIndex[carLaneNumber][carLaneIndex-1])]; // Retardation effect
				
						PosX[index] = topLeftX(PosX[index], PosY[index],Vehicle, VehicleInside[(laneCarIndex[carLaneNumber][carLaneIndex-1])], len, Vehicle_Length) -1;
				
						
						int laneEnd  = changingLane* (Road_Width/lanes);
						
						if((topLeftY(PosX[index], PosY[index],Vehicle, VehicleInside[index],len, Vehicle_Width)) >= laneEnd) {
							
							isOvertaking[index] = false;
							LaneChange[index] = 0;
							overtakeLayer[index]=-1;
							addInLayer(laneCarIndex,lanes,changingLane,index,PosX);	
							removeFromLayer(laneCarIndex,lanes,carLaneNumber, carLaneIndex,index,PosX[index]);
						}
						
				}
				
				else{
					
						LaneChange[index] =  atoi(Vehicle_LaneChange[(findIndexOfStr(Vehicle,VehicleInside[index],len))].c_str());
						PosY[index] = PosY[index] + LaneChange[index];
						
						Vf[(laneCarIndex[carLaneNumber][carLaneIndex])] = Vf[(laneCarIndex[carLaneNumber][carLaneIndex-1])]; // Retardation effect
				
						PosX[index] = topLeftX(PosX[index], PosY[index],Vehicle, VehicleInside[(laneCarIndex[carLaneNumber][carLaneIndex-1])], len, Vehicle_Length) -1;
				
						
						int laneEnd;

						if(changingLane==lanes-1) {
		
							 laneEnd = Road_Width - 1;
						}
						
						else laneEnd = changingLane * (Road_Width/lanes) + (Road_Width/lanes) -1;
		
						
						if((topLeftY(PosX[index], PosY[index],Vehicle, VehicleInside[index],len, Vehicle_Width)) <= laneEnd) {
							
							isOvertaking[index] = false;
							LaneChange[index] = 0;
							overtakeLayer[index] = -1;
							addInLayer(laneCarIndex,lanes,changingLane,index,PosX);	
							removeFromLayer(laneCarIndex,lanes,carLaneNumber, carLaneIndex,index,PosX[index]);
						}
						
					
					
				}
				
				
			}
			
			else{
				
				Vf[neighbour[1]] = Vf[index];		// Constraining the Vehicle on the Behind.
				
				int changingLane = neighbour[0];
				isOvertaking[index] = true;
				
				
				if(carLaneNumber < changingLane){
					
					// Goes down now
					
						LaneChange[index] =  atoi(Vehicle_LaneChange[(findIndexOfStr(Vehicle,VehicleInside[index],len))].c_str());
						PosY[index] = PosY[index] + LaneChange[index];
						
						Vf[(laneCarIndex[carLaneNumber][carLaneIndex])] = Vf[(laneCarIndex[carLaneNumber][carLaneIndex-1])]; // Retardation effect
				
						PosX[index] = topLeftX(PosX[index], PosY[index],Vehicle, VehicleInside[(laneCarIndex[carLaneNumber][carLaneIndex-1])], len, Vehicle_Length) -1;
				
						
						int laneEnd  = changingLane* (Road_Width/lanes);
						
						if((topLeftY(PosX[index], PosY[index],Vehicle, VehicleInside[index],len,Vehicle_Width)) >= laneEnd) {
							
							isOvertaking[index] = false;
							LaneChange[index] = 0;
							addInLayer(laneCarIndex,lanes,changingLane,index,PosX);	
							removeFromLayer(laneCarIndex,lanes,carLaneNumber, carLaneIndex,index,PosX[index]);
						}
						
				}
				
				else{
					
						LaneChange[index] =  -atoi(Vehicle_LaneChange[(findIndexOfStr(Vehicle,VehicleInside[index],len))].c_str());
						PosY[index] = PosY[index] + LaneChange[index];
						
						Vf[(laneCarIndex[carLaneNumber][carLaneIndex])] = Vf[(laneCarIndex[carLaneNumber][carLaneIndex-1])]; // Retardation effect
				
						PosX[index] = topLeftX(PosX[index], PosY[index],Vehicle, VehicleInside[(laneCarIndex[carLaneNumber][carLaneIndex-1])], len, Vehicle_Length) -1;
				
						
						int laneEnd;

						if(changingLane==lanes-1) {
		
							 laneEnd = Road_Width - 1;
						}
						
						else laneEnd = changingLane * (Road_Width/lanes) + (Road_Width/lanes) -1;
		
						
						if((topLeftY(PosX[index], PosY[index],Vehicle, VehicleInside[index],len, Vehicle_Width)) <= laneEnd) {
							
							isOvertaking[index] = false;
							LaneChange[index] = 0;
							addInLayer(laneCarIndex,lanes,changingLane,index,PosX);	
							removeFromLayer(laneCarIndex,lanes,carLaneNumber, carLaneIndex,index,PosX[index]);
						}
						
					
				  }
				}
				
				
			}
		
		  // Show the updates on the corresponding road.	
		
			int rightBottomX = PosX[index];
			int rightBottomY = PosY[index];
			
			int leftTopX = topLeftX(PosX[index], PosY[index], Vehicle, VehicleInside[index],len, Vehicle_Length);
			int leftTopY = topLeftY(PosX[index], PosY[index], Vehicle, VehicleInside[index],len, Vehicle_Width);
		
        		
		
		
		  if(leftTopX<Road_Length){
			for(int j=leftTopX; j<= (min(Road_Length,rightBottomX)); j++){
						
						for(int i = leftTopY+2; i <= rightBottomY +2 ; i++){
							
							Road[t][i][j] = ColorInside[index];
							

						}
						
					}
					
			int zeroLine = min(Road_Length,PosX[index]) + (vehAmount - Road_Length - 1) + 1;
		    int carLaneNumber = findLaneNumber(index, laneCarIndex, lanes);
			int VehIndex = findIndexOfStr(Vehicle, VehicleInside[index], len);
		    for(int i= zeroLine; i > zeroLine - atoi(Vehicle_Length[VehIndex].c_str()); i--){laneInfo[carLaneNumber][i] = 1;}	
					
					
		  }
		  
		  else{
			  
				ColorInside[index] = ' ';
				int carLaneNumber = findLaneNumber(index, laneCarIndex, lanes);
				int carLaneIndex = findLaneIndex(index, laneCarIndex, lanes);		  

		   		removeFromLayer(laneCarIndex,lanes,carLaneNumber, carLaneIndex,index,PosX[index]);
		  }
		  
		    return 0;	
		}

    else{
		
			int changingLane = overtakeLayer[index];
			int carLaneNumber = findLaneNumber(index, laneCarIndex, lanes);
			int carLaneIndex = findLaneIndex(index, laneCarIndex, lanes);		  

			if(carLaneNumber < changingLane){
					
					// Goes down now
					
						LaneChange[index] =  -atoi(Vehicle_LaneChange[(findIndexOfStr(Vehicle,VehicleInside[index],len))].c_str());
						PosY[index] = PosY[index] + LaneChange[index];
						
						Vf[(laneCarIndex[carLaneNumber][carLaneIndex])] = Vf[(laneCarIndex[carLaneNumber][carLaneIndex-1])]; // Retardation effect
				
						PosX[index] = topLeftX(PosX[index], PosY[index],Vehicle, VehicleInside[(laneCarIndex[carLaneNumber][carLaneIndex-1])], len, Vehicle_Length) -1;
				
						
						int laneEnd  = changingLane* (Road_Width/lanes);
						
						if((topLeftY(PosX[index], PosY[index],Vehicle, VehicleInside[index],len,Vehicle_Width)) >= laneEnd) {
							
							isOvertaking[index] = false;
							LaneChange[index] = 0;
							overtakeLayer[index]=-1;
							addInLayer(laneCarIndex,lanes,changingLane,index,PosX);	
							removeFromLayer(laneCarIndex,lanes,carLaneNumber, carLaneIndex,index,PosX[index]);
						}
						
				}
				
				else{
					
						LaneChange[index] =  atoi(Vehicle_LaneChange[(findIndexOfStr(Vehicle,VehicleInside[index],len))].c_str());
						PosY[index] = PosY[index] + LaneChange[index];
						
						Vf[(laneCarIndex[carLaneNumber][carLaneIndex])] = Vf[(laneCarIndex[carLaneNumber][carLaneIndex-1])]; // Retardation effect
				
						PosX[index] = topLeftX(PosX[index], PosY[index],Vehicle, VehicleInside[(laneCarIndex[carLaneNumber][carLaneIndex-1])], len, Vehicle_Length) -1;
				
						
						int laneEnd;

						if(changingLane==lanes-1) {
		
							 laneEnd = Road_Width - 1;
						}
						
						else laneEnd = changingLane * (Road_Width/lanes) + (Road_Width/lanes) -1;
		
						
						if((topLeftY(PosX[index], PosY[index],Vehicle, VehicleInside[index],len, Vehicle_Width)) <= laneEnd) {
							
							isOvertaking[index] = false;
							LaneChange[index] = 0;
							overtakeLayer[index] = -1;
							addInLayer(laneCarIndex,lanes,changingLane,index,PosX);	
							removeFromLayer(laneCarIndex,lanes,carLaneNumber, carLaneIndex,index,PosX[index]);
						}
						
					
					
				}
				

		    int rightBottomX = PosX[index];
			int rightBottomY = PosY[index];
			
			int leftTopX = topLeftX(PosX[index], PosY[index], Vehicle, VehicleInside[index],len, Vehicle_Length);
			int leftTopY = topLeftY(PosX[index], PosY[index], Vehicle, VehicleInside[index],len, Vehicle_Length);
		
		
		  if(leftTopX<Road_Length){
			for(int j=leftTopX; j<= (min(Road_Length,rightBottomX)); j++){
						
						for(int i = leftTopY+2; i <= rightBottomY +2 ; i++){
							
							Road[t][i][j] = ColorInside[index];
							
						}
						
					}
					
			int zeroLine = min(Road_Length,PosX[index]) + (vehAmount - Road_Length - 1) + 1;
		    int carLaneNumber = findLaneNumber(index, laneCarIndex, lanes);
			int VehIndex = findIndexOfStr(Vehicle, VehicleInside[index], len);
		    for(int i= zeroLine; i > zeroLine - atoi(Vehicle_Length[VehIndex].c_str()); i--){laneInfo[carLaneNumber][i] = 1;}	
				
					
		  }
		  
		  else{
			  
				ColorInside[index] = ' ';
				int carLaneNumber = findLaneNumber(index, laneCarIndex, lanes);
				int carLaneIndex = findLaneIndex(index, laneCarIndex, lanes);		  

		   		removeFromLayer(laneCarIndex,lanes,carLaneNumber, carLaneIndex,index,PosX[index]);
		  }
			
		return 0;	
			
	}	
   }	
	
       else{
	

       
	 int carLaneNumber = findLaneNumber(index, laneCarIndex, lanes);
	 int carLaneIndex = findLaneIndex(index, laneCarIndex, lanes);


	 
	 if((carLaneNumber == lanes) || (carLaneIndex==10)) return -1;
	 
	 bool collision = aboutToCollide(laneCarIndex, index, carLaneNumber, carLaneIndex, Vf, A, PosX, PosY, len, Vehicle, VehicleInside, Vehicle_Length);
	 
		if(collision==false) {
		 
		int X = PosX[index] + V[index] + floor((1/2) * A[index] * (2*(t-Start_Time[index]) -1));
	 
		int Y = PosY[index];
	 
		PosX[index] = X;
		PosY[index] = Y;
		Vf[index] = V[index] + A[index] * (t-Start_Time[index]);
		}
     	 
		else{
			
		
				Vf[(laneCarIndex[carLaneNumber][carLaneIndex])] = Vf[(laneCarIndex[carLaneNumber][carLaneIndex-1])]; // Retardation effect
				
				PosX[index] = topLeftX(PosX[index], PosY[index],Vehicle, VehicleInside[(laneCarIndex[carLaneNumber][carLaneIndex-1])], len, Vehicle_Length) -1;
				
			}
			

		  // Show the updates on the corresponding road.	
		    
			int rightBottomX = PosX[index];
			int rightBottomY = PosY[index];
			
			int leftTopX = topLeftX(PosX[index], PosY[index], Vehicle, VehicleInside[index],len, Vehicle_Length);
			int leftTopY = topLeftY(PosX[index], PosY[index], Vehicle, VehicleInside[index],len, Vehicle_Width);
		
		
		  if(rightBottomX>0){
			for(int j=max(0,leftTopX); j<= rightBottomX; j++){
						
						for(int i = leftTopY+2; i <= rightBottomY +2 ; i++){
							
							Road[t][i][j] = ColorInside[index];
							
						}
						
			}
			
			int zeroLine = min(Road_Length,PosX[index]) + (vehAmount - Road_Length - 1) + 1;
		    int carLaneNumber = findLaneNumber(index, laneCarIndex, lanes);
			int VehIndex = findIndexOfStr(Vehicle, VehicleInside[index], len);
		    for(int i= zeroLine; i > zeroLine - atoi(Vehicle_Length[VehIndex].c_str()); i--){laneInfo[carLaneNumber][i] = 1;}	
			
	
		  }
	 
	 
   else{
		 
		 // TO DO: Human
			return 0;
	  }
		 
	}
     }
	 
	 
     else{
	  
	  // TO DO: Human
	  
  }
  
   }
   
   
   else{
	 
	if(VehicleInside[index] != "Human"){
    
      if(PosX[index]>=0){		// Already in motion
	
        if(!isOvertaking[index]){
 	
			int Road_Signal_Position = atoi(Default[6].c_str());
     int carLaneNumber = findLaneNumber(index, laneCarIndex, lanes);
	 int carLaneIndex = findLaneIndex(index, laneCarIndex, lanes);
	 
	 if((carLaneNumber == lanes) || (carLaneIndex==10)) return -1;
	 
	 bool collision = aboutToCollide(laneCarIndex, index, carLaneNumber, carLaneIndex, Vf, A, PosX, PosY, len, Vehicle, VehicleInside, Vehicle_Length);
	 
		if(collision==false) {
		 
		int X = PosX[index] + V[index] + floor((1/2) * A[index] * (2*(t-Start_Time[index]) -1));
	 
		int Y = PosY[index];
	 
		PosX[index] = X;
		PosY[index] = Y;
		Vf[index] = V[index] + A[index] * (t-Start_Time[index]);
		}
     	 
		else{
			

			//0 -> LaneNumber, 1 -> Vehicle to be constrained, 2 -> Constraint level
			
			int neighbour[3];

			neighbour[2]	= findEmptyNeighbour2(laneCarIndex, carLaneNumber,lanes, index, PosX, Road_Length, VehicleInside, Vehicle, Vehicle_Length, len);	// 0 -> Lane; 1 -> Constraint
			neighbour[1]	= findEmptyNeighbour1(laneCarIndex, carLaneNumber,lanes, index, PosX, Road_Length, VehicleInside, Vehicle, Vehicle_Length, len);	// 0 -> Lane; 1 -> Constraint
			neighbour[0]	= findEmptyNeighbour0(laneCarIndex, carLaneNumber,lanes, index, PosX, Road_Length, VehicleInside, Vehicle, Vehicle_Length, len);	// 0 -> Lane; 1 -> Constraint
			if (neighbour[2] == 1){
				
				// No place available
				
				Vf[(laneCarIndex[carLaneNumber][carLaneIndex])] = Vf[(laneCarIndex[carLaneNumber][carLaneIndex-1])]; // Retardation effect
				
				PosX[index] = topLeftX(PosX[index], PosY[index],Vehicle, VehicleInside[(laneCarIndex[carLaneNumber][carLaneIndex-1])], len, Vehicle_Length) -1;
				
			}
			
			else if(neighbour[2] == -1){
				
				// No constrain
				
				int changingLane = neighbour[0];
				isOvertaking[index] = true;
				overtakeLayer[index] = changingLane;
				
				if(carLaneNumber < changingLane){
					
					// Goes down now
					
						LaneChange[index] =  -atoi(Vehicle_LaneChange[(findIndexOfStr(Vehicle,VehicleInside[index],len))].c_str());
						PosY[index] = PosY[index] + LaneChange[index];
						
						Vf[(laneCarIndex[carLaneNumber][carLaneIndex])] = Vf[(laneCarIndex[carLaneNumber][carLaneIndex-1])]; // Retardation effect
				
						PosX[index] = topLeftX(PosX[index], PosY[index],Vehicle, VehicleInside[(laneCarIndex[carLaneNumber][carLaneIndex-1])], len, Vehicle_Length) -1;
				
						
						int laneEnd  = changingLane* (Road_Width/lanes);
						
						if((topLeftY(PosX[index], PosY[index],Vehicle, VehicleInside[index],len,Vehicle_Width)) >= laneEnd) {
							
							isOvertaking[index] = false;
							LaneChange[index] = 0;
							overtakeLayer[index]=-1;
							addInLayer(laneCarIndex,lanes,changingLane,index,PosX);	
							removeFromLayer(laneCarIndex,lanes,carLaneNumber, carLaneIndex,index,PosX[index]);
						}
						
				}
				
				else{
							
						LaneChange[index] =  atoi(Vehicle_LaneChange[(findIndexOfStr(Vehicle,VehicleInside[index],len))].c_str());
						PosY[index] = PosY[index] + LaneChange[index];
						
						Vf[(laneCarIndex[carLaneNumber][carLaneIndex])] = Vf[(laneCarIndex[carLaneNumber][carLaneIndex-1])]; // Retardation effect
						
						PosX[index] = topLeftX(PosX[index], PosY[index],Vehicle, VehicleInside[(laneCarIndex[carLaneNumber][carLaneIndex-1])], len, Vehicle_Length) -1;
						
						
						int laneEnd;

						if(changingLane==lanes-1) {
		
							 laneEnd = Road_Width - 1;
						}
						
						else laneEnd = changingLane * (Road_Width/lanes) + (Road_Width/lanes) -1;
		
						
						if((topLeftY(PosX[index], PosY[index],Vehicle, VehicleInside[index],len, Vehicle_Width)) <= laneEnd) {
							
							isOvertaking[index] = false;
							LaneChange[index] = 0;
							overtakeLayer[index] = -1;
							addInLayer(laneCarIndex,lanes,changingLane,index,PosX);	
							removeFromLayer(laneCarIndex,lanes,carLaneNumber, carLaneIndex,index,PosX[index]);
						}
						
					
					
				}
				
				
			}
			
			else{
				
				Vf[neighbour[1]] = Vf[index];		// Constraining the Vehicle on the Behind.
				
				int changingLane = neighbour[0];
				isOvertaking[index] = true;
				
				
				if(carLaneNumber < changingLane){
					
					// Goes down now
					
						LaneChange[index] =  atoi(Vehicle_LaneChange[(findIndexOfStr(Vehicle,VehicleInside[index],len))].c_str());
						PosY[index] = PosY[index] + LaneChange[index];
						
						Vf[(laneCarIndex[carLaneNumber][carLaneIndex])] = Vf[(laneCarIndex[carLaneNumber][carLaneIndex-1])]; // Retardation effect
				
						PosX[index] = topLeftX(PosX[index], PosY[index],Vehicle, VehicleInside[(laneCarIndex[carLaneNumber][carLaneIndex-1])], len, Vehicle_Length) -1;
				
						
						int laneEnd  = changingLane* (Road_Width/lanes);
						
						if((topLeftY(PosX[index], PosY[index],Vehicle, VehicleInside[index],len,Vehicle_Width)) >= laneEnd) {
							
							isOvertaking[index] = false;
							LaneChange[index] = 0;
							addInLayer(laneCarIndex,lanes,changingLane,index,PosX);	
							removeFromLayer(laneCarIndex,lanes,carLaneNumber, carLaneIndex,index,PosX[index]);
						}
						
				}
				
				else{
					
						LaneChange[index] =  -atoi(Vehicle_LaneChange[(findIndexOfStr(Vehicle,VehicleInside[index],len))].c_str());
						PosY[index] = PosY[index] + LaneChange[index];
						
						Vf[(laneCarIndex[carLaneNumber][carLaneIndex])] = Vf[(laneCarIndex[carLaneNumber][carLaneIndex-1])]; // Retardation effect
				
						PosX[index] = topLeftX(PosX[index], PosY[index],Vehicle, VehicleInside[(laneCarIndex[carLaneNumber][carLaneIndex-1])], len, Vehicle_Length) -1;
				
						
						int laneEnd;

						if(changingLane==lanes-1) {
		
							 laneEnd = Road_Width - 1;
						}
						
						else laneEnd = changingLane * (Road_Width/lanes) + (Road_Width/lanes) -1;
		
						
						if((topLeftY(PosX[index], PosY[index],Vehicle, VehicleInside[index],len, Vehicle_Width)) <= laneEnd) {
							
							isOvertaking[index] = false;
							LaneChange[index] = 0;
							addInLayer(laneCarIndex,lanes,changingLane,index,PosX);	
							removeFromLayer(laneCarIndex,lanes,carLaneNumber, carLaneIndex,index,PosX[index]);
						}
						
					
			    	}
				}
				
				
			}
			
			 // Show the updates on the corresponding road.	
		   
		    carLaneNumber = findLaneNumber(index, laneCarIndex, lanes); 
		
			int signalStop= laneStopPosition[carLaneNumber];	
		
			int rightBottomX = PosX[index];
			int rightBottomY = PosY[index];
			
			int leftTopX = topLeftX(PosX[index], PosY[index], Vehicle, VehicleInside[index],len, Vehicle_Length);
			int leftTopY = topLeftY(PosX[index], PosY[index], Vehicle, VehicleInside[index],len, Vehicle_Width);
		
        		
		
		
		  if(leftTopX<Road_Length){
			
			
			
			if(leftTopX>=signalStop-1){
			
				for(int j=leftTopX; j<= (min(Road_Length,rightBottomX)); j++){
						
						for(int i = leftTopY+2; i <= rightBottomY +2 ; i++){
							
							Road[t][i][j] = ColorInside[index];
							
						}
						
					}
					
				int zeroLine = min(Road_Length,PosX[index]) + (vehAmount - Road_Length - 1) + 1;
		    int carLaneNumber = findLaneNumber(index, laneCarIndex, lanes);
			int VehIndex = findIndexOfStr(Vehicle, VehicleInside[index], len);
		    for(int i= zeroLine; i > zeroLine - atoi(Vehicle_Length[VehIndex].c_str()); i--){laneInfo[carLaneNumber][i] = 1;}	
			
				
				
			}
			
			else if(rightBottomX >= signalStop-1){
				
				rightBottomX = signalStop-1;
				PosX[index] = signalStop-1;
				A[index] = 1;
				leftTopX = topLeftX(PosX[index], PosY[index], Vehicle, VehicleInside[index],len, Vehicle_Length);
				
				for(int j=leftTopX; j<= (min(Road_Length,rightBottomX)); j++){
						
						for(int i = leftTopY+2; i<= rightBottomY +2 ; i++){
							
							Road[t][i][j] = ColorInside[index];
							
						}
						
					}
					
				int zeroLine = min(Road_Length,PosX[index]) + (vehAmount - Road_Length - 1) + 1;
		    int carLaneNumber = findLaneNumber(index, laneCarIndex, lanes);
			int VehIndex = findIndexOfStr(Vehicle, VehicleInside[index], len);
		    for(int i= zeroLine; i > zeroLine - atoi(Vehicle_Length[VehIndex].c_str()); i--){laneInfo[carLaneNumber][i] = 1;}	
			
				laneStopPosition[carLaneNumber] = leftTopX-1;
				Vf[index] = 0;
				V[index] = 0;
				Start_Time[index] = t;
			}
			
			else{
				
				for(int j=leftTopX; j<=(min(Road_Length,rightBottomX)); j++){
						
						for(int i = leftTopY+2; i <= rightBottomY +2 ; i++){
							
							Road[t][i][j] = ColorInside[index];
							
						}
						
					}
					
				int zeroLine = min(Road_Length,PosX[index]) + (vehAmount - Road_Length - 1) + 1;
		    int carLaneNumber = findLaneNumber(index, laneCarIndex, lanes);
			int VehIndex = findIndexOfStr(Vehicle, VehicleInside[index], len);
		    for(int i= zeroLine; i > zeroLine - atoi(Vehicle_Length[VehIndex].c_str()); i--){laneInfo[carLaneNumber][i] = 1;}	
			
				
				
			}
				
		  }
		  
		  else{
			  
				ColorInside[index] = ' ';
				int carLaneNumber = findLaneNumber(index, laneCarIndex, lanes);
				int carLaneIndex = findLaneIndex(index, laneCarIndex, lanes);		  

		   		removeFromLayer(laneCarIndex,lanes,carLaneNumber, carLaneIndex,index,PosX[index]);
		  }
		  
		   return 0;    	
			
		}	
		 
		

        else{
		
				int changingLane = overtakeLayer[index];
				int carLaneNumber = findLaneNumber(index, laneCarIndex, lanes);
				int carLaneIndex = findLaneIndex(index, laneCarIndex, lanes);		  

				int signalStop = laneStopPosition[carLaneNumber];	
		

			if(carLaneNumber < changingLane){
					
					// Goes down now
					
						LaneChange[index] =  -atoi(Vehicle_LaneChange[(findIndexOfStr(Vehicle,VehicleInside[index],len))].c_str());
						PosY[index] = PosY[index] + LaneChange[index];
						
						Vf[(laneCarIndex[carLaneNumber][carLaneIndex])] = Vf[(laneCarIndex[carLaneNumber][carLaneIndex-1])]; // Retardation effect
				
						PosX[index] = topLeftX(PosX[index], PosY[index],Vehicle, VehicleInside[(laneCarIndex[carLaneNumber][carLaneIndex-1])], len, Vehicle_Length) -1;
				
						
						int laneEnd  = changingLane* (Road_Width/lanes);
						
						if((topLeftY(PosX[index], PosY[index],Vehicle, VehicleInside[index],len, Vehicle_Width)) >= laneEnd) {
							
							isOvertaking[index] = false;
							LaneChange[index] = 0;
							overtakeLayer[index]=-1;
							addInLayer(laneCarIndex,lanes,changingLane,index,PosX);	
							removeFromLayer(laneCarIndex,lanes,carLaneNumber, carLaneIndex,index,PosX[index]);
						}
						
				}
				
				else{
					
						LaneChange[index] =  atoi(Vehicle_LaneChange[(findIndexOfStr(Vehicle,VehicleInside[index],len))].c_str());
						PosY[index] = PosY[index] + LaneChange[index];
						
						Vf[(laneCarIndex[carLaneNumber][carLaneIndex])] = Vf[(laneCarIndex[carLaneNumber][carLaneIndex-1])]; // Retardation effect
				
						PosX[index] = topLeftX(PosX[index], PosY[index],Vehicle, VehicleInside[(laneCarIndex[carLaneNumber][carLaneIndex-1])], len, Vehicle_Length) -1;
				
						
						int laneEnd;

						if(changingLane==lanes-1) {
		
							 laneEnd = Road_Width - 1;
						}
						
						else laneEnd = changingLane * (Road_Width/lanes) + (Road_Width/lanes) -1;
		
						
						if((topLeftY(PosX[index], PosY[index],Vehicle, VehicleInside[index],len, Vehicle_Width)) <= laneEnd) {
							
							isOvertaking[index] = false;
							LaneChange[index] = 0;
							overtakeLayer[index] = -1;
							addInLayer(laneCarIndex,lanes,changingLane,index,PosX);	
							removeFromLayer(laneCarIndex,lanes,carLaneNumber, carLaneIndex,index,PosX[index]);
						}
						
					
					
				}
				

		    int rightBottomX = PosX[index];
			int rightBottomY = PosY[index];
			
			int leftTopX = topLeftX(PosX[index], PosY[index], Vehicle, VehicleInside[index],len,Vehicle_Length);
			int leftTopY = topLeftY(PosX[index], PosY[index], Vehicle, VehicleInside[index],len, Vehicle_Width);
		
			 if(leftTopX<Road_Length){
			
			
			
			if(leftTopX>=signalStop-1){
			
				for(int j=leftTopX; j<= (min(Road_Length,rightBottomX)); j++){
						
						for(int i = leftTopY+2; i <= rightBottomY +2 ; i++){
							
							Road[t][i][j] = ColorInside[index];
							
						}
						
					}
					
				int zeroLine = min(Road_Length,PosX[index]) + (vehAmount - Road_Length - 1) + 1;
		    int carLaneNumber = findLaneNumber(index, laneCarIndex, lanes);
			int VehIndex = findIndexOfStr(Vehicle, VehicleInside[index], len);
		    for(int i= zeroLine; i > zeroLine - atoi(Vehicle_Length[VehIndex].c_str()); i--){laneInfo[carLaneNumber][i] = 1;}	
			
			}
			
			else if(rightBottomX >= signalStop-1){
				
				rightBottomX = signalStop-1;
				PosX[index] = signalStop-1;
				A[index] =1;
				leftTopX = topLeftX(PosX[index], PosY[index], Vehicle, VehicleInside[index],len, Vehicle_Length);
				
				for(int j=leftTopX; j<= (min(Road_Length,rightBottomX)); j++){
						
						for(int i = leftTopY+2; i <= rightBottomY +2 ; i++){
							
							Road[t][i][j] = ColorInside[index];
							
						}
						
					}
					
			int zeroLine = min(Road_Length,PosX[index]) + (vehAmount - Road_Length - 1) + 1;
		    int carLaneNumber = findLaneNumber(index, laneCarIndex, lanes);
			int VehIndex = findIndexOfStr(Vehicle, VehicleInside[index], len);
		    for(int i= zeroLine; i > zeroLine - atoi(Vehicle_Length[VehIndex].c_str()); i--){laneInfo[carLaneNumber][i] = 1;}	
				
				laneStopPosition[carLaneNumber] = leftTopX-1;
				Vf[index] = 0;
				V[index] = 0;
				Start_Time[index] = t;
			}
			
			else{
				
				for(int j=leftTopX; j<= (min(Road_Length,rightBottomX)); j++){
						
						for(int i = leftTopY+2; i <= rightBottomY +2 ; i++){
							
							Road[t][i][j] = ColorInside[index];
							
						}
						
					}
					
				int zeroLine = min(Road_Length,PosX[index]) + (vehAmount - Road_Length - 1) + 1;
		    int carLaneNumber = findLaneNumber(index, laneCarIndex, lanes);
			int VehIndex = findIndexOfStr(Vehicle, VehicleInside[index], len);
		    for(int i= zeroLine; i > zeroLine - atoi(Vehicle_Length[VehIndex].c_str()); i--){laneInfo[carLaneNumber][i] = 1;}	
			
				
				
			}
				
		  }
		  
			 else{
			  
				ColorInside[index] = ' ';
				int carLaneNumber = findLaneNumber(index, laneCarIndex, lanes);
				int carLaneIndex = findLaneIndex(index, laneCarIndex, lanes);		  

		   		removeFromLayer(laneCarIndex,lanes,carLaneNumber, carLaneIndex,index,PosX[index]);
		  }
		 
		 
			return 0;
	
	}	
	
      }	
	 
      else{
		 
		// COMMENT: Continue from here.....(Don't change the braces for this construct -_-) To be initialised. To use the laneInfo nouu 
  
		 
 	
     int carLaneNumber = findLaneNumber(index, laneCarIndex, lanes);
	 int carLaneIndex = findLaneIndex(index, laneCarIndex, lanes);
	 
	 if((carLaneNumber == lanes) || (carLaneIndex==10)) return -1;
	 
	 bool collision = aboutToCollide(laneCarIndex, index, carLaneNumber, carLaneIndex, Vf, A, PosX, PosY, len, Vehicle, VehicleInside,Vehicle_Length);
	 
		if(collision==false) {
		 
		int X = PosX[index] + V[index] + floor((1/2) * A[index] * (2*(t-Start_Time[index]) -1));
	 
		int Y = PosY[index];
	 
		PosX[index] = X;
		PosY[index] = Y;
		Vf[index] = V[index] + A[index] * (t-Start_Time[index]);
		}
     	 
		else{
			

				
				Vf[(laneCarIndex[carLaneNumber][carLaneIndex])] = Vf[(laneCarIndex[carLaneNumber][carLaneIndex-1])]; // Retardation effect
				
				PosX[index] = topLeftX(PosX[index], PosY[index],Vehicle, VehicleInside[(laneCarIndex[carLaneNumber][carLaneIndex-1])], len, Vehicle_Length) -1;
				
			
			}

			
		  // Show the updates on the corresponding road.	
          		
			int rightBottomX = PosX[index];
			int rightBottomY = PosY[index];
			
			int leftTopX = topLeftX(PosX[index], PosY[index], Vehicle, VehicleInside[index],len, Vehicle_Length);
			int leftTopY = topLeftY(PosX[index], PosY[index], Vehicle, VehicleInside[index],len, Vehicle_Width);
		
                    		
		
		
		  if(rightBottomX>=0){
			for(int j=max(0,leftTopX); j<=rightBottomX; j++){
						
						for(int i = leftTopY+2; i <= rightBottomY +2 ; i++){
							
							Road[t][i][j] = ColorInside[index];
							
						}
						
					}
					
					
		  }
		  
		  int zeroLine = min(Road_Length,PosX[index]) + (vehAmount - Road_Length - 1) + 1;
		    carLaneNumber = findLaneNumber(index, laneCarIndex, lanes);
			int VehIndex = findIndexOfStr(Vehicle, VehicleInside[index], len);
		    for(int i= zeroLine; i > zeroLine - atoi(Vehicle_Length[VehIndex].c_str()); i--){laneInfo[carLaneNumber][i] = 1;}	
			
		    	
			return 0;

    	  	
			
	  }
		 
	}
  
     else{
	   
	   
	    // TO DO HUman
		 return 0;  
   }
 
	  
  }
   
  }
	 
else {return 0;} 		 
	 
 }


 
 


//COMMENT: Updating the Road as per the proper mathematics	
void makeBasicRoad(char*** Road ,int t,int Start_Time,bool RG,int Road_Width,int Road_Length,string* Default){
	
		if(!RG){ 	//RED
			//cout<<"red \n";
				char str1[33];
			     itoa(t,str1,10);
				 
				char str2[33];
			     itoa((atoi(Default[3].c_str()) - (t%(atoi(Default[3].c_str())))),str2,10);
				//	cout << str2 << endl;

				string timeStr;

				timeStr.append("TIME ");
				timeStr.append(str1);
				timeStr.append(" LEFT ");
				timeStr.append(str2);
				timeStr.append(" ");

				int timeStr_len = timeStr.length();
	
				int Road_Signal_Position = atoi(Default[6].c_str());
	
				for(int i=0; i<timeStr_len; i++){
		
					Road[t][0][i+1] = timeStr[i];
		
					}

				Road[t][0][0] = ' ';
				for(int k=timeStr_len; k< Road_Length; k++){

						Road[t][0][k] = ' ';

				}	
	
			for (int i=1; i<Road_Width + 3 ; i++){
		
		
		
				for(int j=0; j<Road_Length; j++){
			
					if (i==1) Road[t][i][j] = '-';
					else if (i==Road_Width+2) Road[t][i][j] = '-';
					
					else    if((j==Road_Signal_Position) || (j==Road_Signal_Position + atoi(Default[5].c_str()))) Road[t][i][j] = '|';
					else Road[t][i][j] =' '; 
			
				}
		
		
			}
		}
		
		else{
			
			//	cout << "green" << endl;

				char str1[33];
			     itoa(t,str1,10);
				 
				char str2[33];
					 itoa((atoi(Default[3].c_str()) - (t%(atoi(Default[3].c_str())))),str2,10);
				

				string timeStr;

				timeStr.append("TIME ");
				timeStr.append(str1);
				timeStr.append(" LEFT ");
				timeStr.append(str2);
				timeStr.append(" ");
	
				//cout << timeStr << endl;

				int timeStr_len = timeStr.length();
		
				for(int i=0; i<timeStr_len; i++){
		
					Road[t][0][i+1] = timeStr[i];
		
					}

						Road[t][0][0] = ' ';
				for(int k=timeStr_len; k< Road_Length; k++){

						Road[t][0][k] = ' ';

				}	
	


							int Road_Signal_Position = atoi(Default[6].c_str());

			//	cout << Road_Signal_Position << endl;
			for (int i=1; i<Road_Width + 3 ; i++){
		
				//cout << i << endl;
		
				for(int j=0; j<Road_Length; j++){

				//	cout << j << endl;
			
					if (i==1) Road[t][i][j] = '-';
			

					else if (i==Road_Width+2) Road[t][i][j] = '-';
					else Road[t][i][j] =' '; 
			
				}
		
		
			}
			
			
		}
	
	
	
}




int findLane(int** laneInfo, int lanes, int vehAmount, int Road_Length){
	
	int ZeroLine = vehAmount - Road_Length - 1; 
	
	int randomLane = rand()%lanes ;
	
	int tempLane = randomLane;
	
	int counter = 1;
	
	while(laneInfo[tempLane][ZeroLine] != 0){
		
		
		
		tempLane = tempLane + 1;
		counter = counter + 1;
		
		if(tempLane == lanes) tempLane=0;
		
		
		if(counter == lanes) {
			
			ZeroLine = ZeroLine -1;
			counter = 1;
			tempLane = randomLane;
		}
		
		if(ZeroLine<0) {cout << "Too many vehicles initiated at once! Please change the configuration file"; return -1;}
		
		
	}
	
	return tempLane;
	
}

int findZeroLine(int** laneInfo, int lanes, int vehAmount, int Road_Length)
{
	int ZeroLine = vehAmount - Road_Length - 1; 
	
	
	int randomLane = rand()%lanes ;
	
	int tempLane = randomLane;
	
	int counter = 1;
	
	while(laneInfo[tempLane][ZeroLine] != 0){
		
		
		
		tempLane = tempLane + 1;
		counter = counter + 1;
		
		if(tempLane == lanes) tempLane=0;
		
		
		if(counter == lanes) {
			
			ZeroLine = ZeroLine -1;
			counter = 1;
			tempLane = randomLane;
		}
		
		if(ZeroLine<0) {cout << "Too many vehicles initiated at once! Please change the configuration file"; return -1;}
		
		
	}
	
	return ZeroLine;
	
	
}


int findEmptyIndex(int randomLane, int** laneCarIndex){
	
	int ans=0;
	while((laneCarIndex[randomLane][ans]!=0) && (ans<10)){ans++;}
	
	if(ans==10) cout << "Too many Vehicles are there in the same lane. OVERLOAD!";
	
	return ans;
}
	
int findRandomInLane(int randomLane, int lanes, char*** Road, int Road_Width, int PosX,  string* Vehicle, string VehicleInside, int len, string* Vehicle_Width){
	
	if(randomLane==lanes-1) {
		
		int end = Road_Width - 1;
		int start = randomLane* (Road_Width/lanes);

        
		return end;
		
	}
	
	else{
		
		int start = randomLane * (Road_Width/lanes);
		int end = start + (Road_Width/lanes) -1;
		
		
        return end;
		
	}
	
	
}
	
	
int Initiate (int index, char*** Road, char* ColorInside, string* VehicleInside, int layer, int** laneInfo, int lanes, int vehAmount, int* PosX, int* PosY, int Road_Width, int Road_Length, int len, string* Vehicle,int* Vel, int* Vf,int* Acc, int* Retard, int* LaneChange, int** laneCarIndex, string* Vehicle_MaxSpeed, string* Vehicle_Acceleration,string* Vehicle_Break,string* Vehicle_LaneChange, string* Vehicle_Length, string* Vehicle_Width;int* flag){

  if(strcmp("Human", VehicleInside[index].c_str()) != 0)		// NOT a human
	{	
 		int VehIndex = findIndexOfStr(Vehicle, VehicleInside[index], len);
		
		int randomLane = findLane(laneInfo,lanes,vehAmount, Road_Length);
		int zeroLine = findZeroLine(laneInfo, lanes, vehAmount, Road_Length);
		
		if(randomLane == -1) return -1;
		
		
		int RandomlyGenVel = (rand() % (atoi(Vehicle_MaxSpeed[VehIndex].c_str()))) + 1;
		int RandomlyGenAcc = (rand() % (atoi(Vehicle_Acceleration[VehIndex].c_str()))) + 1;
		int RandomlyGenLC = (rand() % (atoi(Vehicle_LaneChange[VehIndex].c_str()))) + 1;
		int RandomlyGenRet = (rand() % (atoi(Vehicle_Break[VehIndex].c_str()))) + 1;
		
		Vel[index] = RandomlyGenVel;
		Acc[index] = RandomlyGenAcc;
		Retard[index] = RandomlyGenRet;
		LaneChange[index] = RandomlyGenLC;
		Vf[index] = RandomlyGenVel;
		
		for(int i= zeroLine; i > zeroLine - atoi(Vehicle_Length[VehIndex].c_str()); i--){laneInfo[randomLane][i] = 1;}	//Occupied
		
		if(flag==1)
		{PosX[index] = zeroLine - (vehAmount - Road_Length - 1) -1;}
		else 
			PosX[index]
		PosY[index] = findRandomInLane(randomLane, lanes, Road, Road_Width, PosX[index], Vehicle, VehicleInside[index], len, Vehicle_Width);
		
	    int emptyIndex = findEmptyIndex(randomLane, laneCarIndex);
		
		if (emptyIndex==10) return -1;
		
		laneCarIndex[randomLane][emptyIndex] = index;
		
    	return zeroLine;
		
	}
	
   else{
	   
	   // TO DO: Humans
	   
   }
}


	
	
// COMMENT: Just to see if there's nothing on the road or not
	
bool isEmpty(char*** Road, int length, int width, int time){
		
			
		
		for(int i=0; i<length; i++){
			
			for(int j=2; j<width-1; j++){
				
				if(Road[time][i][j]!=' ') return false;
			}
			
		}
		
		return true;
	}

// COMMENT: To print the contents of the road as per the time scale. While checking the code, please add a timestep for this after the END.
	
void printArray (char*** Road, int Road_Length, int Road_Width, int t){
		
		for(int i=0; i<Road_Width + 3; i++){
			
			for(int j=0; j< Road_Length;j++){
				
				cout << Road[t][i][j];
				
			}
			
			cout << '\n';
			
		}
		
		
	}
	




int main()
{
	string Default[11]; 
    // string Road_Id;0
    // string Road_Length;1
    // string Road_Width;  2
    // string Road_Signal;3
    // string Road_Yellow;4
    // string Road_Zebra_Width; 5
    // string Road_Signal_Position;6
    // string Default_LaneChange;7
    // string Default_Acceleration;8
    // string Total_Time;9
    // string Total_Vehicles_on_road;10 .
    
    int count =0;
	
	// COMMENT: Variables for the code
	
	bool justAfterStart = false; 	//COMMENT
	bool RG = false;		//COMMENT: false for Red and true for Green
	int Start_Time = 0; //COMMENT

	int t = 0;		//COMMENT

	
	
	ifstream inFile;
	inFile.open("otherConfig.txt");

//cout<<"1"<<endl;
	if (!inFile.is_open()) 
	{
		cout<<"file doesn't open"<<endl;
		return 0 ;
	}

	int value;
	string word;
	//this loop reads all the default values
	while((inFile >> word) && count<11)
	{
		while(word[0] == '#') //always define a comment between 2 #
		{
			inFile>>word;
			while(word!="#")
				inFile>>word;
			inFile>>word;
		}

		
		inFile>>word;
		if(word=="=")
		{
			inFile>>word;
			Default[count] = word;
		//cout<<word<<endl;
			count++;
		}
	}


	//COMMENT - Instead of total vehicles as part of default I have read it separately as NumbVehicles
	//read the number of types of vehicles to be used 
	int n=0;
		//cout<<"hi1 \n";
	//inFile>>word;
	while(word[0] == '#')
	{
		inFile>>word;
		while(word!="#")
			inFile>>word;
		inFile>>word;
	}
			//cout<<"hi2 \n";

	//cout<<"hi \n";
	inFile>>word;
	//cout<<word<<endl;
	inFile>>n;
	
	// ERROR: Correct this........ Anyways it's a better generic form to use 'n' for the number of type of Vehicles available. But I also need the total Number of Vehicles as I stated in the whatsapp chat. So add one accordingly.

   // COMMENT I m changing the value of n to fit the given problem
	n=9;


	string Vehicle[n];
    string Vehicle_Length[n];
    string Vehicle_Width[n];
    string Vehicle_MaxSpeed[n];
    string Vehicle_Acceleration[n];
    string Vehicle_Break[n];
    string Vehicle_LaneChange[n];

    count=0;
    string word1, word2;

    //loop to read all the n types of vehicles
    while((inFile >> word) && count<n)
	{
		//cout<<word<<endl;
		while(word[0] == '#')
		{
			inFile>>word;
			while(word!="#")
				inFile>>word;
			inFile>>word;
		}

		if(word == "Vehicle_Type")
		{
			inFile>>word;
				if(word=="=")
				{
					inFile>>word;
					Vehicle[count] = word;
		//cout<<word<<endl;
				}
		}
		else {cout<<"Error in defining vehicles \n"; return 0;}

		inFile>>word;
		while(word[0] == '#')
		{
			inFile>>word;
			while(word!="#")
				inFile>>word;
			inFile>>word;
		}
		word1=word;
		
		//cout<<word1<<endl;
		inFile>>word2;
		if(word1=="Vehicle_Length" && word2=="=")
		{
			inFile>>word;
			Vehicle_Length[count] = word;
		

		//cout<<"Vehicle_Length "<<word<<endl;
		}
		else {cout<<"Error in defining vehicles "<<count<<endl; return 0;}

		inFile>>word;
		while(word[0] == '#')
		{
			inFile>>word;
			while(word!="#")
				inFile>>word;
			inFile>>word;
		}
		word1=word;
		inFile>>word2;
		if(word1=="Vehicle_Width" && word2=="=")
		{
			inFile>>word;
			Vehicle_Width[count] = word;
		//cout<<"Vehicle_Width "<<word<<endl;
		}
		else {cout<<"Error in defining vehicles "<<count<<endl; return 0;}

		inFile>>word;
		while(word[0] == '#')
		{
			inFile>>word;
			while(word!="#")
				inFile>>word;
			inFile>>word;
		}
		word1=word;
		inFile>>word2;
		if(word1=="Vehicle_MaxSpeed" && word2=="=")
		{
			inFile>>word;
			Vehicle_MaxSpeed[count] = word;
		//	cout<<"Vehicle_MaxSpeed "<<word<<endl;

		}
		else {cout<<"Error in defining vehicles "<<count<<endl; return 0;}

		inFile>>word;
		while(word[0] == '#')
		{
			inFile>>word;
			while(word!="#")
				inFile>>word;
			inFile>>word;
		}
		word1=word;
		inFile>>word2;
		if(word1=="Vehicle_Acceleration" && word2=="=")
		{
			inFile>>word;
			Vehicle_Acceleration[count] = word;
			//	cout<<"Vehicle_Acceleration "<<word<<endl;

		}
		else {cout<<"Error in defining vehicles "<<count<<endl; return 0;}
	
		inFile>>word;
		while(word[0] == '#')
		{
			inFile>>word;
			while(word!="#")
				inFile>>word;
			inFile>>word;
		}
		word1=word;
		inFile>>word2;
		if(word1=="Vehicle_Break" && word2=="=")
		{
			inFile>>word;
			Vehicle_Break[count] = word;
				//	cout<<"Vehicle_Break "<<word<<endl;

		}
		else {cout<<"Error in defining vehicles "<<count<<endl; return 0;}

		inFile>>word;
		while(word[0] == '#')
		{
			inFile>>word;
			while(word!="#")
				inFile>>word;
			inFile>>word;
		}
		word1=word;
		inFile>>word2;
		if(word1=="Vehicle_LaneChange" && word2=="=")
		{
			inFile>>word;
			Vehicle_LaneChange[count] = word;
	//	cout<<"Vehicle_LaneChange "<<word<<endl;
		}
		else {cout<<"Error in defining vehicles  "<<count<<endl; return 0;}

		count++;
	}

	//now the next token should be START
	//inFile>>word;
	while(word[0] == '#')
	{
		inFile>>word;
		while(word!="#")
			inFile>>word;
		inFile>>word;
	}
	if(word!="START")
	{
		cout<<"START expected "<<endl; return 0;
	}

	//now we input the vehicles
	

		ofstream myfile;
		  myfile.open ("opengl.txt");
		  myfile<<"Vehicle_Length \n";
		    for(int i=0; i<n; i++)
  				myfile << atoi(Vehicle_Length[i].c_str())<<endl;;
		  
		  myfile<<"Vehicle_Width \n";
		    for(int i=0; i<n; i++)
  				myfile << atoi(Vehicle_Width[i].c_str())<<endl;;
    // COMMENT: "Start" code...
	
     int Road_Length = atoi(Default[1].c_str());
	int Road_Width = atoi(Default[2].c_str());
	int Total_Time = atoi(Default[9].c_str());
	
	int Road_Signal_Position = atoi(Default[6].c_str());
	
   if(Road_Signal_Position > Road_Length)  {cout<< "Representational ERROR. Please change the width, length, or the Duration"; return 0; } 
	
	
	
	// COMMENT: Defining the default road: FOR RED LIGHT
	
	char ***Road;
	Road = (char***)malloc(sizeof(char**)*Total_Time);
	for(int i =0; i<Total_Time; i++)
	{
		Road[i] = (char**)malloc(sizeof(char*)*Road_Length);
	}

	for(int i =0; i<Total_Time; i++)
	{
		for(int j =0; j<Road_Length; j++)
			Road[i][j] = (char*)malloc(sizeof(char)*(Road_Width+3));
	}


	
	// COMMENT : Something like this
	
	
	// TIME 5 LEFT 25
	//----------------
	//         |   |  
	//         |   |
	//         |   |
	//----------------

				char *str1 ;
				str1 = (char*)malloc(sizeof(char)*33);

   
			     itoa((atoi(Default[9].c_str())),str1,10);
				 
				char *str2 ;
				str2 = (char*)malloc(sizeof(char)*33);
			     itoa((atoi(Default[3].c_str())),str2,10);
						

				string timeStr;

				timeStr.append("TIME ");
				timeStr.append(str1);
				timeStr.append(" LEFT ");
				timeStr.append(str2);
				timeStr.append(" ");

			//	cout << timeStr << "||||||||||||||||||||||||||||||||||||||||||| \n";
		//		cout << Default[1] << '\n';

/////////////////////////////////////////////////////////////////////				////////////////////////////////////////////////////////////////////////////
  

	if(timeStr.length() > Road_Length) { cout << "Representational ERROR. Please change the width, length, or the Duration";  return 0; }
	
    
    	 justAfterStart = true;
		//cout<<"7 \n";												  	//The vehicles inside the Road
	 // cout<<(atoi(Default[10].c_str())+1);
	  char *ColorInside;
	  ColorInside = (char*)malloc(sizeof(char)*(atoi(Default[10].c_str())+1));
	  int Colorsize = atoi(Default[10].c_str())+1;
	///////////////////////////////////////////////////////////////////////////////////////////////
		for(int i=0; i<Colorsize; i++){
			ColorInside[i] = ' ';
		}
	  
	  bool isOvertaking[atoi(Default[10].c_str())+1];	//For the Overtaking state

		for(int i=0; i<Colorsize; i++){
			isOvertaking[i] = false;
		}
	
	int shreya = atoi(Default[10].c_str())+1;
	  int PositX[atoi(Default[10].c_str())+1];  //Bottom right corner of the Vehicle
	  for(int i=0; i<shreya; i++)
	  	PositX[i] = -1000;
	  int PositY[atoi(Default[10].c_str())+1];  //Bottom right corner of the Vehicle
	  	for(int i=0; i<shreya; i++)
	  	PositY[i] = -1000;
      int Vel[atoi(Default[10].c_str())+1];
	  int Vf[atoi(Default[10].c_str())+1];
	  
	  int overtakeLayer[atoi(Default[10].c_str())+1];
  
	  for(int i=0; i<Colorsize; i++){
		  overtakeLayer[i] = -1;
	  }
	  
	  int *Acc;
	  Acc = (int*)malloc(sizeof(int)*(atoi(Default[10].c_str())+1));
	  int *Retard;
	  Retard = (int*)malloc(sizeof(int)*(atoi(Default[10].c_str())+1));
	  int *LaneChange;
	  LaneChange= (int*)malloc(sizeof(int)*(atoi(Default[10].c_str())+1));

	  for(int i=0; i<Colorsize; i++){
			LaneChange[i] = 0;
		}
	  
	  
	  string VehicleInside[atoi(Default[10].c_str()) + 1];
	  
	  for(int i=0; i< Colorsize; i++){

	  		VehicleInside[i] = " ";

	  }

/////////////////////////////////////
	  int carIndex=1;
	  
	  // For the lane system
	  if(Road_Width % 4 != 0) {return }
	  int lanes = (Road_Width>4)? (Road_Width/4) : (1);
	  
	  int vehAmount = floor(1.5 * Road_Length);
	 
	  int **laneInfo;
	  laneInfo = (int**)malloc(sizeof(int*)*lanes);
	  for(int i=0 ; i<lanes; i++)
	  {
	  	laneInfo[i] = (int*)malloc(sizeof(int)*(vehAmount+1));
	  }
	  
	  for(int i =0; i < lanes; i++){
		  for(int j =0; j< vehAmount+1; j++){
			  laneInfo[i][j] = 0;
		  }
	  }
	  
	 
	  int **laneCarIndex;  // assuming that only 10 cars at max in a lane.
	  laneCarIndex= (int**)malloc(sizeof(int*)*lanes);

	  for(int i=0;i<lanes; i++)
	  {
	  	laneCarIndex[i] = (int*)malloc(sizeof(int)*10);
	  }
	  for(int i =0; i < lanes; i++){
		  for(int j =0; j< 10; j++){
			  laneCarIndex[i][j] = 0;
		  }
	  }
	  
	  int laneStopPosition[lanes];
	  int *flag=0;

      for(int i=0; i<lanes; i++){
		  
		  laneStopPosition[i] = atoi(Default[6].c_str());
		  //cout << laneStopPosition[i] <<
	  }	  
	//to read the input of the big vehiclers initially near the zebra   
	   inFile>>word;
	while(word[0] == '#')
	{
		inFile>>word;
		while(word!="#")
			inFile>>word;
		inFile>>word;
	}
	while(word != "Signal")
	{
	
		VehicleInside[carIndex] = word;
		inFile>>word;
		ColorInside[carIndex] = word[0];
		inFile>>word;

		int layer= Initiate(carIndex, Road, ColorInside, VehicleInside, layer, laneInfo, lanes, vehAmount, PositX, PositY, Road_Width, Road_Length,n, Vehicle,  Vel,Vf, Acc, Retard, LaneChange, laneCarIndex, Vehicle_MaxSpeed, Vehicle_Acceleration, Vehicle_Break, Vehicle_LaneChange, Vehicle_Length, Vehicle_Width,flag);
		carIndex++;			
		while(word[0] == '#')
		{
			inFile>>word;
			while(word!="#")
				inFile>>word;
			inFile>>word;
		}
	}
	 
     //next token should define signal state
	if(word!="Signal")
	{
		cout<<"Signal expected "<<endl; return 0;
	}
	inFile>>word; 
	//cout<<word;
	flag = 1;
	if(word!="GREEN" && word!="RED")
		{
		cout<<"wrong signal "<<endl; return 0;
	}
	string signal_state = word;
	int int_Start_Time;
	inFile>>word;
	while(word[0] == '#')
	{
		inFile>>word;
		while(word!="#")
			inFile>>word;
		inFile>>word;
	}
	if(word =="Start_Time")
	{
		inFile>>word;
		inFile>>value;
		int_Start_Time = value;
	}
	else int_Start_Time = 0;
//cout<<int_Start_Time<<endl;

	// For storing the start time
	  int startTime[atoi(Default[10].c_str())+1];
	  
	  for(int i=0; i<Colorsize; i++){
			startTime[i] = int_Start_Time;
		}
	
		t = int_Start_Time;
    // COMMENT: CODE initialization for RED and GREEN... 
   
    if(signal_state=="Red"){
		
		 RG = false;
	}
   
    else{
		RG = true;
	}
   
	
	inFile>>word;
	while(word != "END")
	{
		//i++;
		while(word!="Pass" && word!="END")
		{
			while(word[0] == '#')
				{
					inFile>>word;
					while(word[word.length()-1]!='#')
						inFile>>word;
					inFile>>word;
				}
			//c[count][i][0] = word;  //stores the type of vehicle
			
			if(carIndex > atoi(Default[10].c_str())){ cout<< "Improper value of maximum number of cars inside. Please check the configuration file"; return 0;}
			
			else{
			VehicleInside[carIndex] =  word;  //COMMENT
			
			//cout<<word<<" "<<carIndex<<endl;
			inFile>>word;
			
			//c[count][i][1] = word;  //stores the colour of it
		
		     ColorInside[carIndex] = word[0];   //COMMENT: Add the first character of 'word' instead of 'G'
			//	cout<<ColorInside[carIndex] <<endl;;
		      // call
				//cout<<carIndex<<endl;;
		     int layer= Initiate(carIndex, Road, ColorInside, VehicleInside, layer, laneInfo, lanes, vehAmount, PositX, PositY, Road_Width, Road_Length,n, Vehicle,  Vel,Vf, Acc, Retard, LaneChange, laneCarIndex, Vehicle_MaxSpeed, Vehicle_Acceleration, Vehicle_Break, Vehicle_LaneChange, Vehicle_Length, Vehicle_Width;flag);
			  
		     	// Debugginh

		     	for(int i=0; i< lanes; i++){

		     		for(int j=0; j< 10; j++){

		     	//		cout << laneCarIndex[i][j] << " ";

		     		}

		     	//	cout << endl;

		     	}



		     	//cout << PositX[carIndex ] << endl;

			   if(layer==-1) {return 0;}
			  
			   carIndex++;
			
		//	i++;
			inFile>>word;
			while(word[0] == '#')
				{
					inFile>>word;
					while(word[word.length()-1]!='#')
						inFile>>word;
					inFile>>word;
				}
			//cout<<"word "<<word<<endl;
			}
		
		}
		
	
		  
		if(word!="END")	//PASS reached
			{inFile>>value;
			//cout<<value<<endl;
				int tempCheck;

			int passingTime;
			passingTime = value;
			
			//cout<<value<<endl;
			for(int i=0; i<passingTime;i++){
			
			// call
			
                makeBasicRoad(Road,t, int_Start_Time, RG, Road_Width, Road_Length,Default);
			
               // cout << "time is " << t << endl;
				for(int p=0; p< lanes; p++){
					
					for(int j=0; j<10; j++){
					
					if (laneCarIndex[p][j] == 0) break;
					
				 // call	
					
					tempCheck = positionUpdate(laneCarIndex[p][j],Vel,Vf, Acc,Retard,LaneChange,Road,t, startTime,PositX, PositY , ColorInside, VehicleInside, RG,laneCarIndex, laneInfo, lanes, Road_Length, Road_Width, Vehicle, Vehicle_Length, Vehicle_Width, n, isOvertaking, Vehicle_LaneChange, overtakeLayer, vehAmount, Default, laneStopPosition);
					if(tempCheck==-1) return 0;
					
					//cout << "Xcoord of " << laneCarIndex[p][j] << " is " << PositX[laneCarIndex[p][j]];

					}
				}
				

                 printArray(Road, Road_Length, Road_Width, t);
					cout << '\n';

					myfile<<t<<endl;
					myfile<<"PositX \n";
					for(int i=1; i<shreya+1; i++)
					{
						myfile << PositX[i]<<endl;
					}
					myfile<<endl;
					myfile<<"PositY \n";
					for(int i=1; i<shreya+1; i++)
					{
						myfile << PositY[i]<<endl;
					}
					myfile<<"Type Index \n";
					for(int i=1; i<shreya+1; i++)
					{
						myfile << findIndexOfStr(Vehicle, VehicleInside[i],n)<<endl;
					}  
					 

				t=t+1;
				
				if(t%(atoi(Default[3].c_str()))==0) RG = !RG;
				//cout<<RG<<endl;
				if(t>=Total_Time) {cout<< "Improper timings!" <<'\n'; return 0;}
				
			}
		
			if(word=="END") break;
			inFile>>word;
			//cout<<word<<endl;
		}
	}

  // COMMENT: Terminated while loop. SO EOF reached.
		//xRG=true;
		if(RG){				//COMMENT: The signal is green when stopped and so all the vehicles must be allowed to clear the road OR until there's a RED light

							int tempCheck;

			// call
//cout<<"hi \n";
				while((!isEmpty(Road,Road_Length,Road_Width, t)) &&  (RG)){
					
						// call
	                        makeBasicRoad(Road,t, int_Start_Time, RG, Road_Width, Road_Length, Default);

					
					 		for(int p=0; p< lanes; p++){
					
								for(int j=0; j<10; j++){
								
									if (laneCarIndex[p][j]==0) break;
									// call
									tempCheck = positionUpdate(laneCarIndex[p][j],Vel,Vf, Acc,Retard,LaneChange,Road,t, startTime,PositX, PositY , ColorInside, VehicleInside, RG,laneCarIndex, laneInfo, lanes, Road_Length, Road_Width, Vehicle, Vehicle_Length, Vehicle_Width, n, isOvertaking, Vehicle_LaneChange, overtakeLayer, vehAmount, Default, laneStopPosition);
									if(tempCheck==-1) return 0;
				
								}
							}
				
							 printArray(Road, Road_Length, Road_Width, t);
							cout << '\n';

							myfile<<t<<endl;
							myfile<<"PositX \n";
							for(int i=1; i<shreya+1; i++)
							{
								myfile <<PositX[i]<<endl;
							}
							myfile<<endl;
							myfile<<"PositY \n";
							for(int i=1; i<shreya+1; i++)
							{
								myfile << PositY[i]<<endl;
							}

							myfile<<"Type Index \n";
						for(int i=1; i<shreya+1; i++)
						{
							myfile << findIndexOfStr(Vehicle, VehicleInside[i],n)<<endl;
						}  
					

							t=t+1;
				
							if(t%(atoi(Default[3].c_str()))==0) RG = !RG;
		
							if(t>=Total_Time) {cout<< "Improper timings!" <<'\n'; return 0;}
					
				}
				
			myfile.close();
		}
		
		
    return 0;

}
