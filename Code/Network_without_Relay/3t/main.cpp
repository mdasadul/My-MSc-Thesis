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
#include<list>
//#include <boost/lexical_cast.hpp>

using namespace std;

typedef std::set<int> set_int ;
typedef std::queue<int> q_int;
typedef std::queue<long double> q_double;
typedef std::set<set_int> set_set_int;
typedef std::map<set_int, int> mapfromSet;
/*Structure with four member field*/
typedef std::map<int,int>maploc;

struct Rows
{
    set_set_int Partition;
    mapfromSet tnodeAttach;
    mapfromSet Csize;
   long double cost,delay;
    set_set_int edgeset;
    maploc locmap;
};
      
    
int C_size;

  typedef   std::deque<Rows> tbl;
    std::deque<tbl>dbase,dbase1,tdb;
    set_int Target;q_int ElSeq;
     deque<q_int> posdb;
   long double  Tx,Val=1.0/4;
    long double Dist[100][10];
    int NN;
   
    void pQueue(deque<set_int> z)
    {
        cout<<endl;
        for(deque<set_int>::iterator i=z.begin();i!=z.end();i++)
        {
            for(set_int::iterator i1=(*i).begin();i1!=(*i).end();i1++)
            {
                cout<<" "<<*i1;
            }
        }
    }
