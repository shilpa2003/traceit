//============================================================================
// Name        : Trace It.cpp
// Author      : vvaibhav3
// Version     : 1.0
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================


// C++ implementation to read
// file word by word
#include <iostream>
#include <fstream>
#include<string.h>
using namespace std;

// filestream variable file
fstream file;
ofstream file2;
struct userDefData{
	char uVar[100],uVarValue[100];
	char uType;
}uData1[10];

string vars[10],assumeData,function_names[10];
char ch,tp,temp[1000],var[100],format_specifier[100],ptr_check_flag,pointer[50][50];
int i=0,j=0,c=14,v=0,vv=0,h=0,f=0,assumeFlag=0,mainFlag=0,ud=0,fn=0,checkIndex=0;
char cmd[100]="\nfprintf(fptr,";

//function to process scanf if it occurs
void putDataIfScanf(){

	cout<<"processing scanf..\n";
	file.get(ch);
	while(ch!=','){
		format_specifier[f]=ch;
		file2.put(ch);
		file.get(ch);
		cout<<" ch : "<<ch<<endl;
		f++;
	}
	file2.put(ch);
	format_specifier[f]='\0';
	j=0;
	cout<<"format specifier : "<<format_specifier<<"done..\n";
	while(ch!=';'){
		file.get(ch);
		file2.put(ch);
		cout<<" ch : "<<ch<<endl;
		if(isalnum(ch)){
		var[j]=ch;
		j++;
		}
		if(ch==','){
			var[j]=ch;
			j++;
		}
	}
	var[j]='\0';
	file2<<"\nfputs(";
	file2.put('"');
	file2<<var<<":";
	file2.put('"');
	file2<<",fptr);\n";
	file2<<cmd<<format_specifier<<","<<var<<");"<<endl;
	file2<<"\nfprintf(fptr,";
	file2.put('"');
	file2<<";\\n";
	file2.put('"');
	file2<<");\n";


	i=0;
}

