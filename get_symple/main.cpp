#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <winsock2.h>
#include <mysql.h>
#include <windows.h>
#include <string.h>
#include <vector>
#include <sstream>

using namespace std;

string getsymbol(char* str){
    const char user[] = "root";         //username
    const char pswd[] = "";         //password
    const char host[] = "localhost";    //or"127.0.0.1"
    const char table[] = "geo";        //database
    unsigned int port = 3306;           //server port

    MYSQL myCont;
    MYSQL_RES *result;
    MYSQL_ROW sql_row;

    int res;
    mysql_init(&myCont);
    string t = "";

    if(mysql_real_connect(&myCont,host,user,pswd,table,port,NULL,0))
    {
        mysql_query(&myCont, "SET NAMES GBK"); //Set the encoding format, otherwise Chinese cannot be displayed under cmd
        res=mysql_query(&myCont,str);//select

        if(!res){
            result=mysql_store_result(&myCont);//Save the queried data to result
            if(result){
                while(sql_row=mysql_fetch_row(result)){//Get specific data
                    t = sql_row[0];
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

    return t;
}


int main()
{
    ifstream in("C:\\Users\\Administrator\\Desktop\\肝癌数据集\\geneset.txt");
    if(! in.is_open()){
        cout << "Error opening file\n";
        exit(1);
    }
    ofstream outfile("C:\\Users\\Administrator\\Desktop\\肝癌数据集\\symple.txt");
    if(!outfile.is_open()){
        cout << "Error opening file\n";
    }
    string gene_id;

    while (!in.eof()){
        getline(in,gene_id);
        string str = "select gene_symbol from gpl570 where gene_id = " + gene_id +";";
        outfile << getsymbol((char*)str.data())<< endl;
    }
    return 0;
}
