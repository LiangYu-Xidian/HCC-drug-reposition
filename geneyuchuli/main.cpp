#include <iostream>
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <vector>
#include <string.h>
using namespace std;

int main()
{
     ifstream in("C:\\Users\\Administrator\\Desktop\\drugdata\\probe-gene.txt");
     if(! in.is_open())  {
        cout << "Error opening file probe-gene.txt";
        exit (1);
     }
     ofstream out("C:\\Users\\Administrator\\Desktop\\drugdata\\re.txt");
     if(!out.is_open()){
        cout << "Error opening file";
        exit(1);
     }
     string str;
     while (!in.eof()) {
        getline(in,str);
        if(str.find("///") != std::string::npos){
            stringstream ss(str);
            string t1,t2,t3;
            ss >> t1;
            ss >> t2;
            ss >> t3;
            string pattern = "///";
//            int s1 = t2.size();
            vector<string> geneid;
            vector<string> geneSymbol;
            int i;
            for(i=0;i<t2.size();i++){
                string::size_type pos;
                pos = t2.find(pattern,i);
                if(pos !=string::npos){
                    string s = t2.substr(i,pos-i);
                    geneSymbol.push_back(s);
                    i = pos + pattern.size()-1;
                }else{
                    string s = t2.substr(i);
                    geneSymbol.push_back(s);
                    break;
                }
            }

            for(int i=0;i<t3.size();i++){
                string::size_type pos;
                pos = t3.find(pattern,i);
                if(pos !=string::npos){
                    string s = t3.substr(i,pos-i);
                    geneid.push_back(s);
                    i = pos + pattern.size()-1;
                }else{
                    string s = t3.substr(i);
                    geneid.push_back(s);
                    break;
                }
            }
            for(int i=0;i<geneid.size();i++){
                out << t1 << "\t" << geneSymbol[i] << "\t" << geneid[i] << endl;
            }
        }else{
            out << str << endl;
        }
    }
    return 0;
}
