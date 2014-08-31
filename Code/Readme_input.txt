********************************************
*****           Input File            ******
********************************************
line 1. the Perfect elimination sequence
line 2. n_req although we are showing the output for n_req=1 to |V_sense|
line 3. Transmission range R_tr
line 4. Indicate total number of nodes (NN) in the network 

line 5 to 5+NN. first value is node number
        Second value is number of locality sets |Loc|
        third and fourth values are the coordinate(where the diagonal intersects) of first location
        fifth and sixth values are the coordinate of second rectange and so on
        At the end |Loc| numbers of values are the probability associated with that rectangle respectively

line 5+NN+1. The sensor nodes V_sense

line 5+NN to end. The edge sets e.g., (4 5 there is a edge between node 4 and 5)
