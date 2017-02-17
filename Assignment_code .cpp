/* Details : Dhruv Pachauri, 13117022, B-Tech 4 Year Mechanical Engineering */

#include <bits/stdc++.h>
#include "util_funct.h"
using namespace std;

int main()
{
	NIL.left = NIL.right = NIL.p = NILPTR;
	NIL.color = BLACK_COLOR;
	struct node * tree = NILPTR;
	
	Interval ints[] = {{15, 20}, {10, 30}, {17, 19},
        {5, 20}, {12, 15}, {30, 40}
    };
    
    int n = sizeof(ints)/sizeof(ints[0]);
    
    for (int i = 0; i < n; i++){
         red_black_insert(&tree, ints[i]);
         cout<<"{"<<ints[i].lower_bound<<","<<ints[i].higher_bound<<"} is inserted successfully"<<endl;
    }
 
  
    Interval to_search[] = {{14, 16}, {21, 23}};
 
 	for(int i=0; i<2; i++){
	    cout << "\n{" << to_search[i].lower_bound << "," << to_search[i].higher_bound << "}";
	    Interval res = Overlap_Search_node(tree, to_search[i]);
	    if (res.lower_bound == INT_MIN)
	        cout << " has no Overlapping Inter";
	    else
	        cout << " overlaps with {" << res.lower_bound << ", " << res.higher_bound << "}";
	        
	}
	
	return 0;
}
