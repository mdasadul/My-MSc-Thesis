/* 
 * File:   main.cpp
 * Author: asad
 */

#include<stdio.h>
#include<iomanip>
#include<iostream>
#include<set>
#include<map>
#include<fstream>
#include<deque>
#include<queue>
#include<stdlib.h>
#include<vector>
#include<algorithm>
#include<string.h>
#include<math.h>
#include <sstream>

using namespace std;

typedef std::set<int> set_int ;
typedef std::queue<int> q_int;
typedef std::queue<double> q_double;
typedef std::set<set_int> set_set_int;
typedef std::map<set_int, int> mapfromSet;
typedef std::map<int,int>maploc;

struct Rows
{
    set_set_int Partition;
    mapfromSet tnodeAttach;
    double cost;
    set_set_int edgeset;
    maploc locmap;
};


struct row{
    int Node;
      double x,y;
    int Comp_size;
    double Prob;
    maploc tattach;
};
  typedef std::deque<row> node_tbl;
  std::deque<node_tbl> nodeDb;
  typedef   std::deque<Rows> tbl;
  std::deque<tbl>dbase,dbase1;
    
    
    deque<q_double> posdb;
    double Dist[100][18];
    double  Tx,Val=1.0/4,Pr=1,TotalP=0,C_size;
    set_int Target;
    q_int ElSeq;
    
/*This Function will merge two Partition*/
deque<set_int> mPar(deque<set_int> z,deque<set_int> z1)
{
    bool flag=false;
    for(std::deque<set_int>::iterator j=z1.begin();j!=z1.end();j++)    
    {
         z.push_back(*j);
    }
    bool flag1;
    while(true)   
    {
        flag1=false;
        bool flag2=false;
        std::deque<set_int>::iterator jj;
        for(std::deque<set_int>::iterator i=z.begin();i<z.end();i++)
        {
         if(flag2) i=z.begin();
         set_int t=*i;
         flag2=false;
         for(set_int::iterator mm=t.begin();mm!=t.end();mm++)
         {
            flag=false;
            deque<set_int>::iterator t2,ti=i;
            ++ti;
            for(;ti<z.end();ti++)
            {
            set_int t1=*ti;
                for(set_int::iterator m=t1.begin();m!=t1.end();m++)
                {
                    if(*mm==*m)
                    {
                      flag=true;
                      for(set_int::iterator k=t1.begin();k!=t1.end();k++)
                      {
                          t.insert(*k);    
                      }
                      z.erase(i);
                      z.push_front(t);
                      z.erase(ti);
                      break;  
                    }
             }
            if(flag)break;
            }
            if(flag)
            {
                flag1=true;
                flag2=true;
                break;
            }
        }
    }
 if(!flag1) break;  
 }
    return z;  
}

//Printing  all tables
void pAllTable(std::deque<tbl> db)
{
   
    for (deque<tbl>::iterator it=db.begin();it!=db.end();++it)
    {
        tbl Table=*it;
      double c=0;
      if(Table.size()>0){
        for(int i=0;i<Table.size();i++)
        {
            if(i%2==0)cout<<endl;
            
              for (std::map<set_int,int>::iterator mit=Table[i].tnodeAttach.begin();mit!=Table[i].tnodeAttach.end();++mit)
                {
                        printf("{ ");
                        for(set_int::iterator sit=mit->first.begin();sit!=mit->first.end();++sit)
                        {
                            printf("%d ",*sit);

                        }
                cout<<"}:"<<mit->second<<"  ";
                 }
             cout<<"   ";
           for (std::map<int,int>::iterator mit=Table[i].locmap.begin();mit!=Table[i].locmap.end();++mit)
                {
                        cout<<mit->second<<" ";
                }
             cout<<Table[i].cost;
             if(Table[i].Partition.size()==1)c+=Table[i].cost;
                printf("\n");
        }
        //printf("\n");
    cout<<"Total Cost for a TABLE ="<<c; 
   
    Pr*=c;
    cout<<"\n\n";
      }
      }
     cout<<"Total cost="<<Pr; 
}

