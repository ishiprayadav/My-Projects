#include <bits/stdc++.h>
using namespace std;

class library{
    private:
    int accessno,admno;
    char title[20],author[20],pub[20],issue;
    float price;
    public:
    void accept()
    {
        cout<<"Enter the accession number of book";
        cin>>accessno;
        cout<<"Enter the book title";
        cin>>title;
        cout<<"Enter the author name";
        cin>>author;
        cout<<"Enter the publisher";
        cin>>pub;
        cout<<"Enter the price";
        cin>>price;
        admno=0;
        issue='N';
    }
    
    void display()
    {
        cout<<"Accession number of the book :"<<'\t'<<accessno<<'\n';
        cout<<"Title of the book :"<<'\t'<<title<<'\n';
        cout<<"Author of the book :"<<'\t'<<author<<'\n';
        cout<<"Publisher of the book :"<<'\t'<<pub<<'\n';
        cout<<"Price of the book :"<<'\t'<<price<<'\n';
        cout<<"Issue status of the book :"<<'\t'<<issue<<'\n';
        if(issue=='Y')
        cout<<"Issued to admission number :"<<'\t'<<admno<<'\n';
    }
    int search(int acc)
    {
        if(acc==accessno)
        return 1;
        else
        return 0;
    }

    void issue1()
    {
        if(issue=='Y')
        cout<<"Book is already issued"<<'\n';
        else
        {
            cout<<"Enter the admission number";
            cin>>admno;
            cout<<"Book is issued"<<'\n';
            issue='Y';
        }
    }

    void returnb()
    {
        admno=0;
        issue='N';
        cout<<"Book is returned"<<'\n';
    }

};


int main()
{
    fstream obj;
    library l;
    int acc,ch,r,c=0;
    do{
        cout<<"MAIN MENU"<<'\n';
        cout<<"1- ADD RECORDS"<<'\n';
        cout<<"2- ISSUE A BOOK"<<'\n';
        cout<<"3- RETURN A BOOK"<<'\n';
        cout<<"4- DISPLAY ALL BOOK DETAILS"<<'\n';
        cout<<"5- DISPLAY SINGLE BOOK DETAILS"<<'\n';
        cout<<"6- EXIT"<<'\n';
        cout<<"ENTER YOUR CHOICE"<<'\n';
        cin>>ch;
        switch(ch)
        {
            case 1:
            obj.open("lib.dat",ios::binary|ios::app);
            l.accept();
            obj.write((char *)&l,sizeof(l));
            obj.close();
            break;

            case 2:
            obj.open("lib.dat",ios::binary|ios::in|ios::out);
            cout<<"Enter the accesssion number";
            cin>>acc;
            c=0;
            while(!obj.eof())
            {
                obj.read((char *)&l,sizeof(l));
                c++;
                r=l.search(acc);
                if(r==1)
                {
                    l.issue1();
                    obj.seekp((c-1)* sizeof(l),ios::beg);
                    obj.write((char*)&l,sizeof(l));
                    break;
                }
            }
            if(r==0)
            cout<<"The given book is not found";
            obj.close();
            break;

            case 3:
            obj.open("lib.dat",ios::binary|ios::in|ios::out);
            cout<<"Enter the accession number";
            cin>>acc;
            c=0;
            while(!obj.eof())
            {
                obj.read((char*)&l,sizeof(l));
                c++;
                r=l.search(acc);
                if(r==1)
                {
                    l.returnb();
                    obj.seekp((c-1)* sizeof(l),ios::beg);
                    obj.write((char*) &l,sizeof(l));
            
                }
                break;
            }
            if(r==0)
            cout<<"The given book is not found";
            obj.close();
            break;

            case 4:
            obj.open("lib.dat",ios::binary|ios::in);
            while(obj.read((char*)&l,sizeof(l)))
            {
                l.display();
            }
            obj.close();
            break;

            case 5:
            obj.open("lib.dat",ios::binary|ios::in);
            cout<<"Enter the accession number";
            cin>>acc;
            while(!obj.eof())
            {
                obj.read((char*)&l,sizeof(l));
                r=l.search(acc);
                if(r==1)
                {
                    l.display();
                    break;
                }
            }
                
                if(r==0)
                cout<<"The give n accession number is not found";
                obj.close();
                break;

                case 6:
                exit(0);
                deault:
                cout<<"Wrong choice";
            
        }
    }while(1);
    return 0;

}