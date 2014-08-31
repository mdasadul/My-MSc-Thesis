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
    mapfromSet Csize;
    double cost,delay;
    set_set_int edgeset;
    maploc locmap;
};
  typedef   std::deque<Rows> tbl;
    std::deque<tbl>dbase,dbase1;
    double Dist[100][10];
    int C_size;
    deque<q_int> posdb;
    double  Tx,Val=1.0/4;
    set_int Target;
    int NN;


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
       
        for(std::deque<set_int>::iterator i=z.begin();i!=z.end();i++)
        {
         if(flag2) i=z.begin();
         set_int t=*i;
         flag2=false;
         for(set_int::iterator mm=t.begin();mm!=t.end();mm++)
         {
            flag=false;
            deque<set_int>::iterator ti=i;
            ++ti;
            for(;ti!=z.end();ti++)
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
                      z.push_back(t);
                      z.erase(i);
                     
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
   // pQueue(z);
    return z;  
}

void pTnode(tbl Table)
{
    int i;
    bool flag=false;
    double c=0,c1=0;
    double A[20];
    int max=0;
    for(i=0;i<Table.size();i++)
        { flag=false;
        max=0;
        bool flag1=false;
       // cout<<setw(5);
             for(set_set_int::iterator it=Table[i].Partition.begin();it!=Table[i].Partition.end();it++)
                 {
                 flag1=false;
                        set_int ss=*it;
                        cout<<"{ ";
                        for(set_int::iterator sit=ss.begin();sit!=ss.end();sit++)
                        {
                         cout<<*sit<<" ";
                         if(*sit==1) flag1=true;
                        }
                cout<<"}"<<Table[i].Csize[*it]<<" ";
                if(flag1&&ss.size()+Table[i].Csize[*it]>=C_size)flag=true;
                if(max<ss.size()+Table[i].Csize[*it])max=ss.size()+Table[i].Csize[*it];
                }
        for(int k=1;k<=max;k++)
        {
            A[k]+=Table[i].cost;
        }
       for(set_set_int::iterator it=Table[i].Partition.begin();it!=Table[i].Partition.end();it++)
    {
        set_int ss=*it;
      //  cout<<"{ ";
        for(set_int::iterator sit=ss.begin();sit!=ss.end();sit++)
        {
            cout<<Table[i].locmap[*sit]<<" ";
        }
        //cout<<"}"<<obj.Csize[*it];
       
    }
    cout<<" "<<Table[i].cost;
         //cout<<Table[i].cost;
             if(Table[i].Partition.size()==1)c+=Table[i].cost;
       if(flag) c1+=Table[i].cost;
               printf("\n"); 
        }
    for(int k=1;k<=NN;k++)
    {
        cout<<k<<" "<<A[k]<<endl;
    }
    cout<<"Table cost:="<<c;
    cout<<"Table cost11:="<<c1;
  }

bool Dcheck(tbl &temp,Rows obj)
{   
    bool flag=true,flag1;
    for(int i=0;i<temp.size();i++)
    {
        flag1=false;
        if(temp[i].Partition.size()==obj.Partition.size())
        {
            for(set_set_int::iterator it=temp[i].Partition.begin(),oit=obj.Partition.begin();it!=temp[i].Partition.end();it++,oit++)
            {
                set_int p=*it,q=*oit;
                if(temp[i].Csize[*it]!=obj.Csize[*oit])
                {
                    flag1=true;
                    break;
                }
                if((*it).size()==(*oit).size())
                {
                    for(set_int::iterator sit=p.begin(),soit=q.begin();sit!=p.end();sit++,soit++)
                    {
                        if(*sit!=*soit)
                        {
                            flag1=true;
                            
                            break;
                        }
                        if(temp[i].locmap[*sit]!=obj.locmap[*soit])
                        {
                            flag1=true;
                            //temp[i].cost=temp[i].cost+obj.cost;
                            break;
                        }
                    }
                 
                }
                else
                {
                    flag1=true;
                    break;
                }
            }
          
        }
        else flag1=true;
        
        if(!flag1) 
        {
            flag=false;
            temp[i].cost=temp[i].cost+obj.cost;
            break;
        }
    }
   //if(!flag)temp[i].cost=temp[i].cost+obj.cost;
    return flag;
}
void printobj(Rows obj)
{
    for(set_set_int::iterator it=obj.Partition.begin();it!=obj.Partition.end();it++)
    {
        set_int ss=*it;
        cout<<"{ ";
        for(set_int::iterator sit=ss.begin();sit!=ss.end();sit++)
        {
            cout<<*sit<<" ";
        }
        cout<<"}"<<obj.Csize[*it]<<" ";
       
    }
    for(set_set_int::iterator it=obj.Partition.begin();it!=obj.Partition.end();it++)
    {
        set_int ss=*it;
      //  cout<<"{ ";
        for(set_int::iterator sit=ss.begin();sit!=ss.end();sit++)
        {
            cout<<obj.locmap[*sit]<<" ";
        }
        //cout<<"}"<<obj.Csize[*it];
       
    }
    cout<<" "<<obj.cost;
  
}
bool BadSt(Rows &obj,int es)
{
    bool flag=false;
    Rows ob;
    for(set_set_int::iterator it=obj.Partition.begin();it!=obj.Partition.end();it++)
    {
        bool flg=false;
        set_int ss=*it;
        for(set_int::iterator sit=(*it).begin();sit!=(*it).end();sit++)
        {
            if(*sit==es)
            {
//                if((*it).size()<2&&Target.find(es)!=Target.end()&&obj.tnodeAttach[*it]==1) 
//                {
//                    flag=true;
//                    break;
//                }
                ss.erase(es);
               if(ss.size()>0){ ob.Csize[ss]=obj.Csize[*it]+1;
               flg=true;
               }
                //cout<<"OBJ"<<obj.Csize[*it]<<"ob"<<ob.Csize[ss];
            }
           
            
            
        }
        if(ss.size()>0)
        {
            if(!flg)ob.Csize[ss]=obj.Csize[ss];
            ob.Partition.insert(ss);
            bool f=false;;
            for (set_int::iterator ii=ss.begin();ii!=ss.end();ii++)
            {
                if(Target.find(*ii)!=Target.end())
                {
                    f=true;
                    break;
                }
            }
            
            if(f)ob.tnodeAttach[ss]=1;
            else ob.tnodeAttach[ss]=0;
            for(set_set_int::iterator it1=ob.Partition.begin();it1!=ob.Partition.end();it1++)
            {
                set_int tt=*it1;
                for(set_int::iterator tt1=tt.begin();tt1!=tt.end();tt1++)
                {
                    ob.locmap[*tt1]=obj.locmap[*tt1];
                }
            }
            
        }
        
        if(flag==true)break;
    }
    
    ob.cost=obj.cost;
    
    obj=ob;
     
    return flag;
}
/*This Function will find neighbors nodes of a deleting */
int findMnode(deque<tbl> db,set_int a)
{
    int tContr=0,flag,M;
   for (deque<tbl>::iterator it=db.begin();it!=db.end();++it)
    {
        tbl Table=*it;
        flag=0;
        tContr++;
        set_int allNode;
        for(int i=0;i<Table.size();i++)
        { 
            for (set_set_int::iterator mit=Table[i].Partition.begin();mit!=Table[i].Partition.end();++mit)
            {
               set_int m=*mit; 
                for(set_int::iterator sit=m.begin();sit!=m.end();++sit)
                {
                    allNode.insert(*sit);
                    
                }
             }
        }
        if(allNode==a)
        {
            M=tContr;
            break;
        }
   }
    return M;
}



deque<q_int> findNodes(deque<tbl> db,int es)
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
  for(set_int::iterator sit=s1.begin();sit!=s1.end();sit++)         
 {
      
     set_int::iterator nsit=sit;++nsit;
     for(;nsit!=s1.end();nsit++)
        {
         set_int n;
         n.insert(*sit);
         n.insert(*nsit);
         a=findMnode(db,n);
           T1.push(a);    
         }
 }    
  r.push_back(T);
   r.push_back(T1);
   return r;
}
void pAllTable1(std::deque<tbl> db)
{
    for (deque<tbl>::iterator it=db.begin();it!=db.end();++it)
    {
        tbl Table=*it;
        pTnode(Table);
    }
}
void pAllTable(std::deque<tbl> db)
{
   
    for (deque<tbl>::iterator it=db.begin();it!=db.end();++it)
    {
        tbl Table=*it;
      double c=0,d=0;
        for(int i=0;i<Table.size();i++)
        {
            if(i%2==0)cout<<endl;

//             for (std::map<set_int,int>::iterator mit=Table[i].tnodeAttach.begin();mit!=Table[i].tnodeAttach.end();++mit)
//                {
//                        printf("{ ");
//                        for(set_int::iterator sit=mit->first.begin();sit!=mit->first.end();++sit)
//                        {
//                            printf("%d ",*sit);
//
//                        }
//                cout<<"}:"<<mit->second<<"  ";
//                 }
               for (std::map<set_int,int>::iterator mit=Table[i].Csize.begin();mit!=Table[i].Csize.end();++mit)
                {
                        printf("{ ");
                        for(set_int::iterator sit=mit->first.begin();sit!=mit->first.end();++sit)
                        {
                            printf("%d ",*sit);

                        }
                cout<<"}:"<<mit->second<<"  ";
                 }
           for (std::map<int,int>::iterator mit=Table[i].locmap.begin();mit!=Table[i].locmap.end();++mit)
                {
                        cout<<mit->second<<" ";
                }
             cout<<Table[i].cost<<" ";
              //cout<<Table[i].delay;
             if(Table[i].Partition.size()==1)
             {
                 c+=Table[i].cost;
                 d+=Table[i].delay;
             }
                printf("\n");
        }
        //printf("\n");
    cout<<"Total Cost= "<<c;  
   // cout<<"     Total delay="<<d; 
    cout<<"\n\n\n";
      }
    
}

