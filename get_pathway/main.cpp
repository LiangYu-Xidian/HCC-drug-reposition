#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <vector>
#include <ext/hash_map>
#include <string>

namespace __gnu_cxx {
    template<>
    struct hash<std::string>
    {
        hash<char*> h;
        size_t operator()(const std::string &s) const
        {
            return h(s.c_str());
        };
    };
}

using namespace __gnu_cxx;
using namespace std;

struct pathway{
    string pname;
    vector<string> geneset;
};
typedef pair <string, int> Pair;

int main()
{
//    ifstream infile("C:\\Users\\Administrator\\Desktop\\路径数据\\Kegg\\keggwell.txt");
//    ifstream infile("C:\\Users\\Administrator\\Desktop\\路径数据\\BioCarta\\BioCarta.txt");
    ifstream infile("C:\\Users\\Administrator\\Desktop\\路径数据\\reactome\\reactome.txt");
    if(!infile.is_open()){
        cout << "file open error kegg!\n";
        exit(1);
    }
    vector<pathway> plist;
    string str;
    while(!infile.eof()){
        getline(infile,str);
        size_t pos = 0,found = 0;
        pathway px ;
        found = str.find("\t",pos);
        px.pname = string(str,pos,found-pos);
        pos = found+1;
        while(found!= string::npos){
            found = str.find("\t",pos);
            px.geneset.push_back(string(str,pos,found-pos));
            pos = found+1;
        }
        plist.push_back(px);
        px.geneset.clear();
    }
    infile.close();

    hash_map <string ,int> glist;
    ifstream gfile("C:\\Users\\Administrator\\Desktop\\genesignature4.txt");
    if(!gfile.is_open()){
        cout << "file open error gsfile!\n";
        exit(1);
    }
    string gene; int id =0;
    while(!gfile.eof()){
        getline(gfile,gene);
        glist.insert(Pair(gene,id));
        id++;
    }

    ofstream outpath("C:\\Users\\Administrator\\Desktop\\reactome4.txt");
    if(!outpath.is_open()){
        cout << "error 文件写入\n";
    }
    size_t i,j;
    for(i=0;i<plist.size();i++){
        string strg;
        for(j=0;j<plist[i].geneset.size();j++){
            strg = plist[i].geneset[j];
            if(glist.find(strg) != glist.end()){
                outpath<< plist[i].pname << "\t";
                for(size_t a =0;a<plist[i].geneset.size();a++){
                    if(a<plist[i].geneset.size()-1){
                        outpath << plist[i].geneset[a] << "\t";
                    }else{
                        outpath << plist[i].geneset[a] << endl;
                    }
                }
                break;
            }
        }
    }

    glist.clear();
    plist.clear();




    return 0;
}
