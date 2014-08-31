
/* 
 Library Files 
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

/*
 Define containers 
 */

typedef std::set<int> set_int ;
typedef std::queue<int> q_int;
typedef std::queue<long double> q_double;
typedef std::set<set_int> set_set_int;     //used for Partitions
typedef std::map<set_int, int> mapfromSet; //Used as aKeys
/*Structure with four member field*/

typedef std::map<int,int>maploc;

/*
 * This structures used to hold a row in a table
 * Partition:-indicate each partition like {v1,v2}
 * 
 * //tnodeAttach:-is used for ARCONN to indicate whether 
 * a sensor node is conned with a a partition or not like {v1,v2}1 where 
 * 1 indicate there is a target node connected with partition {v1,v2}
 * 
 * cost:- is the probability associated with each configuration
 * 
 * locmap:-is the locality sets
 */

struct Rows
{
    set_set_int Partition; 
    mapfromSet tnodeAttach; 
    mapfromSet Csize;       
   long double cost;
    maploc locmap;
};
      
    
    int C_size;         
    typedef   std::deque<Rows> tbl; //defining a table
    std::deque<tbl>dbase,dbase1,tdb; //defining databases of tables
    set_int Target;   // initial container to store all sensor nodes from input
    q_int ElSeq;      //Holds the Perfect Elimination Sequence
    deque<q_int> posdb; //holding locality sets of nodes
    long double  Tx;    //holds Transmission Range
    long double Dist[100][20];  //holds probability distribution
    int NN;                     //holds number of nodes
   
