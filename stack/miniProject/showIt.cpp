//============================================================================
// Name        : TraceIt2.cpp
// Author      : vvaibhav3
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <GL/freeglut.h>
#include <GL/gl.h>
#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;

fstream file;
int left1=100,right1=180,top1=600,bottom1=640,x_text=left1+20,y_text=top1-20,boxes=0,initial_top=600,initial_bottom=640;
int i=0,count=0,hd1=0,xmax,ymax,ai=0,si=0,lines=0,wd=9,st=0,prevVal=-1,currentVal=0,factor=180;
char ch,temp[1000],type;
struct holdData{
	int arrayFlag,stackFlag,queueFalg,usize,top;
	char name[30],type[10],size[5],value[10],ptrP[100],ptrP_Val[10],mesg[10];
	char arrValues[10][10],arrIndex[10][10],vars[10][10],varsValues[10][10];
}hold1[10];

//to display text
void showMesg(int x,int y,int id){
	int k=0,len=0;
	glRasterPos2f(x,y);
	len=strlen(hold1[id].mesg);
	while(k<=len){
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,hold1[id].mesg[k]);
		k++;
	}
}

//to display text
void showVarName(int x,int y,int id){
	int k=0,len=0;
	glRasterPos2f(x,y);
	len=strlen(hold1[id].name);
	while(k<=len){
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,hold1[id].name[k]);
		k++;
	}
}

//to display text
void showVarValue(int x,int y,int id){
	int k=0,len=0;
	glRasterPos2f(x,y);
	len=strlen(hold1[id].value);
	while(k<=len){
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,hold1[id].value[k]);
		k++;
	}
}

//to display text
void showVarType(int x,int y,int id){
	int k=0,len=0;
	glRasterPos2f(x,y);
	len=strlen(hold1[id].type);
	while(k<=len){
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,hold1[id].type[k]);
		k++;
	}
}

//to display text
void showVarPtrP(int x,int y,int id){
	int k=0,len=0;
	glRasterPos2f(x,y);
	cout<<hold1[id].ptrP<<endl;
	len=strlen(hold1[id].ptrP);
	while(k<=len){
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,hold1[id].ptrP[k]);
		k++;
	}
}

//to display text
void showVarPtrP_Val(int x,int y,int id){
	int k=0,len=0;
	glRasterPos2f(x,y);
	cout<<hold1[id].ptrP_Val<<endl;
	len=strlen(hold1[id].ptrP_Val);
	while(k<=len){
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,hold1[id].ptrP_Val[k]);
		k++;
	}
}

void drawRec(int l,int r,int t,int b){
	glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
	glBegin(GL_POLYGON);
		glVertex2i(l,t);
		glVertex2i(r,t);
		glVertex2i(r,b);
		glVertex2i(l,b);
	glEnd();
}
//function to remove space ,tab and \n character from preceding
void removeSTN(char data[]){
	int i=0,j=0;
	//printf("\n data before : %s done...\n",data);

	while(data[i]==' ' || data[i]=='\n' || data[i]=='	'){
		i+=1;
	}
	printf("\ni :- %d\n",i);
	if(i>0){
	while(data[j]!='\0'){
		data[j]=data[i];
		i++;
		j++;
	}
	}
	//printf("\n data after : %s done...\n",data);
}

//function to find data type of variables
char getType(char data[])
{
	//cout<<"@in get type function...\n";
	if(strcmp(data,"char")==0)
	{
		return 'c';
	}
	else if(strcmp(data,"int")==0)
	{
		return 'd';
	}
	else if(strcmp(data,"float")==0)
	{
		return 'f';
	}
	else if(strcmp(data,"pointer")==0)
	{
		return 'p';
	}
	else if(strcmp(data,"array")==0)
	{
		return 'a';
	}
	else if(strcmp(data,"stack")==0)
	{
		return 's';
	}
	else if(strcmp(data,"initial")==0)
	{
		return 'i';
	}
	else{
		return '~';
	}
}


int checkVar(){
int k=0;
	while(k<=hd1){
		if(strcmp(hold1[k].name,temp)==0){
			return k;
		}
		k++;
	}
	return hd1+1;
}