//Calculate the euclidian distance between two points
double EuclDist(double x1,double y1,double x2,double y2)
{
    
    double temp;
    temp= sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
   //cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<" "<<temp<<endl;
    return temp;
}



q_int findNodes(deque<tbl> db,int es)
{
   q_int T,T1;
   deque<q_int> r;
   std::deque<tbl>::iterator it;
   int j=0,flag=0,a;
   
   set_int s1;
   for (it=db.begin();it!=db.end();++it)
    {
        tbl Table=*it;
        
        j++;
        flag=0;
        for(int i=0;i<Table.size();i++)
        {
               
            for (set_set_int::iterator mit=Table[i].Partition.begin();mit!=Table[i].Partition.end();++mit)
            {
                set_int m=*mit;
                for(set_int::iterator sit=m.begin();sit!=m.end();++sit)
                {   
                    if(flag==1&&*sit!=es)
                      {
                        s1.insert(*sit);
                        
                      }
                
                    if(*sit==es&&!flag)
                    {
                       
                       T.push(j);
                
                        flag=1;
                    }
                    
                }
             }
        }
   }
   for (int i=0;i<s1.size();++i)
       T.push(*s1.begin());
  
   return T;
}

//read input file and create first tables
void Preprocess()
{
    int i,nx,ny;
    std::ifstream input("exp2_10"); //input file 
    std::string line;
     
  freopen("output.txt","w",stdout); // the output file 
    printf("Elimination sequence :=");
    getline(input,line);
    istringstream is(line );
    int n;
    while(is >> n ) 
    {
       ElSeq.push(n);
        cout<<"   "<<n<<"  ";
    }
    
    printf("\n Component Size "); //n_req
    getline(input,line);
    istringstream is11(line);
    is11>>C_size;
    cout<<C_size;
    
    printf("\n Transmission Range ");
    getline(input,line);
    istringstream is1(line);
    is1>>Tx;
    cout<<Tx;
    getline(input,line);
    istringstream is2(line);
    int C;
    is2>>C;
    printf("\n Node#  PoN IG(X     Y)   EG(X   Y)    NX   NY\n");
    row object;
    for(int k=0;k<C;k++)
    {
        q_double a,aa;
        double l[100];
         q_double m;
         node_tbl Tbl;
        getline(input,line);
        istringstream is2(line );
        double n;
        
        int t=0,tem=0;
        while(is2 >> n) 
        {
            a.push(n);
            cout<<"   "<<n<<"  ";
            if(t==1)tem=n;
             if(t>=(2*tem+2))
                 Dist[k][t-2*tem-2]=n;
            t++;
        }
        aa=a;
        int counter=0;
        while(!aa.empty())
        {
            l[counter]=aa.front();
            aa.pop();
            printf("%lf ",l[counter]);
            counter++;
        }
        
        int ccc=0,ccc1=0;
          cout<<"\n";
           object.Node=k+1;
           cout<<object.Node<<endl;
        for(int cnt=2;cnt<2*l[1]+2;cnt=cnt+1)
        {
          
            object.x=l[cnt];
            cout<<object.x<<" ";
            object.y=l[++cnt];
             
            
            cout<<object.y<<" ";
            object.Comp_size=1;
            cout<< object.Comp_size<<" ";
          object.Prob=Dist[k][ccc1++];
           cout<<object.Prob<<"\n";
           ccc++;
            Tbl.push_back(object);
        }
        cout<<endl;
        posdb.push_back(a);
        nodeDb.push_back(Tbl);
     }
    
 
    printf("Target Nodes:=");
    getline(input,line);
    istringstream is3(line );
    while( is3 >> n ) 
    {
        Target.insert(n);
        cout<<"   "<<n<<"  ";
    }
    cout<<endl;
    while( std::getline( input, line ))
    {
        
        
        tbl Table;
        int a[4],k=0;
        set_int temp,temp1,temp2;
        istringstream is4( line );
        is4 >> a[0]>>a[1]; 
        temp.insert(a[0]);
        temp.insert(a[1]);
        temp1.insert(a[0]);
        temp2.insert(a[1]);
        
        
        q_double a1,b;
        a1=posdb[a[0]-1];
    
    b=posdb[a[1]-1];
    
    int i=0;
    double p[a1.size()+1],q[b.size()+1];
    while(!a1.empty())
    {
        p[i]=a1.front();
        //cout<<p[i]<<" ";
        a1.pop();
        i++;
    }
    i=0;
    while(!b.empty())
    {
      q[i]=b.front();
      b.pop();
      i++;
     }
       
    double x1,y1,x2,y2,dist;
    int Cntr=1,Cntr1;
      
          for(int k=2;k<2*p[1]+2;k++)
          {
              
                  
                  x1=p[k];
                  k++;
                  y1=p[k];
              
              
              
            Cntr1=1;
            
                 for(int k1=2;k1<2*q[1]+2;k1++)
                 {
                     Rows obj,obj1;
           
                         x2=q[k1];
                         k1++;
                         y2=q[k1];
                         dist=EuclDist(x1,y1,x2,y2);
                    //if(dist!=0)  obj1.delay=1/dist;
                         
                         obj.tnodeAttach[temp]=0;
                         obj1.tnodeAttach[temp1]=0;
                         obj1.tnodeAttach[temp2]=0;
                          if(Target.find(a[0])!=Target.end()||Target.find(a[1])!=Target.end())obj.tnodeAttach[temp]=1;
                          if(Target.find(a[0])!=Target.end())obj1.tnodeAttach[temp1]=1;
                          if(Target.find(a[1])!=Target.end())obj1.tnodeAttach[temp2]=1;
                      if(dist<=Tx)
                      {
                          obj.Partition.insert(temp);
                          obj.locmap[a[0]]=Cntr;                         
                          obj.locmap[a[1]]=Cntr1; 
                           obj.cost=Dist[int(p[0])-1][Cntr-1]*Dist[int(q[0])-1][Cntr1-1];
                           //if(dist!=0) obj.delay=1/dist;
                          
                          Table.push_back(obj);

                          obj1.Partition.insert(temp1);
                          obj1.Partition.insert(temp2);
                          obj1.locmap[a[0]]=Cntr;
                          obj1.locmap[a[1]]=Cntr1;
                          obj1.cost=0;
                         
                         Table.push_back(obj1); 
                      }
                      else
                          
                      {
                          obj1.Partition.insert(temp1);
                          obj1.Partition.insert(temp2);
                          obj1.locmap[a[0]]=Cntr;
                          obj1.locmap[a[1]]=Cntr1;
                           obj1.cost=Dist[int(p[0])-1][Cntr-1]*Dist[int(q[0])-1][Cntr1-1];
                         Table.push_back(obj1);
                      }
                    
                     Cntr1++;

                 }
             
            Cntr++;
           
          }
     
        
       
        
        dbase.push_back(Table);
        
    }
 }