/*This Function perform core operation of  merging two Partitions*/
deque<set_int> mPar(deque<set_int> z,deque<set_int> z1)
{
    bool flag=false;
    
           /* appending z1 at the end of z*/
            for(std::deque<set_int>::iterator j=z1.begin();j!=z1.end();j++)    
            {
                z.push_back(*j);
            }

   bool flag1;   // stop the infinite loop
   
  while(true)    //using infinite loop but will stop by using flag1
  {
        flag1=false;
        bool flag2=false;
        
    for(std::deque<set_int>::iterator i=z.begin();i!=z.end();i++)
    {
       if(flag2) 
           i=z.begin();   //reset after merge operation
       
       set_int t=*i;
       flag2=false;
       
       /* This loop search for a common node between two partition 
        If there is one merge those two partition */
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
 return z;     
}


// Printing contents of a table
void pTnode(tbl Table)
{
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
         c3+=Table[i].cost;
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
    cout<<"Total Table cost Table ="<<c3;
  }


/* It finds and returns a table contains nodes specified by set a */
int findMnode(deque<tbl> db,set_int a)
{
    int tContr=0,flag,M;
   for (deque<tbl>::iterator it=db.begin();it!=db.end();++it)
    {
        tbl Table=*it;
        flag=0;
        tContr++;
        set_int allNode;
        for(int i=0;i<1;i++)
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


/*This function check for duplicate rows while adding it to table
 * temp. If duplicate then add the probability and return false 
 * 
 * Otherwise return true */
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
    return flag;
}


/* This function remove node vi (after merging 
 * vi's associate cliques into it's base clique) and  
 * finds and remove bad partitions*/
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
                    if(Target.find(es)!=Target.end())   
                        ob.Csize[ss]=obj.Csize[*it]+1;
                    else ob.Csize[ss]=obj.Csize[*it];
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


/*This Function  performs Table merge t_merge to 
 * convert 2 tree to 3 tree*/           
tbl mTable(tbl Table1,tbl Table2,int com)
    {
       tbl temp;
       int x=1;
       for(int i=0;i<Table1.size();++i)
        {
           //cout<<Table1.size()<<" ";
           for(int j=0;j<Table2.size();j++)
             { 
                       //make sure that the location of common node is same for both tables    
                       if(Table1[i].locmap[com]==Table2[j].locmap[com])
                       {
                        Rows obj;  
                        x=Table1[i].locmap[com];
                        bool flag=true,flag1=false;
                        std::deque<set_int> z,z1,t;
                        
                        //z and z1 are two partitions send to merge them by p_merge
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
                         //adding locality set to the merged partition
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
                         
                         //updating the component size of newly created partitions
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
                            //updating the t-node Attach variable for every partition
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
                         //Updating the cost of newly created row by dividing the the
                         //common node's corresponding location probability
                         obj.cost=(Table1[i].cost*Table2[j].cost)/Dist[com-1][x-1];
                       //flag1=BadSt(obj,com);
                       
                         
                      /*
                       * Check whether the newly created row is already in the table 
                       * or not. If no inset it to the table temp
                       */   
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
 This function perform same task as p_merge (mTable)
 *  except here the number of common nodes is 2
 * to convert 2 tree to 3 tree
 */
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

/*This Function finds the table associated with node a,b,c
 * and returns the table index of table database
 *  */

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

/*
 * This function returns the table indices containing node es
 * because we will merge those tables
 */
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
        for(int i=0;i<1;i++)
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


/*
 * This function returns the table indices containing node es 
 * and the base table of es
 * because we will merge those tables
 * 
 * Here es is the node we are going to eliminate 
 */
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
                       
                        //getting all table index contains es
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
        //getting the base table index and adding that to T
         int a1=findMnode3(db,aa[0],aa[1],aa[2]);
           T.push(a1);
   //r.push_back(T);
  // r.push_back(T1);
   return T;
}

// Printing all tables in a table database
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

// finds the Euclidian distance between two points
long double EuclDist(long double x1,long double y1,long double x2,long double y2)
{
    
    long double temp;
    temp= sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
    //cout<<x1<<" "<<y1<<" "<<x2<<" "<<y2<<" "<<temp;
    return temp;
}


/*Reads input from files
 * create edge tables 
*/
void Preprocess()
{
    int i,nx,ny;
    std::ifstream input("exp2_10_R"); //input file name
    std::string line;
     
  freopen("output.txt","w",stdout);
  
   /*Reading Elimination sequence from input file*/
    printf("Elimination sequence :=");
    getline(input,line);
    istringstream is(line );
    int n;
    while(is >> n ) 
    {
       ElSeq.push(n);
        cout<<"   "<<n<<"  ";
    }
    
    /*Reading component size n_req from input file*/
    printf("\n Component Size ");
    getline(input,line);
    istringstream is11(line);
    is11>>C_size;
    cout<<C_size;
    
    
    /*Reading Transmission Range from input file*/
    printf("\n Transmission Range ");
    getline(input,line);
    istringstream is1(line);
    is1>>Tx;
    cout<<Tx;
    
    
    /*Reading information about total number of nodes from input file*/
    getline(input,line);
    istringstream is2(line);
    is2>>NN;
    
    /*Reading locality sets and probability distribution for each node from input file*/
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
        

        cout<<endl;
        posdb.push_back(a);
     }
 
    /*Reading the list of sensor nodes from input file*/
    printf("Target Nodes:=");
    getline(input,line);
    istringstream is3(line );
    while( is3 >> n ) 
    {
        Target.insert(n);
        cout<<"   "<<n<<"  ";
    }
    cout<<endl;
    
    /*Reading the edge set for 3 tree
     * which is used to create edge tables with the help of above information
     *  from input file*/
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
                     
                         //y2=double(j1+j1+1)/2;
                         x2=q[k1];
                         k1++;
                         y2=q[k1];
                         dist=EuclDist(x1,y1,x2,y2);
          
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


/*
 This function finds the common nodes between two 
 * tables and return that information
 */
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
/*This Function will merge the last clique(after merging everything into Temp) associated
 *  with v_i with the base clique.
 * Here There are three common nodes between the last base clique and 
 * temp so everything is same as mTab (also mtable which helps to 
 * merge 2 triangles) function below 
 * except the probability because there are 
 * 3 common nodes between these two tables
 */
  tbl mTab_final(tbl Table1,tbl Table2,int es)
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
  
 /*This Function will merge two the clique associated
 *  with v_i.
 * Here There are two common nodes between the these merged two tables and 
 * so everything is same as mTab1 function above 
 * except the probability because there are 
 * 2 common nodes between these two tables
 */ 
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
                         obj.cost=(Table1[i].cost*Table2[j].cost)/(ii*jj);
                      
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

 
 /*This Function will merge two the clique associated
 *  with v_i.
 * Here There are two common nodes between the these merged two tables and 
 * so everything is same as mTab1 function above 
 * except the probability because there are 
 * 3 common nodes between these two tables
 */ 
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

/*
 * This function merge edges to form clique of size 3(Triangles)
 */
int CreateTable()
{
   
   Preprocess();
   dbase1=dbase;
   pAllTable(dbase1);
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
           cout<<endl;
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


/*
 * This function along with other functions finds all cliques associates with 
 * node v_i(the node in the PES) 
 * and merge those cliques and removes node v_i.
 * It continue this process until sink with other two nodes left
 */
void threeTree()
{
    deque<q_int> r;
    deque<tbl> tempT;
    q_int T,T1,tt;
    tbl temp2;
    int es;
    CreateTable();
    cout<<"dbase3t\n";
    //pAllTable(dbase);
     cout<<"dbase 3tEnd\n";
    tempT=dbase;
    T=ElSeq;
    
    while(T.size()>3) //end when 3 nodes along with sink left
    {
        es=T.front(); //getting node from PES
        T1=findNodes3(dbase ,es); //finding all cliques associates with the node we are eliminating
        T.pop(); // Remove the eliminating node from PES
        tt=T1;
        int a[T1.size()+2],ii=1;
       
        
        for(;!tt.empty();)
        {
            a[ii]=tt.front()-1;
          
            tt.pop();
            ii++;
        }
       
        /*
         * For 3 tree there will be 4 cliques associates with each node
         */
        temp2=mTab(dbase[a[1]],dbase[a[2]]);
       //pTnode(temp2);cout<<"Xend"<<endl;
        temp2=mTab1(dbase[a[3]],temp2);
        //pTnode(temp2);cout<<endl;
        dbase[a[4]]=mTab_final(temp2,dbase[a[4]],es);
        cout<<"delete"<<es<<endl;
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
    threeTree();
}
