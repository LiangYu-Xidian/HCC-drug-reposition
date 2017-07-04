#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <iterator>
#include <vector>
#include <ext/hash_map>

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

typedef pair <string, int> Pair;

int main()
{
    ofstream out("C:\\Users\\Administrator\\Desktop\\notfind.txt");
    ifstream in("C:\\Users\\Administrator\\Desktop\\drugsortgene.txt");
    if(!in.is_open()){
        cout << "File opening drugsortgene.txt error!\n";
        exit(1);
    }

    string str;
    int id = 1;
    hash_map <string ,int> glist;
    while(!in.eof()){
        getline(in,str);
        glist.insert(Pair(str,id));
        id++;
    }
    in.close();

    ifstream gfile("C:\\Users\\Administrator\\Desktop\\allpathwaygene.txt");
    if(!gfile.is_open()){
        cout << "File opening allpathwaygene.txt error!\n";
        exit(1);
    }
    while(!gfile.eof()){
        getline(gfile,str);
        if(glist[str] == 0){
            out << str << endl;
        }
    }


    return 0;
}
