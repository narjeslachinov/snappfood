#include<iostream>
#include<string>
#include <cstring>
#include<vector>
#include<bits/stdc++.h> 
#include <iostream>
#include<climits>
using namespace std;
bool first = true;

struct node
{
    node(string n ,vector<string> a ) : name(n), adjacent(a)  {}
    string name;
    vector<string> adjacent;//name hasayehay har node dar in vector negah dari mishavad
    bool met  = false;//dar algoritm dikstra nodi ke kharej mishavad met an true mishavad
    float cost = INT_MAX ;
    string parent ;
};

struct edage
{
    edage(string s , string d , float dis , float t) : node1(s) , node2(d) , distance(dis) ,  traffic_insesity(t) {}
    string node1;
    string node2;
    float distance;
    float traffic_insesity;
    float cost = traffic_insesity * distance;
};

vector<float> cost;
vector<node> keep_node;
vector<edage> keep_edage;

void creat_graf()
{
 
   keep_node = {
                
                 node ("shandiz_haji" ,{"intersection_takhti","square_khomeyni","square_parvaneha"}),
                 node ("square_khomeyni" , {"abdolah_shrine", "intersection_khajerashide" ,"square_parvaneha", "intersection_takhti" ,"shandiz_haji"}),
                 node ("intersection_takhti" , {"square_khomeyni","square_parvaneha", "boalisina_shrine" ,"shandiz_haji" }),
                 node ("square_parvaneha" , {"square_khomeyni", "intersection_takhti","shandiz_haji" }),
                 node ("boalisina_shrine" , {"intersection_khajerashide","low_shokrie","intersection_takhti"  }),
                 node ("intersection_khajerashide" , {"square_khomeyni","abdolah_shrine", "boalisina_shrine" , "square_shariati"}),
                 node ("abdolah_shrine" , {"square_khomeyni","intersection_khajerashide"  }),
                 node ("low_zamani" , {"high_zamani","low_javadie"  }),
                 node ("low_javadie" , {"square_shariati","high_javadie"  , "low_zamani" }),
                 node ("square_shariati" , {"low_javadie","intersection_pazhohesh", "low_shokrie","intersection_khajerashide" }),
                 node ("low_shokrie" , {"square_shariati","boalisina_shrine" ,"high_shokrie" }),
                 node ("high_shokrie" , {"low_shokrie","intersection_pazhohesh"  }),
                 node ("high_javadie" , {"intersection_pazhohesh","low_javadie","ghadir_dorm" ,"high_zamani" }),
                 node ("high_zamani" , {"low_zamani","high_javadie"  }),
                 node ("intersection_pazhohesh" , {"square_shariati","high_javadie" , "high_shokrie" }),
                 node ("ghadir_dorm" , {"high_javadie" }),
             
                 };
   keep_edage = {edage("shandiz_haji", "square_khomeyni" ,0.2 ,3 ),
                 edage("shandiz_haji", "intersection_takhti" ,0.2 , 1),
                 edage("shandiz_haji", "square_parvaneha" ,0.2 , 1),

                 edage("square_khomeyni", "intersection_takhti" ,0.2 , 2),
                 edage("square_khomeyni", "square_parvaneha" ,1.3, 3),
                 edage("square_khomeyni", "abdolah_shrine" ,1.9 , 2),
                 edage("square_khomeyni", "intersection_khajerashide" ,2.1 , 3),

                 edage("intersection_takhti", "square_parvaneha" ,1.4 , 2),
                 edage("intersection_takhti", "boalisina_shrine" ,2.4 , 2),

                 edage("boalisina_shrine", "intersection_khajerashide" ,1.9 , 2),
                 edage("boalisina_shrine", "low_shokrie" ,3 , 3),
                 
                 edage("abdolah_shrine", "intersection_khajerashide" ,2 , 1),
                 
                 edage("low_shokrie", "high_shokrie" ,4.1 , 2),
                 edage("low_shokrie", "square_shariati" ,0.1 , 1),

                 edage("high_shokrie", "intersection_pazhohesh" ,1.2 , 3),

                 edage("square_shariati", "intersection_khajerashide" ,0.1 , 3),
                 edage("square_shariati", "intersection_pazhohesh" ,3.5 , 2),
                 edage("square_shariati", "low_javadie" ,0.1 , 2),

                 edage("intersection_pazhohesh", "high_javadie" ,0.8 , 3),
        
                 edage("low_javadie", "low_zamani" ,1.1 , 1),
                 edage("low_javadie", "high_javadie" ,2 , 1),
                 
                 edage("high_javadie", "ghadir_dorm" ,0.2 , 1),
                 edage("high_javadie", "high_zamani" ,0.6 , 3),

                 edage("low_zamani", "high_zamani" ,1.8 , 2),          
   };          
}