//Printing a node table 
void printT(node_tbl U)
{
    cout<<endl;
    int k=1;
    double max=0,d=0,d1=0,A[20];
       for(int i=0;i<U.size();i++)
   {
           
       cout<<endl;
             cout<<U[i].Node<<" ";

             if(i==0)
             cout<<"Loc"<<k<<" ";
             else if(U[i].x==U[i-1].x&&U[i].y==U[i-1].y) cout<<"Loc"<<k<<" ";
             else {k++;
             cout<<"Loc"<<k<<" ";
             }
             cout<<U[i].Comp_size<<" ";
             for(int j=1;j<=U[i].Comp_size;j++)
             {
                 A[j]+=U[i].Prob;
             }
             if(max<U[i].Comp_size)max=U[i].Comp_size;
             cout<<U[i].Prob<<" ";
             if(U[i].Comp_size>=C_size)d+=U[i].Prob;
   }
    cout<<endl<<endl;
    
    for(int k=1;k<=max;k++)
        cout<<k<<" "<<A[k]<<endl;
}

//printing information of all nodes
void printDb()
{
   std::deque<node_tbl>::iterator it;
   cout<<endl;
   for(it=nodeDb.begin();it!=nodeDb.end();++it)
   {
       node_tbl u=*it;
       printT(u);
   }
}