int checkUVar(){
int k=0;
	while(k<=hold1[st].stackFlag){
		if(strcmp(hold1[st].vars[k],temp)==0){
			return k;
		}
		k++;
	}
	return hold1[st].stackFlag+1;
}

void storeVarType(int j,char ch1){
	switch(ch1){

	case 'c': strcpy(hold1[j].type,"char");
			break;

	case 'd': strcpy(hold1[j].type,"int");
			break;

	case 'f': strcpy(hold1[j].type,"float");
			break;

	case 'p': strcpy(hold1[j].type,"pointer");
			break;

	case 'a': strcpy(hold1[j].type,"array");
			break;

	case 's': strcpy(hold1[j].type,"stack");
			break;
	}
}

void storeVarData(int j,int k){

switch(k){

case 0: storeVarType(j,type);
		strcpy(hold1[j].name,temp);
		break;

case 1: strcpy(hold1[j].value,temp);
		break;

case 2: strcpy(hold1[j].ptrP,temp);
		break;

case 3: strcpy(hold1[j].ptrP_Val,temp);
		break;
}
int ij=0;

cout<<"*******************Vars With Initial Values***************************\n";
while(ij<=hd1){
	cout<<"var : "<<hold1[ij].name<<" value : "<<hold1[ij].value<<"ptrP : "<<hold1[ij].ptrP<<"ptrPVal : "<<hold1[ij].ptrP_Val<<"done..\n";
	ij+=1;
}
}


//to display text
void showArrVal(int x,int y,int id,int ai){
	int k=0,len=0;
	glRasterPos2f(x,y);
	cout<<hold1[id].arrValues[ai]<<endl;
	len=strlen(hold1[id].arrValues[ai]);
	while(k<=len){
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,hold1[id].arrValues[ai][k]);
		k++;
	}
	glRasterPos2f(x,y-40);
	glutBitmapCharacter(GLUT_BITMAP_9_BY_15,'0'+ai);
}

//to display text
void showStackVal(int x,int y,int id,int ai){
	int k=0,len=0;
	glRasterPos2f(x,y);
	cout<<hold1[id].arrValues[ai]<<endl;
	len=strlen(hold1[id].arrValues[ai]);
	while(k<=len){
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,hold1[id].arrValues[ai][k]);
		k++;
	}
	//glRasterPos2f(x,y-40);
	//glutBitmapCharacter(GLUT_BITMAP_9_BY_15,'0'+ai);
}
//to display text
void showArrIndex(int x,int y,int id,int ai){
	int k=0,len=0;
	glRasterPos2f(x,y);
	cout<<hold1[id].arrIndex[ai]<<endl;
	len=strlen(hold1[id].arrIndex[ai]);
	while(k<=len){
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,hold1[id].arrIndex[ai][k]);
		k++;
	}

	if(strcmp(hold1[id].varsValues[1],hold1[id].arrIndex[ai])==0){
	k=0;
	x=left1-60;
	glRasterPos2f(x,y);
	cout<<"*********************************************TOP*************************************\n"<<hold1[id].vars[2]<<endl;
	len=strlen(hold1[id].vars[1]);
	while(k<=len){
		glutBitmapCharacter(GLUT_BITMAP_9_BY_15,hold1[id].vars[1][k]);
		k++;
	}
	}
}


