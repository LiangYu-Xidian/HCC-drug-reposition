#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <iterator>
#include <list>
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

typedef pair <string, int> Pair; // �Զ���Ĺ�ϣ�����ݽṹ

struct Node{ // �ڵ����ݽṹ
    string gene; // ����name
    int id; // ������HCC rank list �е�����λ��
};

void insertsort(list<Node>&L,Node *x){ // ��������Ĺ���
    if(L.empty()){
        L.push_back(*x);
    }
    list<Node>::iterator it;
    for(it = L.begin();it!=L.end();it++){
        if(it->id >x->id)
            break;
    }
    L.insert(it,*x);
    return ;
}

int main()
{
    ofstream out("C:\\Users\\Administrator\\Desktop\\tkeggout.txt");// ��������Ľ��
    ifstream in("C:\\Users\\Administrator\\Desktop\\hcc_gene_rank.txt"); // �Ѿ�����õ�HCC�Ļ����б�
    if(!in.is_open()){
        cout << "File opening hcc_gene_rank.txt error!\n";
        exit(1);
    }

    string str;
    int id = 1;
    hash_map <string ,int> glist; //HCC rank list��ϣ�洢�ṹ

    while(!in.eof()){ // ������ϣ��
        getline(in,str);
        glist.insert(Pair(str,id));
        id++;
    }
    in.close();

    ifstream pfile("C:\\Users\\Administrator\\Desktop\\tkegg.txt"); // ���KEGG·���ļ�
    if(!pfile.is_open()){
        cout << "File opening tkegg.txt error!\n";
        exit(1);
    }
    string pattern = "\t";
    while(!pfile.eof()){
        getline(pfile,str);
        list<Node> L;
        for(size_t i=0;i<str.size();i++){
            string::size_type pos;
            pos = str.find(pattern,i);
            if(pos != string::npos){
                string s = str.substr(i,pos-i);
                Node* x =new Node();
                x->gene = s;
                x->id = glist[s];
                insertsort(L,x);
                i = pos + pattern.size()-1;
            }else{
                string s = str.substr(i);
                Node* x =new Node();
                x->gene = s;
                x->id = glist[s];
                insertsort(L,x);
                break;
            }
        }
        list<Node>::iterator it;
        int pos = 0;
        for(it = L.begin();it!=L.end();it++){
            it != L.begin()? out << "\t" <<it->gene <<"--"<<it->id  : out << it->gene<<"--"<<it->id;
        }
        out <<endl;

        L.clear();
    }


    return 0;
}
