#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <string>
#include <algorithm>
using namespace std;

struct Student {
    string n,r; //n=Name,r=Roll no
    vector<double>q,a; //q=Quiz,a=Assignment
    double m,f,p,t; //m=Midterm,f=Finalterm,p=Project,t=Total
    string g; //g=Grade
};

void calculategrades(vector<Student>&students,double avg) {
    for (auto&s:students) {
        if(s.t < avg - 22)s.g="F";
        else if(s.t<avg-18)s.g="D";
        else if(s.t<avg-14)s.g="C-";
        else if(s.t<avg-10)s.g="C";
        else if(s.t<avg-6)s.g="C+";
        else if(s.t<avg-2)s.g="B-";
        else if(s.t<avg+2)s.g="B";
        else if(s.t<avg+6)s.g="B+";
        else if(s.t<avg+10)s.g="A-";
        else s.g="A";
    }
}

int main() {
    string fn;
    cout<<"Welcome to the Teacher Result Portal!"<<endl;
    cout<<endl;

    cout<<"Enter name of file with extension:";
    cin>>fn;

    ifstream file(fn);
    if (!file.is_open()) {
    	cout<<endl;
        cout<<"File does not exist"<<endl;;
        return 1;
    }

    string line,col; //col=Column
    getline(file,line);
    stringstream ss(line);
    int nq=0,na=0;
    vector<string> hdrs; //hdrs=Headers
    while (getline(ss,col,',')) {
        hdrs.push_back(col);
        if(col[0]=='Q') nq++;
        else if(col[0]=='A') na++;
    }

    double qw,aw,mw,fw,pw; //w=Weightage
    cout<<"Entering the weightage:"<<endl;
    cout<<endl;
    cout<<"Total weightage for Quizzes:"; 
	cin>>qw;
    cout<<"Total weightage for Assignments:"; 
	cin>>aw;
    cout<<"Total Weightage for Midterm:"; 
	cin>>mw;
    cout<<"Total Weightage for Final Exam:"; 
	cin>>fw;
    cout<<"Total Weightage for Project:"; 
	cin>>pw;

    double tw=qw+aw+mw+fw+pw;
    if(tw!=100) {
        cout<<"Total Wightage is not equal to 100. You entered:"<<tw<<".Please run the program again."<<endl; 
        return 1;
    }

    vector<Student>students;
    while(getline(file,line)) {
        stringstream ss(line);
        Student s;
        string val;
        getline(ss,s.n,',');
        getline(ss,s.r,',');
        for(int i=0;i<nq;i++) {
            getline(ss,val,',');
            s.q.push_back(stod(val)); //stod=String to double
        }
        for(int i=0;i<na;i++) {
            getline(ss,val,',');
            s.a.push_back(stod(val));
        }
        getline(ss,val,','); 
		s.m=stod(val);
        getline(ss,val,','); 
		s.f=stod(val);
        getline(ss,val,','); 
		s.p=stod(val);

        double qs=0,as=0; //s=Sum
        for(auto m:s.q) qs+=m;
        for(auto m:s.a) as+=m;

        s.t=(qs/(nq*10.0))*qw
             + (as/(na*10.0))*aw
             + (s.m/100.0)*mw
             + (s.f/100.0)*fw
             + (s.p/40.0)*pw;

        students.push_back(s);
    }

    double avg=0;
    for (auto s:students) 
	avg+=s.t;
    avg/=students.size();

    calculategrades(students, avg);

    int ch;
    do{
    	cout<<endl;
        cout<<"1.Display Class Result on Console"<<endl;
        cout<<"2.Generate Result CSV File"<<endl;
        cout<<"3.Search Student by Roll Number"<<endl;
        cout<<"4.Exit"<<endl;
        cout<<"Enter your choice:";
        cin>>ch;

        if(ch==1) {
            cout<<endl<<"Class Results:"<<endl;;
            cout<<left<<setw(25)<<"Name"<<setw(12)<<"Roll No"<<setw(8)<<"Total"<<"Grade\n";
            for(auto s:students)
                cout<<left<<setw(25)<<s.n<<setw(12)<<s.r<<setw(8)<<fixed<<setprecision(2)<<s.t<<s.g<<'\n';

        }
		else if(ch==2) {
            ofstream outFile(fn.substr(0,fn.find('.'))+"_result.csv");
            outFile <<"Name,Roll No,Total,Grade"<<endl;;
            for(auto s:students)
                outFile<<s.n<<','<<s.r<<','<<fixed<<setprecision(2)<<s.t<<','<<s.g<<'\n';
            cout<<endl<<"File created"<<endl;;

        } 
	    else if(ch==3) {
            string sr;
            cout<<endl<<"Enter Roll Number to search:";
            cin>>sr;
            bool found=false;
            for (auto s:students) {
                if (s.r==sr) {
                    cout<<"\nName:" <<s.n<<"\nTotal:"<<fixed<<setprecision(2)<<s.t<<"\nGrade:"<<s.g<<'\n';
                    found=true;
                    break;
                }
            }
            if(!found) 
			cout<<endl<<"Student with Roll No "<<sr<<"not found in records"<<endl;;
        }

    } 
	while (ch!=4);

    cout<<endl<<"Thank you for using the Teacher Result Portal"<<endl;
    return 0;
}

