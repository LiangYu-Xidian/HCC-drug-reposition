#include <iostream>
#include <fstream>
#include <stdlib.h>

using namespace std;

int main()
{
    ofstream p1("C:\\Users\\Administrator\\Desktop\\p1.txt");
    if(! p1.is_open()){
        cout << "Error opening p1.txt"<<endl;
        exit(1);
    }
//    ofstream p2("C:\\Users\\Administrator\\Desktop\\p2.txt");
//    if(! p2.is_open()){
//        cout << "Error opening p2.txt"<<endl;
//        exit(1);
//    }
//    ofstream p3("C:\\Users\\Administrator\\Desktop\\p3.txt");
//    if(! p3.is_open()){
//        cout << "Error opening p3.txt"<<endl;
//        exit(1);
//    }
//    ofstream p4("C:\\Users\\Administrator\\Desktop\\p4.txt");
//    if(! p4.is_open()){
//        cout << "Error opening p4.txt"<<endl;
//        exit(1);
//    }
//    ofstream p5("C:\\Users\\Administrator\\Desktop\\p5.txt");
//    if(! p5.is_open()){
//        cout << "Error opening p5.txt"<<endl;
//        exit(1);
//    }
//    ofstream p6("C:\\Users\\Administrator\\Desktop\\p6.txt");
//    if(! p6.is_open()){
//        cout << "Error opening p6.txt"<<endl;
//        exit(1);
//    }
//    ofstream p7("C:\\Users\\Administrator\\Desktop\\p7.txt");
//    if(! p7.is_open()){
//        cout << "Error opening p7.txt"<<endl;
//        exit(1);
//    }
//    ofstream p8("C:\\Users\\Administrator\\Desktop\\p8.txt");
//    if(! p8.is_open()){
//        cout << "Error opening p8.txt"<<endl;
//        exit(1);
//    }
//    ofstream p9("C:\\Users\\Administrator\\Desktop\\p9.txt");
//    if(! p9.is_open()){
//        cout << "Error opening p9.txt"<<endl;
//        exit(1);
//    }

    ifstream in("C:\\Users\\Administrator\\Desktop\\drugdata\\probeÊý¾Ý\\probe_id.txt");
    if(! in.is_open()){
        cout << "Error opening p_id.txt" << endl;
        exit(1);
    }

    int i=0;
    string str;
    while(! in.eof()){
        getline(in,str);
        if(i<2000){
            p1<< str <<"\n";
        }
//        cout << str << endl;
//        int file = i/2000+1;
//        switch(file){
//            case 1:p1<< str << "\n"; break;
//            case 2:p2<< str << "\n"; break;
//            case 3:p3<< str << "\n"; break;
//            case 4:p4<< str << "\n"; break;
//            case 5:p5<< str << "\n"; break;
//            case 6:p6<< str << "\n"; break;
//            case 7:p7<< str << "\n"; break;
//            case 8:p8<< str << "\n"; break;
//            case 9:p9<< str << "\n"; break;
//        }
        i++;
    }

    return 0;
}