double EuclDist(double x1,double y1,double x2,double y2)
{
    
    double temp;
    temp= sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
  
    return temp;
}


void Preprocess(q_int &ElSeq)
{
    
    std::ifstream input("exp2_10");
    std::string line;
     
  freopen("output.txt","w",stdout);
    printf("Elimination sequence :=");
    getline(input,line);
    istringstream is(line );
    int n;
    while(is >> n ) 
    {
       ElSeq.push(n);
        cout<<"   "<<n<<"  ";
    }
    printf("\n C_Size ");
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
    
    is2>>NN;
    printf("\n Node#  PoN IG(X     Y)   EG(X   Y)    NX   NY\n");
    for(int k=0;k<NN;k++)
    {
        q_int a,b;
         q_double m;
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
        

        cout<<endl;
        posdb.push_back(a);
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
        
        
        q_int a1,b;
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
//                          q_int n,m,p;
                     obj.delay=0;
                     obj1.delay=0;
                         //y2=double(j1+j1+1)/2;
                         x2=q[k1];
                         k1++;
                         y2=q[k1];
                         dist=EuclDist(x1,y1,x2,y2);
                    if(dist!=0)  obj1.delay=1/dist;
                         
                         obj.tnodeAttach[temp]=0;
                         obj1.tnodeAttach[temp1]=0;
                         obj1.tnodeAttach[temp2]=0;
                       
                         obj1.Csize[temp1]=0;
                         obj1.Csize[temp2]=0;
                         obj.Csize[temp]=0;
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

tbl pmTable(tbl Table1,tbl Table2,int com)
    {
       tbl temp;
       int x=1;
       for(int i=0;i<Table1.size();++i)
        {
          
           for(int j=0;j<Table2.size();j++)
             { 
              
                        if(Table1[i].locmap[com]==Table2[j].locmap[com])
                        {
//                            cout<<"Rowi ";
//                            printobj(Table1[i]);
//                            cout<<"\n Rowj";
//                            printobj(Table2[j]);
                        Rows obj;  
                        x=Table1[i].locmap[com];
                       // cout<<x<<" ";
                        bool flag=true,flag1=false;
                        std::deque<set_int> z,z1,t;
                        for(set_set_int::iterator it=Table1[i].Partition.begin();it!=Table1[i].Partition.end();it++)
                        { 
                            z.push_back(*it);
                        }
                        
                        for (set_set_int::iterator ite=Table2[j].Partition.begin();ite!=Table2[j].Partition.end();ite++)
                        {
                           z1.push_back(*ite);
                        }
                        
                         t=mPar(z,z1);
                        
                        for(deque<set_int>::iterator it=t.begin();it!=t.end();it++)
                        {
                            set_int tt=*it;
                            obj.Partition.insert(tt);
                        }
                         
                         for(set_set_int::iterator it=obj.Partition.begin();it!=obj.Partition.end();it++)
                         {
                             set_int ite=*it;
                             for(set_int::iterator nit=ite.begin();nit!=ite.end();nit++)
                             {
                                 if(Table1[i].locmap[*nit]!=0)
                                 obj.locmap[*nit]=Table1[i].locmap[*nit];
                                 else obj.locmap[*nit]=Table2[j].locmap[*nit];
                             }
                         }
                         //find the sum of partition size
                         
                         
                         for(set_set_int::iterator it=Table1[i].Partition.begin();it!=Table1[i].Partition.end();it++)
                         {  bool flag=false;
                             for(set_int::iterator it1=(*it).begin();it1!=(*it).end();it1++)
                             {
                                 for(set_set_int::iterator oit=obj.Partition.begin();oit!=obj.Partition.end();oit++)
                                 {
                                     for(set_int::iterator soit=(*oit).begin();soit!=(*oit).end();++soit)
                                     {
                                         if(*it1==*soit&&!flag)
                                         {
                                             flag=true;
                                             obj.Csize[*oit]+=Table1[i].Csize[*it];
                                         }
                                     }
                                 }
                             }
                         }
                           for(set_set_int::iterator it=Table2[j].Partition.begin();it!=Table2[j].Partition.end();it++)
                         {  bool flag=false;
                             for(set_int::iterator it1=(*it).begin();it1!=(*it).end();it1++)
                             {
                                 for(set_set_int::iterator oit=obj.Partition.begin();oit!=obj.Partition.end();oit++)
                                 {
                                     for(set_int::iterator soit=(*oit).begin();soit!=(*oit).end();++soit)
                                     {
                                         if(*it1==*soit&&!flag)
                                         {
                                             flag=true;
                                             obj.Csize[*oit]+=Table2[j].Csize[*it];
                                         }
                                     }
                                 }
                             }
                         }

                        // finding Max
                          for(set_set_int::iterator it=obj.Partition.begin();it!=obj.Partition.end();it++)
                         {
                           for(set_int::iterator iit=(*it).begin();iit!=(*it).end();iit++)
                           {
                            bool flag=false;
                            for(set_set_int::iterator t1i=Table1[i].Partition.begin();t1i!=Table1[i].Partition.end();t1i++)
                            {
                                for(set_int::iterator t11=(*t1i).begin();t11!=(*t1i).end();t11++)
                                {
                                   if(*iit==*t11)
                                   {
                                       obj.tnodeAttach[*it]=max(obj.tnodeAttach[*it],Table1[i].tnodeAttach[*t1i]); 
                                   flag=true;
                                   break;
                                   }
                                }
                            }
                                for(set_set_int::iterator st1i=Table2[j].Partition.begin();st1i!=Table2[j].Partition.end();st1i++)
                                { 
                                    for(set_int::iterator s11=(*st1i).begin();s11!=(*st1i).end();s11++)
                                    {
                                        if(*iit==*s11)
                                        {
                                            obj.tnodeAttach[*it]=max(obj.tnodeAttach[*it],Table2[j].tnodeAttach[*st1i]);
                                         flag=true;
                                         break;
                                        }
                                           
                                        }
                                    }
                              

                                }        
                         }
                          //
                         
                         obj.cost=(Table1[i].cost*Table2[j].cost)/Dist[com-1][x-1];
                         obj.delay=Table1[i].delay+Table2[j].delay;
//                         cout<<"\n beforeF";
//                         printobj(obj);
                       flag1=BadSt(obj,com);
//                        cout<<"\n afterF";
//                       if(!flag1)
//                       printobj(obj);
                      if(temp.size()>0) 
                      flag=Dcheck(temp,obj);
                    
                       if(flag&&!flag1)
                       {
                          
                         temp.push_back(obj);
                       }
                       
                    }
                        
             }
            
        }
        return temp;
    }


tbl pmTable1(tbl Table1,tbl Table2)
    {
       tbl temp;
       int pq[3];
       for(int i=0;i<Table1.size();++i)
        {
           //cout<<Table1.size()<<" ";
                    for(int j=0;j<Table2.size();j++)
                    { bool f=true;
                       
                        if(Table1[i].locmap==Table2[j].locmap)
                        {
                        Rows obj;
//                        printobj(Table1[i]);
//                        cout<<"\n Second";
//                        printobj(Table2[j]);
                        bool flag=true,flag1=false;
                        std::deque<set_int> z,z1,t;
                        for(set_set_int::iterator it=Table1[i].Partition.begin();it!=Table1[i].Partition.end();it++)
                        { 
                            z.push_back(*it);
                        }
                        
                        for (set_set_int::iterator ite=Table2[j].Partition.begin();ite!=Table2[j].Partition.end();ite++)
                        {
                           z1.push_back(*ite);
                        }
                        
                         t=mPar(z,z1);
                        
                        for(deque<set_int>::iterator it=t.begin();it!=t.end();it++)
                        {
                            set_int tt=*it;
                            obj.Partition.insert(tt);
                        }
                         pq[0]=0;pq[1]=0;
                          int k=0;
                         for(set_set_int::iterator it=obj.Partition.begin();it!=obj.Partition.end();it++)
                         {
                             set_int ite=*it;
                            
                             for(set_int::iterator nit=ite.begin();nit!=ite.end();nit++)
                             {
                                 obj.locmap[*nit]=Table1[i].locmap[*nit];
                                 pq[k]=*nit;
                                 k++;
                             }
                         }
                          
                          //finding sum of partition size
                        for(set_set_int::iterator it=Table1[i].Partition.begin();it!=Table1[i].Partition.end();it++)
                         {  bool flag=false;
                             for(set_int::iterator it1=(*it).begin();it1!=(*it).end();it1++)
                             {
                                 for(set_set_int::iterator oit=obj.Partition.begin();oit!=obj.Partition.end();oit++)
                                 {
                                     for(set_int::iterator soit=(*oit).begin();soit!=(*oit).end();++soit)
                                     {
                                         if(*it1==*soit&&!flag)
                                         {
                                             flag=true;
                                             obj.Csize[*oit]+=Table1[i].Csize[*it];
                                         }
                                     }
                                 }
                             }
                         }
                           for(set_set_int::iterator it=Table2[j].Partition.begin();it!=Table2[j].Partition.end();it++)
                         {  bool flag=false;
                             for(set_int::iterator it1=(*it).begin();it1!=(*it).end();it1++)
                             {
                                 for(set_set_int::iterator oit=obj.Partition.begin();oit!=obj.Partition.end();oit++)
                                 {
                                     for(set_int::iterator soit=(*oit).begin();soit!=(*oit).end();++soit)
                                     {
                                         if(*it1==*soit&&!flag)
                                         {
                                             flag=true;
                                             obj.Csize[*oit]+=Table2[j].Csize[*it];
                                         }
                                     }
                                 }
                             }
                         }
                    //finding Max
                          for(set_set_int::iterator it=obj.Partition.begin();it!=obj.Partition.end();it++)
                         {
                           for(set_int::iterator iit=(*it).begin();iit!=(*it).end();iit++)
                           {
                            bool flag=false;
                            for(set_set_int::iterator t1i=Table1[i].Partition.begin();t1i!=Table1[i].Partition.end();t1i++)
                            {
                                for(set_int::iterator t11=(*t1i).begin();t11!=(*t1i).end();t11++)
                                {
                                   if(*iit==*t11)
                                   {
                                       obj.tnodeAttach[*it]=max(obj.tnodeAttach[*it],Table1[i].tnodeAttach[*t1i]); 
                                   flag=true;
                                   break;
                                   }
                                }
                            }
                                for(set_set_int::iterator st1i=Table2[j].Partition.begin();st1i!=Table2[j].Partition.end();st1i++)
                                { 
                                    for(set_int::iterator s11=(*st1i).begin();s11!=(*st1i).end();s11++)
                                    {
                                        if(*iit==*s11)
                                        {
                                            obj.tnodeAttach[*it]=max(obj.tnodeAttach[*it],Table2[j].tnodeAttach[*st1i]);
                                         flag=true;
                                         break;
                                        }
                                           
                                        }
                                    }
                              

                                }        
                         }
                        double ii=Dist[pq[0]-1][Table1[i].locmap[pq[0]]-1];
                        double jj=Dist[pq[1]-1][Table1[i].locmap[pq[1]]-1];
                        obj.cost=((Table1[i].cost*Table2[j].cost)/(ii*jj));
                       
                        if(Table1[i].cost>=Table2[j].cost)
                        obj.delay=Table1[i].delay;
                      else     obj.delay=Table2[j].delay;
//                        cout<<"\n before";
//                        printobj(obj);
                      if(temp.size()>0) 
                      flag=Dcheck(temp,obj);
//                        cout<<"\n After";
//                     printobj(obj);
                       if(flag&&!flag1)
                         temp.push_back(obj);
                    }
                }
        }
     
        return temp;
    }

 int main()
{

   int es;
   q_int ElSeq;
   Preprocess(ElSeq);
    
   
   dbase1=dbase;
   cout<<endl<<endl<<"DataBase: "<<endl;
   pAllTable(dbase);
  
   tbl Temp2;
    for(;ElSeq.size()>2;)
    {
        es=ElSeq.front();
        ElSeq.pop();
        int t1,t2,t3;
        deque<q_int> r;
        q_int T,T1,tt,tt1;
        
        r=findNodes(dbase ,es);
        for(deque<q_int>::iterator it=r.begin();it!=r.end();it++)
        {
            T=*it;
            it++;
            T1=*it;
        }
        tt=T;
        int a[T.size()+2],ii=1;
        
        for(;!tt.empty();)
        {
            a[ii]=tt.front()-1;
            tt.pop();
            ii++;
        }
        tt1=T1;
        int b[T1.size()+2],jj=1;
        
        for(;!tt1.empty();)
        {
            b[jj]=tt1.front()-1;
            tt1.pop();
            jj++;
        }
        
        int k=1;
        for(int i=1;i<=T.size();i++)
        {
            for(int j=i+1;j<=T.size();j++)
            {
                t1=a[i];t2=a[j]; t3=b[k];
                k++;
                 pTnode(dbase[t1]);
                pTnode(dbase[t2]);
                Temp2=pmTable(dbase[t1],dbase[t2],es);
                cout<<"Begin:\n";
               pTnode(Temp2);
                cout<<"End\n";
                pTnode(dbase[t3]);
                dbase[t3]=pmTable1(Temp2,dbase[t3]);
                cout<<endl<<t3<<"Final\n";
                pTnode(dbase[t3]);
                cout<<endl;
            } 
        }
        
        //   pAllTable(dbase);
          // cout<<"sep\n";
        for(int i=T.size();i>=1;i--)
        {
            for(int nn=a[i];nn<dbase.size()-1;nn++)
                dbase[nn]=dbase[nn+1];
            
            dbase.pop_back();
        }
        
          // pAllTable(dbase);
    }
   
   cout<<"\n FinalDB \n";
    pAllTable1(dbase);
  
return 0;
}
