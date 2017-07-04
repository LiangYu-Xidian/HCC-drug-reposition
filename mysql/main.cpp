#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include <mysql.h>
#include <iostream>
#include <vector>
#include<cstdlib>
#include<sstream>

using namespace std;

char* getprobe(char* str){
    const char user[] = "root";         //username
    const char pswd[] = "";         //password
    const char host[] = "localhost";    //or"127.0.0.1"
    const char table[] = "geo";        //database
    unsigned int port = 3306;           //server port

    MYSQL myCont;
    MYSQL_RES *result;
    MYSQL_FIELD *fd;
    MYSQL_ROW sql_row;

    char column[32][32];
    int res;

    char* queryre;// 存放查询后的结果
    vector<string> record; // 结果
    mysql_init(&myCont);
    if(mysql_real_connect(&myCont,host,user,pswd,table,port,NULL,0))
    {
        cout<<"connect succeed!"<<endl;
        mysql_query(&myCont, "SET NAMES GBK"); //设置编码格式,否则在cmd下无法显示中文
        res=mysql_query(&myCont,str);//查询
        if(!res){
            result=mysql_store_result(&myCont);//保存查询到的数据到result
            if(result){
                int i,j;
                while(sql_row=mysql_fetch_row(result)){//获取具体的数据
                    record.push_back(sql_row[0]);
                }
                string t;
                for(i=0;i<record.size();i++){
                    t.append("'");
                    t = t+record[i];
                    if(i != record.size()-1){
                        t.append("',");
                    }else{
                        t.append("'");
                    }

                }
                queryre = (char*) t.data();
            }
        }else {
            cout << "query sql failed!"<<endl;
            cout << mysql_error(&myCont) << endl;
            mysql_close(&myCont);//断开连接
        }
    }
    else
    {
        cout<<"connect failed!"<<endl;
    }
    if(result!=NULL) mysql_free_result(result);//释放结果资源
    mysql_close(&myCont);//断开连接
    return queryre;
}
double* query2(char* str){
    const char user[] = "root";         //username
    const char pswd[] = "";         //password
    const char host[] = "localhost";    //or"127.0.0.1"
    const char table[] = "geo";        //database
    unsigned int port = 3306;           //server port

    MYSQL myCont;
    MYSQL_RES *result;
    MYSQL_FIELD *fd;
    MYSQL_ROW sql_row;

    double data[200];
    string arr[10][200];
    int res;

    char* queryre;// 存放查询后的结果
    vector<string> record; // 结果
    mysql_init(&myCont);
    if(mysql_real_connect(&myCont,host,user,pswd,table,port,NULL,0))
    {
        cout<<"connect succeed!"<<endl;
        mysql_query(&myCont, "SET NAMES GBK"); //设置编码格式,否则在cmd下无法显示中文
        res=mysql_query(&myCont,str);//查询

        if(!res){
            result=mysql_store_result(&myCont);//保存查询到的数据到result
            int num = (int)mysql_num_rows(result);
            if(result){
                int i,j;
                j=mysql_num_fields(result);
                for(int i=0;i<num;i++){
                    sql_row=mysql_fetch_row(result);
                    for(int k=1;k<j;k++){
                        arr[i][k] = sql_row[k];
                    }
                }
                for(int i=1;i<j;i++){
                    double t = 0.00000000;
                    for(int k=0;k<num;k++){
                        stringstream ss;
                        ss<< (char*)arr[k][i].data();
                        double d;
                        ss >> d;
                        ss.clear();
                        t += d;


                    }
                    cout.precision(10);
                    cout << t << endl;
                    data[i-1] = t;
                }
            }
        }else {
            cout << "query sql failed!"<<endl;
            cout << mysql_error(&myCont) << endl;
            mysql_close(&myCont);//断开连接

        }
    }
    else
    {
        cout<<"connect failed!"<<endl;
    }
    if(result!=NULL) mysql_free_result(result);//释放结果资源
    mysql_close(&myCont);//断开连接
    return data;
}

int main()
{
    char* q1 = "select probe_id from gpl570 where gene_id = '780';";
    char* probe = getprobe(q1);
    char* q2 = "select * from gse where probe_id in(";

    const size_t len = strlen(q2)+strlen(probe);
    char* expressionata = new char[len+1];
    strcpy(expressionata,q2);
    strcat(expressionata,probe);
    strcat(expressionata,");");
    double* data = query2(expressionata);

    return 0;
}