void drawArrayRec(int arrSize,int id){
	int k=0;
	boxes=0;
	left1=100;
	right1=180;
	top1=initial_top-120;
	bottom1=initial_bottom-120;
	initial_top=top1;
	initial_bottom=bottom1;
	x_text=left1+20;
	y_text=top1-20;
	drawRec(left1,right1,top1,bottom1);
	showVarName(x_text,y_text,id);//name
	showVarValue(x_text,y_text+40,id);//value
	showVarType(x_text,y_text+65,id);//type
	boxes+=1;
	lines+=1;
	while(k!=arrSize){
	if(boxes<=wd){
		left1=right1;
		right1=left1+80;
		x_text=left1+20;
		boxes+=1;
		drawRec(left1,right1,top1,bottom1);
		//showArrIndex(x_text,y_text,id,k);//index
		showArrVal(x_text,y_text+40,id,k);//value
	}
	else{
		left1=100;
		right1=180;
		top1=initial_top-120;
		bottom1=initial_bottom-120;
		initial_top=top1;
		initial_bottom=bottom1;
		x_text=left1+20;
		y_text=top1-20;
		boxes=0;
		drawRec(left1,right1,top1,bottom1);
		//showArrIndex(x_text,y_text,id,k);//index
		showArrVal(x_text,y_text+40,id,k);//value
		left1=right1;
		right1=left1+80;
		x_text=left1+20;
		boxes+=1;
		lines+=1;
	}
		k++;
	}
}
void processPointer(int k){
	cout<<"**********************int pointer***********************";
	left1=100;
	right1=180;
	top1=initial_top-120;
	bottom1=initial_bottom-120;
	initial_top=top1;
	initial_bottom=bottom1;
	x_text=left1+20;
	y_text=top1-20;
	boxes=wd+1;
	drawRec(left1,right1+20,top1,bottom1);
	showVarName(x_text,y_text,k);
	showVarValue(x_text,y_text+40,k);
	showVarType(x_text,y_text+65,k);//type
	glBegin(GL_LINES);
		glVertex2i(right1+20,y_text+40);
		glVertex2i(right1+100,y_text+40);
	glEnd();
	drawRec(right1+100,right1+180,top1,bottom1);
	showVarPtrP(right1+120,y_text,k);
	showVarPtrP_Val(right1+120,y_text+40,k);
	lines+=1;

}

void initArray(){
	while(ch!=';'){
	file.get(ch);
	if(ch==':'){
		temp[i]='\0';
		cout<<"#temp :"<<temp<<"done..\n";
		strcpy(hold1[hd1].type,"array");
		strcpy(hold1[hd1].name,temp);
		count+=1;
		i=0;
		file.get(ch);
	}

	if(ch==';'){
		//i--;
		temp[i]='\0';
		cout<<"#temp :"<<temp<<"done..\n";
		strcpy(hold1[hd1].size,temp);
		count+=1;
		i=0;
		file.get(ch);
		break;
	}
	temp[i]=ch;
	i++;
	}
	hd1+=1;
	i=0;
}
void processArray(int k){

	cout<<"array..\n"<<ai<<endl;
	while(ch!=';'){
	file.get(ch);
	if(ch==':'){
		temp[i]='\0';
		cout<<"#temp :"<<temp<<"done..\n";
		strcpy(hold1[k].arrIndex[ai],temp);
		count+=1;
		i=0;
		file.get(ch);
	}
	if(ch==';'){
		//i--;
		temp[i]='\0';
		cout<<"##temp :"<<temp<<"done..\n";
		strcpy(hold1[k].arrValues[ai],temp);
		count+=1;
		i=0;
		file.get(ch);
		break;
	}
	temp[i]=ch;
	i++;
	}
	//getting size of array
	int ij=0,s=0;
	while(hold1[k].size[ij]!='\0'){
		s+=hold1[k].size[ij]-'0';
		ij+=1;
	}
	cout<<"size : "<<s<<endl;
	ai+=1;
	drawArrayRec(s,k);
	i=0;

}

void drawStackRec(int arrSize,int id){
	int k=1;
	boxes=0;
	//left1=100;
	//right1=180;
	top1=initial_top-(40*arrSize);
	bottom1=initial_bottom-(40*arrSize);
	//initial_top=top1;
	//initial_bottom=bottom1;
	x_text=left1+20;
	y_text=top1-20;
	drawRec(left1,right1,top1,bottom1);
	showVarName(x_text,y_text,id);//name
	showMesg(x_text,y_text-20,id);//operation name
	y_text=top1+20;
	showArrIndex(x_text+70,y_text,id,0);//index
	showStackVal(x_text,y_text,id,0);//value
	//showVarValue(x_text,y_text+40,id);//value
	//showVarType(x_text,y_text+65,id);//type
	boxes+=2;
	lines+=1;
	while(k!=arrSize){
	if(boxes<=wd){
		//left1=right1;
		//right1=left1+80;
		top1=initial_top-(40*(arrSize-k));
		bottom1=initial_bottom-(40*(arrSize-k));
		y_text=top1+20;
		boxes+=2;
		drawRec(left1,right1,top1,bottom1);
		showArrIndex(x_text+70,y_text,id,k);//index
		showStackVal(x_text,y_text,id,k);//value

	}
		k++;
	}
	left1=100+factor;
	factor+=180;
	right1=left1+80;
	//initial_top=top1;
	//initial_bottom=bottom1;
	x_text=left1+20;
	y_text=top1-20;

}