//check the duplicate row
bool dcheck(node_tbl &Temp,row obj)
{
    bool flag=false;
  
    for(int i=0;i<Temp.size();i++)
    { 
        if(Temp[i].Node==obj.Node&&Temp[i].x==obj.x&&Temp[i].y==obj.y&&Temp[i].Comp_size==obj.Comp_size)
        {
            
                flag=true;
                Temp[i].Prob+=obj.Prob;
                break;
            
        }
    }
    return flag;
}

// finding and merging two tables
void fndNodes(int up,int es)
{
   
    deque<node_tbl> tempdb;
   std::deque<node_tbl>::iterator it;
   bool flag;
   node_tbl T,F,U;
   
   for (it=nodeDb.begin();it!=nodeDb.end();++it)
    {
        node_tbl Table=*it;
        

        flag=0;
        
        for(int i=0;i<Table.size();i++)
        {    
            if (es==Table[i].Node)
            {   
                    //nodeDb.erase(it); 
                    
                F=Table;
                flag=1;
                break;
            }
         if(up==Table[i].Node)
            {
                
                T=Table;
                flag=1;
                break;
            }
        }
        if(flag==0) tempdb.push_back(Table);
   }

   //printT(T);
   //printT(F);
   set_int a=Target;
  
   double x1,y1,x2,y2,dist;
   
   int k=0;
   for(int i=0;i<T.size();i++)
   {
       row obj;
       obj.Node=T[i].Node;
       
       x1=T[i].x;
       y1=T[i].y;
       for(int j=0;j<F.size();j++)
       {
           
       x2=F[j].x;
       y2=F[j].y;
       dist=EuclDist(x1,y1,x2,y2);
       if(dist<=Tx)
       {

           obj.x=T[i].x;
           obj.y=T[i].y;
           
           if(Target.find(F[j].Node)!=Target.end())
           {obj.Comp_size=T[i].Comp_size+F[j].Comp_size;
           //cout<<F[j].Node<;
           }
           else { obj.Comp_size=T[i].Comp_size+F[j].Comp_size-1;
           
           }
           obj.Prob=T[i].Prob*F[j].Prob;
       }
       else {
          
           obj.x=T[i].x;
           obj.y=T[i].y;
           obj.Comp_size=T[i].Comp_size;
           obj.Prob=T[i].Prob*F[j].Prob;
       }
     
       // cout<<"OBJ"<<obj.x;
      flag=dcheck(U,obj);
      if(!flag)
       U.push_back(obj);
         k++;
       }
       
   }
   printT(U);
   tempdb.push_back(U);
   nodeDb=tempdb;
 
}


