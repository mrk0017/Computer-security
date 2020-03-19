/*******************************************************************
*   Source Code File Name:Project_1.cpp
*   Your Name: Krishna Chaitanya Choudary Anumolu
*   Class: CS585- Introduction to Computer Security.
*   Programming Assignment number and name: 1 , Encryption in Vigener Cipher and Block Affine Cipher
*   This program is entirely my own work
*******************************************************************/
using namespace std;

#include<iostream>
#include<string.h>
#include<stdlib.h>
#include<fstream>

// Intinalization of global variables

string vkey; //vigenre key
int addvalue; //add value from add function
char c; // Selection of size
int gcdval; // gcd value from gcd
int modinv; // Modular inverse value
int subval; // sub value form sub function
int flagx; //flag for removing added element

// User defined functions

void vkeygen(string a); //vigener key generation function
void add(char cstring,char key); // add function for vigenere cipher encryption
void gcd(int a,int b); // greatest common divisor functioin for calculating coprime
void modularinv(int a,int m); //Modular Inverse calculation function for Block affine decryption
void sub(char cstring,char key); //sub function for vigenere cipher decryption

int main()
{
    cout<<"Encryption In Vigenere and Block affine ciphers"<<endl;
    
    ifstream intxt("plaintext.txt"); // reading plain text from input file 
    
    int flagz=0;
    
    
    cout<<"Select size of Cipher(S/L):"<<endl;
    cin>>c;                          // Size selection
    
    while(c != 'S' && c != 'L')      // Verifying input
    {
        cout<<"Please enter proper selection:"<<endl;
        cin>>c;
    }
    
    string x,y;
    
    while(!intxt.eof())  //reading text string 
    {
        intxt>>x;
        
        y=y+x;
    }
    
    if(y.size()%2==1)  //Checking size of string to append 'A' if odd
    {
        y=y+'A';
        flagx=1;
    }
    
    vkeygen(y);  //Calling function to generate vigenere cipher key
    
    if(c == 'S') // Capitalizing string charachters
    {
        for(int i=0;i<y.size();i++)
        {
            y[i]=toupper(y[i]);
            
            vkey[i]=toupper(vkey[i]);
        }
    }
    
    string S ("0ABCDEFGHIJKLMNOPQRSTUVWXYZ"); //Intialaizing characheter table strings
    string L ("0ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
    string cipher;
    
    int i,i1,j,j1;
    
    for(i=0;i<vkey.size();i++) //Encryption using Vigener cipher
    {
        add(y[i],vkey[i]); // Calling add function
        if(c=='S')
        {
            for(i1=1;i1<=26;i1++)
            {
                if(addvalue==i1) //Checking for number of the charachter
                {
                    cipher=cipher+S[i1];
                }
            }
        }
        else
        {
            for(i1=1;i1<=52;i1++)
            {
                if(addvalue==i1) // Checking for number of charachter
                {
                    cipher=cipher+L[i1];
                }
            }
        }
    }
     
     ofstream vcouttxt("vigenerecipheroutput.txt"); //opening output file
     
     vcouttxt<<cipher; //passing vigenere cipher text into file
     
     intxt.close(); // closing open files
     
     vcouttxt.close();
     
     ifstream baffinetxt("vigenerecipheroutput.txt"); //opening input file
     
     string x1,y1;
     
    while(!baffinetxt.eof())
    {
        baffinetxt>>x1;
        
        y1=y1+x1;
    }
    
    string z;
    
    cout<<"Input Multiplier for Block Affine cipher"<<endl; // Input multiplier and offset for Block affine cipher
    int m,o;
    cin>>m;
    cout<<"Input offset for Block affine cipher:"<<endl;
    cin>>o;
    
    if(c == 'S') //Calculating gcd
    {
        gcd(m,26);
    }
    else
    {
        gcd(m,52);
    }
    
    int flag=0;
    
    while(flag==0) // Checking gcd for given input is 1 or not.
    {
        if(gcdval==1)
        {
            flag = 1;
        }
        else
        {
            cout<<"Wrong input multiplier"<<endl;
            exit(0);
        }
    }
    
    int t;
    int func;
    string cipher1;
    
    ofstream baout("blockaffinecipheroutput.txt"); //Opening output file
    
    for(i=0;i<y1.size();i++) // Encryption using Block Affine cipher
    {
        if((i%2)==1)
        {
            t=i;
            
            if(c=='S')
            {
                for(i1=1;i1<=26;i1++)
                {
                    if(y1[t-1]==S[i1]) //Finding value of charachter in string
                    {
                        func=(((m*i1)+o)%26); // Block affine cipher function for 26 Characters
                        cipher1=cipher1+S[func];
                    }
                }
                
                for(i1=1;i1<=26;i1++)
                {
                    if(y1[t]==S[i1]) // Finding value of charachter in key
                    {
                        func=((m*i1)+o)%26;
                        cipher1=cipher1+S[func];
                    }
                }
            }
            else
            {
                for(j1=1;j1<=52;j1++)
                {
                    if(y1[t-1]==L[j1])
                    {
                        func=((m*j1)+o)%52;
                        cipher1=cipher1+L[func];
                    }
                }
                
                for(j1=1;j1<=52;j1++)
                {
                    if(y1[t]==L[j1])
                    {
                        func=((m*j1)+o)%52;
                        cipher1=cipher1+L[func];
                    }
                }
            }
            
        }
    }
    
    baout<<cipher1;
    
    baout.close();
    
    ifstream badeciph("blockaffinecipheroutput.txt");
    
    string x2,y2;
    
    while(!badeciph.eof())
    {
        badeciph>>x2;
        
        y2=y2+x2;
    }
    
    if(c=='S') // Calculating the modular inverse
    {
        modularinv(m,26);
    }
    else
    {
        modularinv(m,52);
    }
    
    string deciph1;
    
    int ttemp;
    
    for(i=0;i<y2.size();i++) //Decryption of Block Affine cipher
    {
        if(c=='S')
        {
            for(i1=1;i1<=26;i1++)
            {
                if(y2[i]==S[i1])
                {
                    ttemp=i1-o;
                    if(ttemp<0)
                    {
                        ttemp=ttemp+26;
                    }
                    deciph1= deciph1+S[(modinv*(ttemp))%26];
                }
            }
        }
        else
        {
            for(i1=1;i1<=52;i1++)
            {
                if(y2[i]==L[i1])
                {
                    ttemp=i1-o;
                    if(ttemp<0)
                    {
                        ttemp=ttemp+52;
                    }
                    deciph1= deciph1+L[(modinv*(ttemp))%52];
                }
            }
        }
    }
    
    ofstream badeciphout("blockaffinecipherplaintextoutput.txt");
    
    badeciphout<<deciph1;
    
    badeciphout.close();
    
    ifstream vdeciphin("blockaffinecipherplaintextoutput.txt");
    
    string x3,y3;
    
    while(!vdeciphin.eof())
    {
        vdeciphin>>x3;
        y3=y3+x3;
    }
    
    string cipher2;
    
    
    for(i=0;i<y3.size();i++) // Decryption of Vigenere cipher
    {   
        sub(y3[i],vkey[i]);
        if(c=='S')
        {
            for(i1=1;i1<=26;i1++)
            {
                if(subval==i1)
                {
                    cipher2=cipher2+S[i1];
                }
            }
        }
        else
        {
            for(i1=1;i1<=52;i1++)
            {
                if(subval==i1)
                {
                    cipher2=cipher2+L[i1];
                }
            }
        }
    }
    
    ofstream finalout("secondplaintext.txt");
    
    if(flagx == 1) //Removing the appended bit 'A' from the string
    {
        for(int i=0; i<(cipher2.size()-1);i++)
        {
            finalout<<cipher2[i];
        }
       
    }
     else
    {
        finalout<<cipher2;
    }
    
    finalout.close();
    
    return 0;
    
}

void vkeygen(string a) // Vigenere key generator
{
    string x,y;
    
    ifstream vktxt("vcipherkey.txt");
    
    while(!vktxt.eof())
    {
        vktxt>>x;
        
        y=y+x;
    }
    
    int cs=a.size();
    int kt=y.size();
    
    for(int i=0;i<(cs/kt);i++)
    {
        vkey+=y;
    }
    
    for(int i=0;i<(cs%kt);i++)
    {
        vkey+=y[i];
    }
    
    vktxt.close();
    
}

void add(char cstring,char key) // Adding charachter values
{
    string S ("0ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    string L ("0ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
    

     int i,i1;
     int j,j1;
     int x;
     char temp;
     
     
     
     if(c=='S')
     {
         
        for(i=1;i<=26;i++)
        {
            temp= S[i];
            if(temp == cstring)
            {
                i1=i;
            }
        }
        
        for(j=1;j<=26;j++)
        {
            if(key == S[j])
            {
                j1=j;
            }
        }
         x=(i1+j1)%26;
         if(x==0)
         {
             addvalue=26;
         }
         else
         {
             addvalue=x;
         }
         
     }
     else
     {
        for(i=1;i<=52;i++)
        {
            if(cstring == L[i])
            {
                i1=i;
            }
        }
        for(j=1;j<=52;j++)
        {
            if(key == L[j])
            {
                j1=j;
            }
        }
         
         x=(i1+j1)%52;
         
         if(x==0)
         {
             addvalue=52;
         }
         else
         {
             addvalue=x;
         }
     }
     
}

void gcd (int a ,int b ) // Claculating the gcd value
{
    int i;
      
    i=b%a;
      
    while(i!=0)
    {
        b=a;
        a=i;
        i=b%a;
    }
      
    gcdval=a;
}

void modularinv(int a,int m) // Calculating the modular inverse
{
    int i,x;
    
    a = a%m;
    
    for(i=0;i<m;i++)
    {
       if ((a*i) % m == 1)
       {
           x=i;
       }
    }
    
    modinv=x;
}

void sub(char cstring,char key) //Subtracting Charachters
{
    string S ("0ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    string L ("0ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
    
     int i,i1;
     int j,j1;
     int x;
     
     if(c=='S')
     {
         
        for(i=1;i<=26;i++)
        {
            if(cstring == S[i])
            {
                i1=i;
            }
        }
        for(j=1;j<=26;j++)
        {
            if(key == S[j])
            {
                j1=j;
            }
        }
         x=abs((i1-j1+26)%26);
         if(x==0)
         {
             subval=26;
         }
         else
         {
             subval=x;
         }
         
     }
     else
     {
        for(i=1;i<=52;i++)
        {
            if(cstring == L[i])
            {
                i1=i;
            }
        }
        for(j=1;j<=52;j++)
        {
            if(key == L[j])
            {
                j1=j;
            }
        }
         
         x=abs((i1-j1+52)%52);
         
         if(x==0)
         {
             subval=52;
         }
         else
         {
             subval=x;
         }
     }
}