void processStack(int k){
	int ij=0,flag=0;
	cout<<"stack..\n"<<si<<endl;
	while(ch!=';'){
	file.get(ch);
	if(ch==':'){
		temp[i]='\0';
		cout<<"# stack index temp :"<<temp<<"done..\n";
		while(ij<=si){
			if(strcmp(hold1[k].arrIndex[ij],temp)==0){
				flag=1;
				break;
			}
			ij++;
		}
		if(flag==1){
			si-=1;
			cout<<" duplicate  : "<<hold1[k].arrIndex[ij]<<endl;
			hold1[k].arrIndex[ij][0]='\0';
			strcpy(hold1[k].varsValues[1],hold1[k].arrIndex[ij-1]);
		}
		else{
			strcpy(hold1[k].arrIndex[si],temp);
		}
		//count+=1;
		i=0;
		file.get(ch);
	}
	if(ch==';'){
		//i--;
		temp[i]='\0';
		cout<<"##stack value temp :"<<temp<<"done..\n";
		if(flag==1){
			si-=1;
			hold1[k].arrValues[ij][0]='\0';
			strcpy(hold1[st].mesg,"-pop");
			flag=0;
		}
		else{
			strcpy(hold1[k].arrValues[si],temp);
			strcpy(hold1[st].mesg,"-push");
		}
		//count+=1;
		i=0;
		file.get(ch);
		break;
	}
	temp[i]=ch;
	i++;
	}
	drawStackRec(hold1[st].usize,st);
	ij=0;
	//int ij=0;
	cout<<"****************stack*********************\n";
	cout<<"name : "<<hold1[k].name<<endl;
	while(ij<=si){
		cout<<" i : "<<hold1[k].arrIndex[ij]<<" value : "<<hold1[k].arrValues[ij]<<endl;
		ij+=1;
	}
	si+=1;
	//drawArrayRec(s,k);
	i=0;

}

void initStack(){
	hold1[hd1].stackFlag=0;
	while(ch!=';'){
	file.get(ch);
	if(ch==':'){
		temp[i]='\0';
		i=0;
		cout<<":@@@@@@@@temp :"<<temp<<"done..\n";
		file.get(ch);
	}
	if(ch==','){
		temp[i]='\0';
		cout<<"@@@@@@@@temp :"<<temp<<"done..\n";
		if(count==0){
			strcpy(hold1[hd1].type,"stack");
			strcpy(hold1[hd1].name,temp);
		}
		else{
			strcpy(hold1[hd1].vars[hold1[hd1].stackFlag],temp);
			hold1[hd1].stackFlag+=1;
		}
		count+=1;
		i=0;
		file.get(ch);
	}

	if(ch==';'){
		//i--;
		temp[i]='\0';
		cout<<";@@@@@@@@@temp :"<<temp<<"done..\n";
		strcpy(hold1[hd1].vars[hold1[hd1].stackFlag],temp);
		count+=1;
		i=0;
		file.get(ch);
		break;
	}
	temp[i]=ch;
	i++;
	}

	int ij=0;
	cout<<"****************stack*********************\n";
	cout<<"name : "<<hold1[hd1].name<<endl;
	while(ij<=hold1[hd1].stackFlag){
		cout<<hold1[hd1].vars[ij]<<endl;
		ij+=1;
	}
	st=hd1;
	hd1+=1;
	i=0;
}