/*This Function will merge two Partition*/
deque<set_int> mPar(deque<set_int> z,deque<set_int> z1)
{
    bool flag=false;
//    deque<set_int> temp;
//    if(z.size()>=z1.size()){
        
    
            for(std::deque<set_int>::iterator j=z1.begin();j!=z1.end();j++)    
            {

                z.push_back(*j);

            }
    
   
//  pQueue(z);
    //cout<<endl;
   bool flag1;
    
  while(true)    {
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
            deque<set_int>::iterator t2,ti=i;
            ++ti;
            //if(z.size()>1)
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
//                      temp=z;
//                        pQueue(z);
//                       temp.erase(i);
//                       temp.push_back(t);
//                        temp.erase(ti);
//                        z=temp;
//                      for(deque<set_int>::iterator iterat=z.begin();iterat!=z.end();iterat++)
//                      {
//                          set_int itera=*iterat;
//                         // itera.va
////                         if(itera!=i) 
//                             temp.push_back(itera);
//                      }
                      z.push_back(t);
//                       pQueue(z);
                      z.erase(i);
                      
//                      pQueue(z);
//                      z.push_front(t);
//                     // z.push_back(t);
//                      pQueue(z);
                        z.erase(ti);
//                        pQueue(z);
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
        if(!flag1) break;    }
    //cout<<"value"<<endl;    
   //pQueue(z);
   //cout<<endl; 
    return z;  
    
}
tbl mtable(tbl Table)
{
    tbl temp;
    bool flag=false;
    Rows obj=Table[0];
   temp.push_back(obj);
    for(int i=1;i<Table.size();i++)
    {
        list<int> set,t;
       
       for(set_set_int::iterator it11=Table[i].Partition.begin();it11!=Table[i].Partition.end();it11++)
        {
            
         for(set_int::iterator sit=(*it11).begin();sit!=(*it11).end();sit++)   
         {
             set.push_back(Table[i].locmap[*sit]);
             
         }
        }
            int j=0;
            bool flg=false;
      for(j=0;j<temp.size();j++)
      { t=set;
      list<int> p;
       flag=false;
           for(set_set_int::iterator it1=temp[j].Partition.begin();it1!=temp[j].Partition.end();it1++)
        {
              
               for(set_int::iterator it2=(*it1).begin();it2!=(*it1).end();it2++)
               {
                   p.push_back(temp[j].locmap[*it2]);
               }
           }
       p.sort();
       t.sort();
       while(!t.empty()&&!p.empty())
       {
           if(p.front()!=t.front())
           {
               flag=true;
               break;
           }
           else {
               p.pop_front();
               t.pop_front();
           }
       }
       if(!flag)
               {
          // Rows s=temp[j];
                   temp[j].cost=temp[j].cost+Table[i].cost;
                   //s.cost+=Table[i].cost;
                  
                   flg=true;
                   break;
               }
               
            
        
        }
            if(!flg){
                   temp.push_back(Table[i]);
             
               }
            
    }
    return temp;
}
void pTnode(tbl Table)
{
   // Table=mtable(Table);
    int i;
    bool flag=false;
    long double c=0,c1=0,c3=0;
   long double A[20];
    int max=0;
    for(i=0;i<20;i++)A[i]=0;
    for(i=0;i<Table.size();i++)
        { flag=false;
        max=0;
        bool flag1=false;
       // cout<<setw(5);
        if(1)
        {
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
    printf("%.12Lf ",Table[i].cost);
         c3+=Table[i].cost;
             if(Table[i].Partition.size()==1)c+=Table[i].cost;
       if(flag) c1+=Table[i].cost;
               printf("\n"); 
    }
    }   
    for(int k=1;k<=NN;k++)
    {
        //cout<<k<<" "<<lexical_cast<string>(A[k])<<endl;
        printf("%d %.12Lf\n",k,A[k]);
    }
    cout<<"Connectivity where all are in one partition:="<<c<<endl;
    cout<<"Connectivity when sink is connected with at least n_req nodes="<<c1<<endl;
    cout<<"Total Connectivity="<<c3<<endl;
  }
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
            //cout<<endl<<obj.cost<<" "<<temp[i].cost;
            temp[i].cost=temp[i].cost+obj.cost;
            //cout<<endl<<"After Adding "<<temp[i].cost;
            break;
        }
    }
   //if(!flag)temp[i].cost=temp[i].cost+obj.cost;
    return flag;
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
                if(ss.size()>0)
                {
                    ob.Csize[ss]=obj.Csize[*it]+1;
                    flg=true;
                }
            }
            
            
        }
        if(ss.size()>0)
        {
            if(!flg) ob.Csize[ss]=obj.Csize[ss];
            ob.Partition.insert(ss);
            
            //ob.tnodeAttach[ss]=obj.tnodeAttach[*it
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
/*This Function will merge two Table Partition*/
              
tbl mTable(tbl Table1,tbl Table2,int com)
    {
       tbl temp;
       int x=1;
       for(int i=0;i<Table1.size();++i)
        {
           //cout<<Table1.size()<<" ";
           for(int j=0;j<Table2.size();j++)
             { 
              // cout<<x<<" ";x++;
                       if(Table1[i].locmap[com]==Table2[j].locmap[com])                       {
                        Rows obj;  
                        x=Table1[i].locmap[com];
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
                          //
                         obj.cost=(Table1[i].cost*Table2[j].cost)/Dist[com-1][x-1];
                       //flag1=BadSt(obj,com);
                       
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

tbl mTable1(tbl Table1,tbl Table2,set_int f)
    {
    set_int::iterator ii=f.begin();
    int com=*ii,com1=*(++ii);
       tbl temp;
       int x=1;
       
       for(int i=0;i<Table1.size();++i)
        {
           //cout<<Table1.size()<<" ";
           for(int j=0;j<Table2.size();j++)
             { 
              // cout<<x<<" ";x++;
                      if(Table1[i].locmap[com]==Table2[j].locmap[com]&&Table1[i].locmap[com1]==Table2[j].locmap[com1])                       
                      {
                        Rows obj;    
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
                          //
                         long double ii=Dist[com-1][Table1[i].locmap[com]-1],jj=Dist[com1-1][Table1[i].locmap[com1]-1];
                         obj.cost=(((Table1[i].cost*Table2[j].cost)/ii)/jj);
                       //flag1=BadSt(obj,com);
                       
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
/*
tbl mTable3(tbl Table1,tbl Table2,int es)
    {
        tbl temp,ttt;
       for(int i=0;i<Table1.size();++i)
        {
                    for(int j=0;j<Table2.size();j++)
                    { 
                        Rows obj;
                        
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
                            
                            //for(set_int::iterator qq=tt.begin();qq!=tt.end();qq++)
                            obj.Partition.insert(tt);
                            
                        }
                         
                      
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
                                //if(flag)break;

                                }        
                         }
                         
                        
//                        for(set_set_int::iterator sit=Table1[i].edgeset.begin();sit!=Table1[i].edgeset.end();sit++)
//                        { 
//                            obj.edgeset.insert(*sit);
//                        }
//
//                        for(set_set_int::iterator sit=Table2[j].edgeset.begin();sit!=Table2[j].edgeset.end();sit++)
//                        {
//                            obj.edgeset.insert(*sit);
//                        }
//                          obj.cost=0;
//                          
//                         for(set_set_int::iterator sit=obj.edgeset.begin();sit!=obj.edgeset.end();sit++)
//                         {
//                             int r=0;
//                             
//                           
//                              r=findMnode(dbase1,*sit);
//                             obj.cost+=dbase1[r-1][0].cost;
//                         }
                         
                       flag1=BadSt(obj,es);
                    
                      if(temp.size()>0) 
                      flag=Dcheck(temp,obj);
                      
                      //cout<<endl;
                        if(flag&&!flag1)
                         temp.push_back(obj);
                    }
            
        }
        //pTnode(ttt);
        return temp;
    }
*/
/*This Function will find neighbors nodes of a deleting */

int findMnode3(deque<tbl> db,int a,int b,int c)
{
    //cout<<a<<b<<c;
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
        if(allNode.find(a)!=allNode.end()&&allNode.find(b)!=allNode.end()&&allNode.find(c)!=allNode.end())
        {
            M=tContr;
            break;
        }
   }
    return M;
}

deque<q_int> findNodes(int es)
{
    deque<tbl> db=dbase;
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
                {   if(flag==1&&*sit!=es)
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
     
  r.push_back(T);
   
   return r;
}
q_int findNodes3(deque<tbl> db,int es)
{
   q_int T,T1;
   deque<q_int> r;
   std::deque<tbl>::iterator it;
   int j=0,flag=0,k=1,a,b;
   
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
                {   if(flag==1&&*sit!=es)
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
   int aa[s1.size()+1],i=0;
 for(set_int::iterator sit=s1.begin();sit!=s1.end();sit++)         
 { aa[i]=*sit;i++;
    
 }         
   
         int a1=findMnode3(db,aa[0],aa[1],aa[2]);
           T.push(a1);
   //r.push_back(T);
  // r.push_back(T1);
   return T;
}

void pAllTable(std::deque<tbl> db)
{
   
    for (deque<tbl>::iterator it=db.begin();it!=db.end();++it)
    {
        tbl Table=*it;
        pTnode(Table);
//      double c=0,d=0;
//        for(int i=0;i<Table.size();i++)
//        {
//            //if(i%2==0)cout<<endl;
////             for (set_set_int::iterator it=Table[i].Partition.begin();it!=Table[i].Partition.end();it++)
////            {
////                set_int T=*it;
////                cout<<"{";
////                for(set_int::iterator t=T.begin();t!=T.end();t++)
////                {
////                    cout<<*t<<" ";
////                }
////                cout<<"}";
////            }
////             cout<<"   ";
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
//           for (std::map<int,int>::iterator mit=Table[i].locmap.begin();mit!=Table[i].locmap.end();++mit)
//                {
//                        cout<<mit->second<<" ";
//                }
//             cout<<Table[i].cost<<" ";
//              //cout<<Table[i].delay;
//             if(Table[i].Partition.size()==1)
//             {
//                 c+=Table[i].cost;
//                 //d+=Table[i].delay;
//             }
//                printf("\n");
//        }
//        //printf("\n");
//    cout<<"Total Cost= "<<c;  
//   // cout<<"     Total delay="<<d; 
//    cout<<"\n\n";
      }
    
}


long double EuclDist(long double x1,long double y1,long double x2,long double y2)
{
    
    long double temp;
    temp= sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
    //cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<" "<<temp;
    return temp;
}
void Preprocess()
{
    int i,nx,ny;
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
    printf("\n Component Size ");
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
        long double n;
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
        

       // cout<<endl;
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
    //cout<<endl;
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
    long double p[a1.size()+1],q[b.size()+1];
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
       
    long double x1,y1,x2,y2,dist;
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
                         
                         
                         obj1.Csize[temp1]=0;
                         obj1.Csize[temp2]=0;
                         obj.Csize[temp]=0;
                         
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
/*
                          obj1.Partition.insert(temp1);
                          obj1.Partition.insert(temp2);
                          obj1.locmap[a[0]]=Cntr;
                          obj1.locmap[a[1]]=Cntr1;
                          obj1.cost=0;
                         
                       Table.push_back(obj1); 
 */
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





set_int searchP(tbl Table1,tbl Table2)
{
    set_int r,temp,Rval;
    for(set_set_int::iterator iit=Table1[0].Partition.begin();iit!=Table1[0].Partition.end();iit++)
    {
        set_int p=*iit;
    for(set_int::iterator it=p.begin();it!=p.end();it++)
    {
        r.insert(*it);
    }
    }
    temp=r;
   for(set_set_int::iterator iit=Table2[0].Partition.begin();iit!=Table2[0].Partition.end();iit++)
   {
       set_int q=*iit;
    for(set_int::iterator it=q.begin();it!=q.end();it++)
    {
        temp.insert(*it);
        if(temp.size()==r.size())Rval.insert(*it);
        else temp.erase(*it);
    }
   }
    return Rval;
}
/*This Function will merge two Table Partition*/
  tbl mTab_final(tbl Table1,tbl Table2,int es)
    {
       tbl temp;
       int x=1;
        set_int com=searchP(Table1,Table2);
//        cout<<" Common Nodes";
//        for(set_int::iterator it=com.begin();it!=com.end();it++)
//               {
//                   cout<<*it<<" ";
//                   //if (Table1[i].locmap[*it]!=Table2[j].locmap[*it])flg=true;
//               }
       for(int i=0;i<Table1.size();++i)
        {
           //cout<<Table1.size()<<" ";
           for(int j=0;j<Table2.size();j++)
             { 
              // cout<<x<<" ";x++;
               bool flg=false;
               for(set_int::iterator it=com.begin();it!=com.end();it++)
               {
                   //cout<<*it<<" ";
                   if (Table1[i].locmap[*it]!=Table2[j].locmap[*it])flg=true;
               }
                       if(!flg)     
                       {
                        Rows obj;    
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
                          //
                          int t1[com.size()+1],i1=0;
                        for(set_int::iterator it=com.begin();it!=com.end();it++)
                         {
                          t1[i1]=*it;
                          i1++;
                        }
                         
                         long double ii=Dist[t1[0]-1][Table1[i].locmap[t1[0]]-1],jj=Dist[t1[1]-1][Table1[i].locmap[t1[1]]-1],
                                 kk=Dist[t1[2]-1][Table1[i].locmap[t1[2]]-1];
                         
                         if(ii==0||jj==0||kk==0) cout<<"HALTTTTT";
                         obj.cost=(Table1[i].cost*Table2[j].cost)/(ii*jj*kk);
                         //obj.cost=(Table1[i].cost*Table2[j].cost)/(Val*Val*Val);
                       flag1=BadSt(obj,es);
                       
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
tbl mTab(tbl Table1,tbl Table2)
    {
       tbl temp;
       //need to change from here
        set_int com=searchP(Table1,Table2);
       for(int i=0;i<Table1.size();++i)
        {
           //cout<<Table1.size()<<" ";
           for(int j=0;j<Table2.size();j++)
             { 
              // cout<<x<<" ";x++;
               bool flg=false;
               for(set_int::iterator it=com.begin();it!=com.end();it++)
               {
                   int x=*it;
                   if (Table1[i].locmap[x]!=Table2[j].locmap[x])flg=true;
               }
                       if(!flg)     
                       {
                        Rows obj;    
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
                                 //cout<<Table1[i].locmap[*nit]<<" Table 2 Locmap"<<Table2[j].locmap[*nit]<<endl;
                                 if(Table1[i].locmap[*nit]!=0)
                                 obj.locmap[*nit]=Table1[i].locmap[*nit];
                                 else obj.locmap[*nit]=Table2[j].locmap[*nit];
                             }
                         }
                         int t1[3],i1=0;
                        for(set_int::iterator it=com.begin();it!=com.end();it++)
                         {
                          t1[i1]=*it;
                          i1++;
                        }
                         
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
                          //
                        long double ii=Dist[t1[0]-1][Table1[i].locmap[t1[0]]-1],jj=Dist[t1[1]-1][Table1[i].locmap[t1[1]]-1];
                        if(ii>0&&jj>0)
                         obj.cost=(Table1[i].cost*Table2[j].cost)/(ii*jj);
                        else cout<<"DIVISION ERROR";
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
tbl mTab1(tbl Table1,tbl Table2)
    {
       tbl temp;
       int x=1;
        set_int com=searchP(Table1,Table2);
       for(int i=0;i<Table1.size();++i)
        {
           //cout<<Table1.size()<<" ";
           for(int j=0;j<Table2.size();j++)
             { 
              // cout<<x<<" ";x++;
               bool flg=false;
               for(set_int::iterator it=com.begin();it!=com.end();it++)
               {
                   int x=*it;
                   if (Table1[i].locmap[x]!=Table2[j].locmap[x])flg=true;
               }
                       if(!flg)     
                       {
                        Rows obj;    
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
                          //
                         
                         int t1[com.size()+1],i1=0;
                        for(set_int::iterator it=com.begin();it!=com.end();it++)
                         {
                          t1[i1]=*it;
                          i1++;
                        }
                         
                        long double ii=Dist[t1[0]-1][Table1[i].locmap[t1[0]]-1],jj=Dist[t1[1]-1][Table1[i].locmap[t1[1]]-1],
                                 kk=Dist[t1[2]-1][Table1[i].locmap[t1[2]]-1];
                         obj.cost=(Table1[i].cost*Table2[j].cost)/(ii*jj*kk);
                         //obj.cost=(Table1[i].cost*Table2[j].cost)/(Val*Val*Val);
                       //flag1=BadSt(obj,com);
                       
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
int CreateTable()
{

  // int es;
   
   Preprocess();
  

   dbase1=dbase;
 //pAllTable(dbase1);
  
   
   q_int els=ElSeq;
   
    tbl Temp2;
    while(!els.empty())
    {
       int e=els.front();
       //cout<<e;
       els.pop();
        int t1,t2,t3;
        deque<q_int> r;
        q_int T,tt;
        
        r=findNodes(e);
        for(deque<q_int>::iterator it=r.begin();it!=r.end();it++)
        {
            T=*it;
         }
        tt=T;
        int a[T.size()+2],ii=1;
       
        
        for(;!tt.empty();)
        {
            a[ii]=tt.front();
            tt.pop();
            ii++;
        }
       
        for(int i=1;i<=T.size();i++)
        {
            for(int j=i+1;j<=T.size();j++)
            {
                t1=a[i];t2=a[j]; 
                
           
           Temp2=mTable(dbase[t1-1],dbase[t2-1],e);
           //pTnode(Temp2);
           //cout<<endl;
           set_int ss;
          for( set_set_int::iterator it= Temp2[0].Partition.begin();it!=Temp2[0].Partition.end();it++)
          {
           set_int sit=*it;
           for(set_int::iterator ssit=sit.begin();ssit!=sit.end();ssit++)
           {
               ss.insert(*ssit);
           }
          }
           ss.erase(ss.find(e));
           
           t3=findMnode(dbase,ss);
           
           tbl tem=mTable1(Temp2,dbase[t3-1],ss);
           //pTnode(tem);
           
            tdb.push_back(tem);
        
            } 
        }
        
        for(int i=T.size();i>=1;i--)
        {
            for(int nn=a[i]-1;nn<dbase.size()-1;nn++)
                dbase[nn]=dbase[nn+1];
            dbase.pop_back();
        }
    }
    dbase=tdb;
    //ElSeq=els;
return 0;
}
void threeTree()
{
    deque<q_int> r;
    deque<tbl> tempT;
    q_int T,T1,tt;
    tbl temp2;
    int es;
    CreateTable();
    cout<<"dbase3t\n";
    pAllTable(dbase);
     cout<<"dbase 3tEnd\n";
    tempT=dbase;
    T=ElSeq;
    
    while(T.size()>3) 
    {
        es=T.front();
        T1=findNodes3(dbase ,es);
        T.pop();
        tt=T1;
        int a[T1.size()+2],ii=1;
       
        
        for(;!tt.empty();)
        {
            a[ii]=tt.front()-1;
          
            tt.pop();
            ii++;
        }
          cout<<"delete "<<es<<endl;
       pTnode(dbase[a[1]]);
        pTnode(dbase[a[2]]);
        temp2=mTab(dbase[a[1]],dbase[a[2]]);
      cout<<"\n TAbl0" ;pTnode(temp2);cout<<"Xend"<<endl;
//       
        temp2=mTab1(dbase[a[3]],temp2);
//        cout<<"\n TAble1" ; pTnode(dbase[a[3]]);cout<<endl;
//         cout<<"\n TAble2" ; pTnode(temp2);cout<<endl;
        dbase[a[4]]=mTab_final(dbase[a[4]],temp2,es);
        cout<<"delete and final table"<<endl;
       pTnode(dbase[a[4]]);
        for(int i=T1.size()-1;i>=1;i--)
        {
            for(int nn=a[i];nn<dbase.size()-1;nn++)
                dbase[nn]=dbase[nn+1];
            dbase.pop_back();
        }
       
   }
    cout<<"Final:db\n";
     pAllTable(dbase);
      cout<<"Final:db End\n";
     dbase=tempT;
}
int main()
{
//    long double a=0.00390625, b=0.0078125;
//    long double c=a+b;
//    printf("%.12Lf",c);
//    deque<set_int> z1,z2;
//    set_int k,j,l,m,n,o,p;
//    k.insert(2);
//    z1.push_back(k);
//    l.insert(3);
//    z1.push_back(l);
//    j.insert(8);
//    z1.push_back(j);
//    m.insert(9);
//    z1.push_back(m);
//    p.insert(10);
//    z2.push_back(k);z2.push_back(l);z2.push_back(j);//z1.push_back(p);
//    z1=mPar(z2,z1);
//    pQueue(z1);
    
    threeTree();
}
