#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <winsock2.h>
#include <mysql.h>
#include <windows.h>
#include <string.h>
#include <vector>
#include<sstream>

using namespace std;

string getprobe(char* str){
    const char user[] = "root";         //username
    const char pswd[] = "";         //password
    const char host[] = "localhost";    //or"127.0.0.1"
    const char table[] = "geo";        //database
    unsigned int port = 3306;           //server port

    MYSQL myCont;
    MYSQL_RES *result;
    MYSQL_ROW sql_row;

    int res;
    vector<string> record; // result
    mysql_init(&myCont);
    string t = "";

    if(mysql_real_connect(&myCont,host,user,pswd,table,port,NULL,0))
    {
        mysql_query(&myCont, "SET NAMES GBK"); //Set the encoding format, otherwise Chinese cannot be displayed under cmd
        res=mysql_query(&myCont,str);//select

        if(!res){
            result=mysql_store_result(&myCont);//Save the queried data to result
            int num = (int)mysql_num_rows(result);
            if(result){
                int i;
                while(sql_row=mysql_fetch_row(result)){//Get specific data
                    record.push_back(sql_row[0]);
                }
                for(i=0;i<num;i++){
                    t.append("'");
                    t = t+record[i];
                    if(i != num-1){
                        t.append("',");
                    }else{
                        t.append("'");
                    }
                }
            }
        }else {
            cout << "query sql failed!"<<endl;
            cout << mysql_error(&myCont) << endl;
            mysql_close(&myCont);//Disconnect
        }
    }
    else
    {
        cout<<"connect failed!"<<endl;
    }
    if(result!=NULL) mysql_free_result(result);//Release result resources
    mysql_close(&myCont);//Disconnect
    record.clear();
    return t;
}

void query2(char* str,ofstream& outfile){
    const char user[] = "root";         //username
    const char pswd[] = "";         //password
    const char host[] = "localhost";    //or"127.0.0.1"
    const char table[] = "drug";        //database
    unsigned int port = 3306;           //server port

    MYSQL myCont;
    MYSQL_RES *result;
    MYSQL_ROW sql_row;

    vector<vector <string> > arr;
    int res;
    mysql_init(&myCont);
    if(mysql_real_connect(&myCont,host,user,pswd,table,port,NULL,0))
    {
        mysql_query(&myCont, "SET NAMES GBK"); //Set the encoding format, otherwise Chinese cannot be displayed under cmd
        res=mysql_query(&myCont,str);//select
        if(!res){
            result=mysql_store_result(&myCont);//Save the queried data to result
            if(result){
                int j;
                j = mysql_num_fields(result);
                int num = 0;
                vector<string> row;
                while(sql_row=mysql_fetch_row(result)){
                    for(int k=1;k<j;k++){
                        row.push_back(sql_row[k]);
                    }
                    arr.push_back(row);
                    row.clear();
                    num++;
                }

                for(int i=0;i<j-1;i++){
                    double t = 0.00000000;
                    for(int k=0;k<num;k++){
                        stringstream ss;
                        ss<< arr[k][i];
                        double d;
                        ss >> d;
                        ss.clear();
                        t += d;
                    }
                    char value[25] = "";
                    sprintf(value,"%.8f",t);//Format a and output it to str, taking 7 decimal places
                    if(i != j-2){
                        outfile << value <<"\t";
                    }else{
                        outfile << value << endl;
                    }
                }
            }
        }else {
            cout << "query sql failed!"<<endl;
            cout << mysql_error(&myCont) << endl;

            mysql_close(&myCont);//Disconnect
        }
    }
    else
    {
        cout<<"connect failed!"<<endl;
    }
    if(result!=NULL) mysql_free_result(result);//Release result resources
    mysql_close(&myCont);//Disconnect
    arr.clear();
    return ;
}



int main()
{
    ifstream in("C:\\Users\\Administrator\\Desktop\\肝癌数据集\\geneset.txt");
    if(! in.is_open()){
        cout << "Error opening file\n";
        exit(1);
    }
    ofstream outfile("C:\\Users\\Administrator\\Desktop\\肝癌数据集\\exprestiondata.txt");
    if(!outfile.is_open()){
        cout << "Error opening file\n";
    }
    string gene_id;
    while (!in.eof()){
        getline(in,gene_id);
        string str1 = "select probe_id from gpl570 where gene_id = " + gene_id +";";
        char* probe = (char*) str1.data();
        string probeset = getprobe(probe);
        string str2 = "select * from gse where probe_id in(" + probeset + ");";
        char* query = (char*)str2.data();
        outfile << gene_id<< "\t";
        query2(query,outfile);

    }
    return 0;
}