void processInit(){
	int ij=0,count=0;
	i=0;
	while(ch!=';'){
	file.get(ch);
	if(ch==':'){
		temp[i]='\0';
		cout<<"init : temp : "<<temp<<"done..\n";
		file.get(ch);
		//after initial

		while(ij<=hold1[st].stackFlag){
			if(strcmp(hold1[st].vars[ij],temp)==0){
				cout<<"vars found...."<<ij<<endl;
				break;
			}
			ij+=1;
		}
		i=0;
	}
	if(ch==','){
		temp[i]='\0';
		strcpy(hold1[st].varsValues[ij],temp);
		if(count==0){
			strcpy(hold1[st].size,temp);
			count+=1;
		}
		i=0;
		file.get(ch);
	}
	if(ch==';'){
			//i--;
			temp[i]='\0';
			strcpy(hold1[st].mesg,"-initial");
			cout<<";@@@@@@@@@temp :"<<temp<<"done..\n";
			strcpy(hold1[st].varsValues[ij],temp);
			count+=1;
			i=0;
			file.get(ch);
			break;
	}
	temp[i]=ch;
	i++;
	}
	int s=0;
	ij=0;
		while(hold1[st].size[ij]!='\0'){
			s+=hold1[st].size[ij]-'0';
			ij+=1;
		}
		cout<<"size : "<<s<<endl;
		drawStackRec(s,st);
		hold1[st].usize=s;
	ij=0;
	cout<<"****************stack with initial values*********************\n";
	cout<<"name : "<<hold1[st].name<<"size : "<<hold1[st].size<<endl;
	while(ij<=hold1[st].stackFlag){
		cout<<"vars: "<<hold1[st].vars[ij]<<" value : "<<hold1[st].varsValues[ij]<<endl;
		ij+=1;
	}
	i=0;
}
void renderFunction(){

	glClearColor(0, 0, 0, 0);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.f, 0.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    xmax=glutGet(GLUT_WINDOW_WIDTH);
	ymax=glutGet(GLUT_WINDOW_HEIGHT);
	gluOrtho2D(0,xmax,0,ymax);
	file.open("./output.txt");

	//drawRec(left1,right1,top1,bottom1);
	//drawRec(100,160,100,130);
	//showVarName(x_text,y_text);

	while(!file.eof()){

		file.get(ch);
		if(ch!=':' && ch!=';'){
			temp[i]=ch;
			i++;
		}
		else if(ch==':'){
			temp[i]='\0';
			//removeSTN(temp);
			cout<<":@temp before :"<<temp<<"done...\n";
			type=getType(temp);
			i=0;
			if(type!='~'){

				if(type=='a'){
					initArray();
				}
				else if(type=='s'){
					initStack();
				}
				else if(type=='i'){
					processInit();
				}
				else{
					//process varaiables
				while(ch!=';'){
					file.get(ch);
					if(ch==':'){
						temp[i]='\0';
						cout<<"#temp :"<<temp<<"done..\n";
						storeVarData(hd1,count);
						count+=1;
						i=0;
						file.get(ch);
					}

					if(ch==';'){
						//i--;
						temp[i]='\0';
						cout<<"#temp :"<<temp<<"done..\n";
						storeVarData(hd1,count);
						count+=1;
						i=0;
						file.get(ch);
						break;
					}
					temp[i]=ch;
					i++;
				}
				if(count>1){
					if(boxes<=wd){
						drawRec(left1,right1,top1,bottom1);
						showVarName(x_text,y_text,hd1);//name
						showVarValue(x_text,y_text+40,hd1);//value
						showVarType(x_text,y_text+65,hd1);//type
						left1+=100;
						right1+=100;
						x_text=left1+20;
						boxes+=1;
					}
					else{
						left1=100;
						right1=180;
						top1=initial_top-120;
						bottom1=initial_bottom-120;
						initial_top=top1;
						initial_bottom=bottom1;
						x_text=left1+20;
						y_text=top1-20;
						boxes=0;
						drawRec(left1,right1,top1,bottom1);
						showVarName(x_text,y_text,hd1);//name
						showVarValue(x_text,y_text+40,hd1);//value
						showVarType(x_text,y_text+65,hd1);//type
						left1+=100;
						right1+=100;
						x_text=left1+20;
						boxes+=1;
						lines+=1;
					}
				}
				cout<<"@count: "<<count<<endl;
				hd1+=1;
				}
			}
			else{ //after init
				//int k=hd1+1;
				int k=checkVar();
				if(k<=hd1){
					if(strcmp(hold1[k].type,"array")==0){
						processArray(k);
					}
					else if(strcmp(hold1[k].type,"stack")==0){
						processStack(k);
					}
					else{
					count+=1;
					cout<<"variable detected...in else part....\n"<<temp<<endl;
					while(ch!=';'){
					file.get(ch);
					if(ch==':'){
						temp[i]='\0';
						cout<<"#temp :"<<temp<<"done..\n";
						storeVarData(k,count);
						count+=1;
						i=0;
						file.get(ch);
					}

					if(ch==';'){
						//i--;
						temp[i]='\0';
						cout<<"##temp :"<<temp<<"done..\n";
						storeVarData(k,count);
						count+=1;
						i=0;
						file.get(ch);
						break;
					}
					temp[i]=ch;
					i++;
					}
					if(boxes<=7){
						if(strcmp(hold1[k].type,"pointer")==0){
							processPointer(k);
						}
						else{
							drawRec(left1,right1,top1,bottom1);
							showVarName(x_text,y_text,k);
							showVarValue(x_text,y_text+40,k);
							showVarType(x_text,y_text+65,k);//type
							left1+=100;
							right1+=100;
							x_text=left1+20;
							boxes+=1;
						}
					}else{
						if(strcmp(hold1[k].type,"pointer")==0){
							processPointer(k);
						}
						else{
							left1=100;
							right1=180;
							top1=initial_top-120;
							bottom1=initial_bottom-120;
							initial_top=top1;
							initial_bottom=bottom1;
							x_text=left1+20;
							y_text=top1-20;
							boxes=0;
							drawRec(left1,right1,top1,bottom1);
							showVarName(x_text,y_text,k);
							showVarValue(x_text,y_text+40,k);
							showVarType(x_text,y_text+65,k);//type
							left1+=100;
							right1+=100;
							x_text=left1+20;
							boxes+=1;
							lines+=1;
						}
					}
				}
				}else{
					int s1=checkUVar();
					if(s1<=hold1[st].stackFlag){
						cout<<"stack var...."<<temp<<endl;
						while(ch!=';'){
						file.get(ch);
						if(ch==':'){
							temp[i]='\0';
							cout<<"#stack temp :"<<temp<<"done..\n";
							i=0;
							file.get(ch);
						}

						if(ch==';'){
							//i--;
							temp[i]='\0';
							cout<<"##stack temp :"<<temp<<"done..\n";
							strcpy(hold1[st].varsValues[s1],temp);
							count+=1;
							i=0;
							file.get(ch);
							break;
						}
						temp[i]=ch;
						i++;
						}
						int s=0,ij=0;
								while(hold1[st].varsValues[s1][ij]!='\0'){
									s+=hold1[st].varsValues[s1][ij]-'0';
									ij+=1;
								}
								/*cout<<"Current Val : "<<s<<endl;
								if(currentVal>prevVal){
									drawStackRec(hold1[st].usize,st);
								}*/
						cout<<" new data...\n"<<hold1[st].vars[s1]<<" : "<<hold1[st].varsValues[s1]<<endl;
					}
				}
			}
			cout<<":@temp after :"<<temp<<"done...\n";
			i=0;
			count=0;
		}

	}
	glFlush();

}

int main(int argc, char** argv)
{
	//processData();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE);
	glutInitWindowSize(1366,768);
	glutInitWindowPosition(100,100);
	glutCreateWindow("OpenGL - First window demo");
	glutDisplayFunc(renderFunction);
	glutMainLoop();
	return 0;
}

/*
int:var1:20;
char:ch;
var1:50;
ch:c;
pointer:ptr1;
ptr1:0x379:var1:700;
var1:70;
ptr1:0x380:var1:900;
stack:stack1,size:MAXSIZE1,top:top1;
initial:MAXSIZE1:5,top1:-1;
top1:0;
stack1:0:13;
top1:1;
stack1:1:14;
top1:2;
stack1:2:15;
top1:3;
stack1:3:16;
top1:4;
stack1:4:17;
stack1:4:17;
top1:3;
 */