node min_cost(node src , node des )// agar node src taeen konande meghdar cost node des bashad parent an mishavad
{
    for (int i =0  ; i < keep_edage.size()  ; i++)
    {
        if ( (keep_edage[i].node1 == src.name && keep_edage[i].node2 == des.name) ||(keep_edage[i].node1 == des.name && keep_edage[i].node2 == src.name)   )
        {
            if( des.cost == INT_MAX)//agar hazine node des binahayat bashad taghir mikonad va bararbar hazine node src  + hazine yalli ke shamel in do node ast mishavad
            {      
                des.cost  = keep_edage[i].cost + src.cost;
                cost.push_back(des.cost);//hazine jadid dar vector cost negah dari mishavad
                des.parent = src.name;
                return des;
            }
            else if(des.cost > (src.cost + keep_edage[i].cost) && des.cost - (src.cost + keep_edage[i].cost) > 0.1 )//agar hazine node des bishtar az hazine node src  + yall shamel in  2 node bashad taghir mikonad
            {
                replace(cost.begin() , cost.end() , des.cost ,keep_edage[i].cost + src.cost );//hazine jadid jaygozin hazine ghabli mishavad
                des.cost  = keep_edage[i].cost + src.cost;
                des.parent = src.name; 
                return des;
            }
            return des;  
        }
    }
    
}

void dijkstra( string src)
{
    int num1;
    int num2;
    for(int i = 0 ; i < keep_node.size() ; i++)//yaftan nodi ke name an src ast dar vector keep_node
    {
        if(keep_node[i].name == src)
        {
          num1 = i;  
        }
    }
    if(first)// avalin bar ke in tabe farakhani mishavad first true ast va meghdar cost node src 0 mishvad cost baghi node ha be tor pishfarz bi nahayat ast
    {
        keep_node[num1].cost  = 0;
    }
    keep_node[num1].met = true;
    first = false;
    
    for (int i = 0 ; i <keep_node[num1].adjacent.size()   ; i++)
    {   
        for(int j = 0 ; j <keep_node.size() ; j++)
        {
            if(keep_node[j].name == keep_node[num1].adjacent[i] )
            {
                num2 = j;
            }
        }
        
        if(keep_node[num2].met == false)
        {
            keep_node[num2] =  min_cost(keep_node[num1] , keep_node[num2]  );//node src ra ba tak tak hamsayehayash be tabe min_cost midahim
        }
    }

    sort(cost.begin(), cost.end());
    for (int i = 0  ; i < keep_node.size()   ; i++)//entekhab nodi ke kamtarin hazine ra darad v kharej nashode ast
    {
        if(keep_node[i].cost == cost[0] )
        {
            if(keep_node[i].met == false )
            {
                cost.erase(cost.begin());
                dijkstra( keep_node[i].name);
            }
        }
    }
}
string print_shortest_path(string src, string des)//kotah trin masir an node src be des ra pyda mikonad
{
    if(first)
    {
        dijkstra( src);        
    }

    if(des != src)
    {
         for(int i = 0 ; i < keep_node.size() ; i++)
        {
            if(keep_node[i].name == des)
            {
                return print_shortest_path(src,keep_node[i].parent ) +"->" + des ;// parent har node nodi ast ke des ghabi bude
            }
        }
        
    }
    else
    {
        first = false;
        return   des ;
    } 
}

float find_cost(string path)//in tabe yek string be form  shandiz_hji->square_khomeyni->abdolah_shrine daryaft mikonad ke neshan dahande yek masir ast
{  
    //yal hay mojude dar in masir ra peyda mikonad be tori ke node aval va dovom in string yek yal tashkil midahand va node dovom va sevom yall badi ra
    string src;
    string des;
    float total_cost = 0;
    int found = 0;
    int i = -2;
    int j;

    while(found != -1)
    {
        found = path.find("->" ,found + 1 );
        j = found;
        if( i == -2)
        {

            src = path.substr(0 , j );
        }
        else
        {
            des = path.substr(i + 2 , j -i - 2 );
            for (int k = 0; k <= keep_edage.size(); k++)
            {
                if( (keep_edage[k].node1 == src && keep_edage[k].node2 == des) ||(keep_edage[k].node1 == des && keep_edage[k].node2 == src))
                {
                   
                    total_cost = total_cost +( keep_edage[k].traffic_insesity * keep_edage[k].distance) ;
                }
            }
            src = des; 
        }
        i = j; 
    }
    return total_cost;  
}

float find_distance(string path)
{  
    string src;
    string des;
    float total_distance = 0;
    int found = 0;
    int i = -2;
    int j;

    while(found != -1)
    {
        found = path.find("->" ,found + 1 );
        j = found;
        if( i == -2)
        {

            src = path.substr(0 , j );
        }
        else
        {
            des = path.substr(i + 2 , j -i - 2 );
            for (int k = 0; k <= keep_edage.size(); k++)
            {
                if( (keep_edage[k].node1 == src && keep_edage[k].node2 == des) ||(keep_edage[k].node1 == des && keep_edage[k].node2 == src))
                {
                    total_distance = total_distance + keep_edage[k].distance;
                   
                }
            }
            src = des; 
        }
        i = j;
    }
    return total_distance;
  
}  

int main()
{
    creat_graf();
    cout << "shortest path from shandiz haji to ghadir dorm:" <<   print_shortest_path("shandiz_haji" , "ghadir_dorm") << endl;
    cout << "Its distance : " << find_distance( print_shortest_path("shandiz_haji" , "ghadir_dorm")) << endl;          
    cout << "Its cost : " << find_cost( print_shortest_path("shandiz_haji" , "ghadir_dorm")) << endl;             
}