//function to remove space ,tab and \n character from preceding
void removeSTN(char data[]){
	int i=0,j=0;
	//printf("\n data before : %s done...\n",data);

	while(data[i]==' ' || data[i]=='\n' || data[i]=='	' || data[i]=='/'){
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
	else{
		return '~';
	}
}

void putDataIfMain(){

	while(ch!=')'){
		file.get(ch);
		file2.put(ch);
		temp[i]=ch;
		i++;
	}
	temp[i]='\0';
	i=0;
	file.get(ch);
	file2.put(ch);//it will put '{' file
	file.get(ch);
	file2.put(ch);// it will '\n' in file
	file2<<"\nfptr=fopen(";
	file2.put('"');
	file2<<"./output.txt";
	file2.put('"');
	file2.put(',');
	file2.put('"');
	file2<<"w+";
	file2.put('"');
	file2<<");";
	mainFlag=1;
	//putting data for user defined data type like stack , queue
	if(assumeFlag==1){
		//putting output related data
		file2<<"\nfputs(";
		file2.put('"');
		i=0;
		file2<<assumeData<<";\\n";
		file2.put('"');
		file2<<",fptr);";

		int ij=1;
		file2<<"\nfputs(";
		file2.put('"');
		file2<<"initial:";
		while(ij!=ud-1){
			file2<<uData1[ij].uVar<<":"<<uData1[ij].uVarValue<<",";
			ij+=1;
		}
		file2<<uData1[ij].uVar<<":"<<uData1[ij].uVarValue<<";\\n";
		file2.put('"');
		file2<<",fptr);";
		assumeFlag=0;
	}
	i=0;
	cout<<"\nin main function\n";
}

void processDataIfAssume(){

	i=0;
	char divideTemp[20];
	while(temp[i]!='\0'){
		if(temp[i]==':'){
			divideTemp[j]='\0';
			if(strcmp(divideTemp,"stack")==0 || strcmp(divideTemp,"queue")==0){
				cout<<"user defined data strcuture is used...\n";
				j=0;
				i+=1;//for avoiding '=' symbol
				while(temp[i]!=','){
					divideTemp[j]=temp[i];
					i++;
					j++;
				}
				divideTemp[j]='\0';
				strcpy(uData1[ud].uVar,divideTemp);
				i+=1;//for avoiding ',' symbol
				cout<<"Name1 : "<<uData1[ud].uVar<<"done..\n";
				j=0;
				ud+=1;
			}
			else if(strcmp(divideTemp,"size")==0 || strcmp(divideTemp,"top")==0 || strcmp(divideTemp,"rear")==0 || strcmp(divideTemp,"front")==0){
				cout<<"user defined data strcuture variables detected...\n";
				int tempflag=0;
				j=0;
				i+=1;//for avoiding '=' symbol
				while(temp[i]!=','){
					divideTemp[j]=temp[i];
					i++;
					j++;
					if(temp[i]=='\0'){
						divideTemp[j]='\0';
						strcpy(uData1[ud].uVar,divideTemp);
						cout<<"Name2 : "<<uData1[ud].uVar<<"done..\n";
						ud+=1;
						tempflag=1;
						break;
					}
				}
				if(tempflag==0){
				divideTemp[j]='\0';
				strcpy(uData1[ud].uVar,divideTemp);
				cout<<"Name3 : "<<uData1[ud].uVar<<"done..\n";
				ud+=1;
				i+=1;//for avoiding ',' symbol
				j=0;
				}
			}
		}
		divideTemp[j]=temp[i];
		i++;
		j++;

	}
}
//function for shifting chars
void shiftData(char data[],int k){
	int n=0;
	while(data[n]!='\0'){
		data[n]=data[k];
		n++;
		k++;
	}
}
//function to check whether there is any arithmatic symbol like + , - , * , / ..
int checkSymbol(char data[]){
	int k=0;
	v=0;
	//char ht;//hold temprary
	cout<<"\n in check symbol\n";
	removeSTN(data);
	while(data[k]!='\0'){
			cout<<"data : "<<data[k]<<endl;
			switch(data[k]){

			case '-':
			case '*':
			case '/':
			case '+':
						data[k]='\0';
						vars[v]=data;
						v+=1;
				  	  	cout<<"@@data1 : "<<data<<"done..\n";
						data[k]=' ';
						shiftData(data,k);
						cout<<"@@data1 after shifting : "<<data<<"done..\n";
						if(checkSymbol(data)){
							//cout<<"\n k : "<<data[k]<<endl;
							k=k-2;//for avoiding \n and ;
							data[k]='\0';
					  	  	cout<<"@@data2 : "<<data<<"done..\n";
						}
			  	  	  return 1;
			  	  	  break;
			}
			k++;
	}
	return 0;

}


//function to put fprintf lines
void putLine(int t,int k){
	if(t==0){
		file2<<"\nfprintf(fptr,";
		file2.put('"');
		file2<<uData1[0].uVar<<":%"<<uData1[k].uType<<":%"<<uData1[0].uType<<";\\n";
		file2.put('"');
		file2<<","<<uData1[k].uVar<<","<<uData1[0].uVar<<"["<<uData1[k].uVar<<"]);\n";
		checkIndex=0;
	}
	else{
		file2<<"\nfprintf(fptr,";
		file2.put('"');
		file2<<uData1[t].uVar<<":%"<<uData1[t].uType<<";\\n";
		file2.put('"');
		file2<<","<<uData1[t].uVar<<");\n";
	}
}

//function to find initial values variables
int getValue(){
	int max=0,flag=0,ij=0;
	while(max!=ud){
		cout<<" uData : "<<uData1[max].uVar<<"done..\n";
		if(strcmp(uData1[max].uVar,temp)==0){
			i=0;
			while(ch!=';'){
				file.get(ch);
				file2.put(ch);
				if(ch==']'){
					i++;
					flag=1;
					break;
				}
				cout<<"!ch : "<<ch<<endl;
				temp[i]=ch;
				i++;
			}
			temp[i]='\0';
			cout<<"***********Value************"<<temp<<endl;
			i--;//to avoid semicolon ';'
			if(temp[i-1]==';' || temp[i-1]==']' || temp[i-1]==' '){
				i-=1;
			}
			temp[i]='\0';

			cout<<"***********Value************"<<temp<<endl;
			i=0;
			char t1;
			file.get(ch);//getting '=' symbol
			file2.put(ch);//writing '=' symbol
			cout<<"!!ch : "<<ch<<endl;
			t1=ch;
			if(flag==1 && ch!=';'){
				//check if index varaible or direct value
				while(ij!=ud){
					if(strcmp(temp,uData1[ij].uVar)==0){
						cout<<"***************index**********************"<<temp<<endl;
						checkIndex=1;
						break;
					}
					else{
						checkIndex=2;
					}
					ij+=1;
				}
				if(ch!='='){
					file.get(ch);//getting '=' symbol
					file2.put(ch);//writing '=' symbol
					cout<<"!!ch : "<<ch<<endl;
				}
				while(ch!=';'){
					file.get(ch);
					file2.put(ch);
					temp[i]=ch;
					i++;
				}
				i--;
				temp[i]='\0';
			}
			if(ij<ud && checkIndex==1){
				cout<<"*************call1**********************"<<endl;
				putLine(0,ij);
			}
			else if(flag==1 && t1==';'){
				//check if index varaible or direct value
				while(ij!=ud){
					if(strcmp(temp,uData1[ij].uVar)==0){
						cout<<"***************index**********************"<<temp<<endl;
						checkIndex=1;
						break;
					}
					else{
						checkIndex=2;
					}
					ij+=1;
				}
				if(ij<ud && checkIndex==1){
					cout<<"*************call2**********************"<<endl;
					putLine(0,ij);
				}

			}
			/*if(checkSymbol(temp)){
				cout<<"@check symbol : "<<temp<<"done..\n";
			}*/
			removeSTN(temp);
			cout<<"***********Value************"<<temp<<endl;
			/*strcpy(uData1[max].uVarValue,temp);
			uData1[max].uType=tp;
			cout<<" var : "<<uData1[max].uVar<<" value : "<<uData1[max].uVarValue<<"Type : "<<uData1[max].uType<<"done..\n";*/
			break;
		}
		max+=1;
	}
	return max;
}


int main(int argc,char** argv)
{

    file2.open("./output1.c");
    string word, t, q;
    char filename[100]="./";
    string store;

    // filename of the file
    //filename = "/home/vvaibhav3/eclipse-workspace/Trace It/src/userInput.c";
	strcat(filename,argv[1]);
    // opening file
    file.open(filename);
	//file2<<"#include<fstream>\n";
    // extracting words from the file
    while (!file.eof())	//till file not end
    {
    	file.get(ch);	//read char by char

    	if(ch!=' '){
    		if(ch=='\n'){
    			cout<<"new line character..\n";
    			cout<<"#temp : "<<temp<<"done...\n";
    			temp[i]='\0';
    			if(strcmp(temp,"#include<stdio.h>")==0){
    				file2<<"\n//in main\n//opening file to write data in output file\nFILE *fptr;";
    			}
    			i=0;
    		}
    		//putting data for user defined data type like stack , queue
    		if(mainFlag==1 && assumeFlag==1){
    			//putting output related data
    			file2<<"\nfputs(";
    			file2.put('"');
    			i=0;
    			file2<<"assume:"<<assumeData;
    			file2.put('"');
    			file2<<",fptr);";
    			mainFlag=0;
    			assumeFlag=0;
    		}

    		if(ch=='='){
    			file2.put(ch);
    			temp[i]='\0';
    			cout<<"@@@@@@temp before '=' : "<<temp;
    			i=0;
    			int t=0;
    			while(t!=ud){
    				if(strcmp(temp,uData1[t].uVar)==0){
    					break;
    				}
    				t++;
    			}
    			cout<<"*************************T Value*************************"<<t<<" "<<ud<<endl;
    			i=0;
    			while(ch!=';'){
    				if(ch=='\n'){
    					break;
    				}
    				if(ch=='['){
    					i--;
    					temp[i]='\0';
    					cout<<"************************temp***********************"<<temp<<endl;
    					if(strcmp(temp,uData1[0].uVar)==0){
    						getValue();
    					}
    					break;
    				}
    				file.get(ch);
    				file2.put(ch);
    				temp[i]=ch;
    				i++;
    			}
    			temp[i]='\0';
    			/*if(checkSymbol(temp)){
    				cout<<"@@check symbol : "<<temp<<"done..\n";
    			}
    			*/
    			cout<<"@@@@@@temp after '=' : "<<temp;
    			/*i=0;
    			while(temp[i]!='\0'){
    				if(temp[i]=='['){
    	    			temp[i]='\0';
    	    			if(strcmp(temp,uData1[0].uVar)==0){
    	    				getValue();
    	    			}
       					break;
    				}
    				i++;
    			}*/
    			if(t<ud){
    				putLine(t,0);
    			}
    		}else if(ch=='['){
    			file2.put(ch);
    			temp[i]='\0';
    			cout<<"befor '[' data : "<<temp<<"done..\n";
    			getValue();
    			cout<<"after ']' data : "<<temp<<"done...\n";
    		}else if(ch!=';' && ch!='*'){

    			//check if any function call
        		if(ch=='('){
        			file2.put(ch);
        			temp[i]='\0';
        			cout<<"check1 : "<<temp<<"done.."<<endl;
        			//if main function is started then
        			if(strcmp(temp,"main")==0){
        				putDataIfMain();
        			}
        			else{
        				removeSTN(temp);
        				if(strcmp(temp,"scanf")==0){ //if there is scanf function
        					//putDataIfScanf();
        				}
    					else if(strcmp(temp,"printf")==0){
    						cout<<"printf2..\n";
    						while(ch!=';'){
    							file.get(ch);
    							file2.put(ch);
    						}
    					}
        				else{
        					cout<<"#function names : "<<temp;
        					function_names[fn]=temp;
        				}
        			}
        		}
        		else{
        			file2.put(ch);
    				temp[i]=ch;
    				//cout<<"$#temp : "<<temp[i]<<"done....";
    				i++;
        		}
    		}
    		else if(ch==';'){
    			file2.put(ch);
    			temp[i]='\0';
    			cout<<"\n //middle temp : "<<temp<<" done.."<<endl;
    			i=0;
    		}
    	}
    	else{
    		file2.put(ch);
    		temp[i]='\0';
    		cout<<"\n //end Temp :"<<temp<<" done.."<<endl;
    		removeSTN(temp);
    		tp=getType(temp);//to find type of vars
    		if(tp!='~'){
    			cout<<"@type : "<<tp<<" done...\n";
    			i=0;
    			while(ch!=';'){
    				file.get(ch);
    				//check if any function call
    				if(ch=='('){
    					file2.put(ch);
    					temp[i]='\0';
    					cout<<"\ncheck2 : "<<temp<<"done.."<<endl;
    					//if main function is started then
    					if(strcmp(temp,"main")==0){
    						putDataIfMain();
    					}
    					else if(strcmp(temp,"printf")==0){
    						cout<<"printf2..\n";
    						while(ch!=';'){
    							file.get(ch);
    							file2.put(ch);
    						}
    					}
    					i=0;
    					break;
    				}
    				else if(ch=='='){
    					file2.put(ch);
    					while(temp[i-1]==' '){
    						i-=1;
    					}
    					temp[i]='\0';
    					cout<<"detect '=' : "<<temp<<"done..\n";
    					int max=getValue();
    					strcpy(uData1[max].uVarValue,temp);
    					uData1[max].uType=tp;
    					cout<<" var : "<<uData1[max].uVar<<" value : "<<uData1[max].uVarValue<<"Type : "<<uData1[max].uType<<"done..\n";

    					cout<<"after '=' data : "<<temp<<"done...\n";
    					break;
    				}
    				else if(ch=='['){
    					file2.put(ch);
    					temp[i]='\0';
    					cout<<"after '[' data : "<<temp<<"done..\n";
    					int max=getValue();
    					strcpy(uData1[max].uVarValue,temp);
    					uData1[max].uType=tp;
    					cout<<" var : "<<uData1[max].uVar<<" value : "<<uData1[max].uVarValue<<"Type : "<<uData1[max].uType<<"done..\n";

    					cout<<"before ']' data : "<<temp<<"done...\n";
    					break;
    				}
    				file2.put(ch);
    				temp[i]=ch;
    				i++;
    			}
    			temp[i]='\0';
    			i=0;
    			cout<<"\n@@temp : "<<temp<<"done...\n";
    		}
    		else{
    			removeSTN(temp);
    			cout<<"@temp at assume : "<<temp<<"done..\n";
    			if(strcmp(temp,"assume:")==0){
    				assumeFlag=1;
    				cout<<"**************************temp**************"<<temp<<endl;
    				file>>temp;//read data after assume
    				file2<<temp;//write data first
    				processDataIfAssume();
    				assumeData=temp;
    				cout<<"assume.....\n";
    			}
    		}
    		i=0;
    	}
    }
	cout<<"**************************UVARS WITH INITIAL VALUES**********************************\n";
	int ij=0;
	while(ij!=ud){
		cout<<"var : "<<uData1[ij].uVar<<"    value : "<<uData1[ij].uVarValue<<endl;
		ij+=1;
	}
    return 0;
}