//get two nodes locality sets and find the distance between then 
//if they can reach each other then compute the probability
//and update the probability distribution to the parent 
//node
void Ed(int ii,int jj)
{
    q_double a1,b;

    a1=posdb[ii-1];
    fndNodes(ii, jj); 
    b=posdb[jj-1];
    
    int i=0;
    double p[a1.size()+1],q[b.size()+1];
    while(!a1.empty())
    {
        p[i]=a1.front();
        a1.pop();
        i++;
    }
    i=0;
    while(!b.empty())
    {
      q[i]=b.front();
      b.pop();
      i++;
     }
       
    double x1,y1,x2,y2,dist1;
    int Cntr=1,Cntr1;
    //cout<<"Search "<<ii<<"  in the target node";
//     if(Target.find(ii)==Target.end()){ Target.insert(ii);
//     //cout<<ii<<" added in the target";
//     }
   if(Target.find(jj)!=Target.end())
   {
       //row.Node=p[0];
          for(int k=2;k<2*p[1]+2;k++)
          {
              
                  
                  
                  x1=p[k];
                  k++;
                  y1=p[k];
         //         row.x=x1;
           //       row.y=y1;
                  
            Cntr1=1;
            cout<<endl;
            double dd=0;
            
                 for(int k1=2;k1<2*q[1]+2;k1++)
                 {
                    
                         
                         x2=q[k1];
                         k1++;
                         y2=q[k1];
                         dist1=EuclDist(x1,y1,x2,y2);
                     
                      if(dist1<=Tx)
                      {
                          
                          dd+=Dist[int(p[0])-1][Cntr-1]*Dist[int(q[0])-1][Cntr1-1];
                          
                      }
                      else
                          
                      {
                          }
                    
                     Cntr1++;

                 }
            if(dd!=0)
            {//    row.Comp_size++;
            //row.Prob=dd;
            }
            
           if(dd>0) Dist[int(p[0])-1][Cntr-1]=dd;
            
             Cntr++;
             //node_tbl.push_back(row);
          }
     
     }
}
 int main()
{

   int es,avC=1;
   
   Preprocess(); //reading files and create a locality sets table and a probability distribution able
                  //Also create a database with the edges
   dbase1=dbase;
 //cout<<endl<<endl<<"DataBase: "<<endl;
 //pAllTable(dbase);
  
   //tbl Temp2;
    for(;ElSeq.size()>1;)
    {
        es=ElSeq.front(); //removing nodes from the PES
        ElSeq.pop();
     
        deque<q_int> r;
        q_int T,tt;
        double tem[100];
        
       T=findNodes(dbase ,es); //finding the neighbor nodes of the node we are going to eliminate
        tt=T;
        int a[T.size()+2],ii1=1,kk=0;
        
        for(;!tt.empty();)
        {
            a[ii1]=tt.front();
            tt.pop();
            ii1++;
        }
       cout<<"\n When eliminating "<<es<<" update to "<<a[2];
       cout<<endl;
       TotalP=0; 
       q_double a1;
       a1=posdb[a[2]-1];
          int ii=0;
       double p[a1.size()+1];
    while(!a1.empty())
    {
        p[ii]=a1.front();
        a1.pop();
        ii++;
    }
       for(int i=0;i<p[1];i++)
       {//cout<<Dist[a[2]-1][i]<<" ";
       tem[i]=Dist[a[2]-1][i];
       }
       cout<<endl;
        Ed(a[2],es);
        avC++;
        for(int i=0;i<p[1];i++)
        {//cout<<Dist[a[2]-1][i]<<" ";
        TotalP+=Dist[a[2]-1][i];   }
         
        if(TotalP==0)
        {
           
            // Dist[a[2]-1][100]=0;
            for(int i=0;i<p[1];i++)
               Dist[a[2]-1][i]=tem[i]; 
        }
        else {
           kk=Dist[es-1][100]+1;
            Dist[a[2]-1][100]+=kk;
           // cout<<Dist[a[2]-1][100]<<" for"<<a[2];
        }
        cout<<endl;
            for(int nn=a[1]-1;nn<dbase.size()-1;nn++)
                dbase[nn]=dbase[nn+1];
            
            dbase.pop_back();
        
        //cout<<"Total: "<<TotalP;
        TotalP=0;
         avC=Dist[a[2]-1][100]+1;
         // pAllTable(dbase);
    }
    //pAllTable(dbase);
   
 //cout<<"Average Comp_Size="<<avC;
return 0;
}