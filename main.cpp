#include <cstdlib>
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

typedef struct TNode {
    string who,
           action,
           followers[250],
           by;
    int num;
	int arrLen;
    TNode (string s1, string s2, string pole[250], int c)
    {
          who = s1;
          action = s2;
          for (int i = 0; i<c; i++)
          {
              followers[i] = pole[i];
              
          }
    }
    TNode (string master, string act, string slave, int number)
    {
          who = master;
          action = act;
          by = slave;
          num = number;
    }
}TNode;

struct names{
   string name;
   string shape;
   int distance;
};

void search(names *& name, int & len, string who, bool follower )
{
	bool possible = true;
	for ( int i = 0 ; i < len ; i ++ )
	{
		if ( name[i].name == who )
		{
			if ( follower )
			{
				name[i].shape = "house";
				name[i].distance = 1;
				cout << "prepsano name[" << i << "] : " << name[i].name << " " << name[i].shape  << " " << name[i].distance << endl;
				break;
			}
			else
			    possible = false;
			
		}
	}
	if ( follower )
	{
		len += 1;
		name[len].name = who;
		name[len].shape = "house";
		name[len].distance = 1;
		cout << "vytvoren follower name[" << len << "] : " << name[len].name << " " << name[len].shape  << " " << name[len].distance << endl;
		possible = false;
	}

	if ( possible )
	{
		len += 1;
		name[len].name = who;
		name[len].shape = "egg";
		name[len].distance = 0;

		cout << "vytvoreno name[" << len << "] : " << name[len].name << " " << name[len].shape  << " " << name[len].distance << endl;
	}
}



int main(int argc, char *argv[])
{
    
    string line, s1, s2;
	int index = 1;
	bool result;
	string master;
	names *name = new names[200];
    char str1[256];
    char str2[256];
    int vstup, pozice = 0;
    TNode **list = new TNode*[1000];

	getline ( cin , master);
	name[0].name = master;
	name[0].shape = "Mdiamond";	
	name[0].distance = 0;
    
	while (1)
    {
     vstup = scanf("%s %s", str1, str2);
     if (vstup == 2)
     {
         string doc1(str1);
         string doc2(str2);

		
		 search ( name, index, doc1, false );
		 
		 if (doc2 == "followedBy:")
         {
          string get;
          getline(cin, get);
		  get += " ";
          int a = 0, b = get.length(), c = 1;
          string pole[256];
          
          for (int i=1; i<b;i++)
          {
              if(get[i] == ' ')
              {
               
					search ( name, index, pole[a], true );
			
					a++;
                    c++;
				    continue;
              }
              else pole[a] += get[i];
          }
          
		  TNode * novy = new TNode(doc1, doc2, pole, c);
          list[pozice] = novy;
          pozice++;
          fflush(stdin); 
         }
         else if (doc2 == "repliedBy:")
         {
              char doc3[256];
              int number;
              if (scanf("%s %d", doc3, &number) == 2)
              {
                  string slave(doc3);
                  TNode * novy = new TNode(doc1, doc2, slave, number);
                  list[pozice] = novy;
                   pozice++;
              }
             
               fflush(stdin); 
         }
         else if (doc2 == "retweetedBy:")
         {
              char doc3[256];
              int number;
              if (scanf("%s %d", doc3, &number) == 2)
              {
                 string slave(doc3);
                  TNode * novy = new TNode(doc1, doc2, slave, number);
                  list[pozice] = novy;
                   pozice++;
              }
               fflush(stdin); 
         }
     }
     else
     {
         cout << "konec vstupu" << endl;
         break;
     }
    }
    for (int i = 0; i < pozice; i++)
     {
		cout << list[i]->who << " " << list[i]->action << " " << endl;
     }
    system("PAUSE");
    return 0;
}
