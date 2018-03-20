#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>


using namespace std;


/*
Inventory (g_i, L, P, c, n){
cost [n][L] = {inf}
gallons[n][L] = {-1}
cost[0][0] = 0

for (i = 1; i <= L; i++)
cost[0][i] = inf;

for (k =1; k <= n; k++)

for(j = 0; j <= L; j++)
lower = max(0, j+g_i-L)
upper = j+g_i

for (m = lower; m <= upper; m++)
temp_cost = c*(j+g[i]-m)+c*m+cost[k-1][j+g[i]-L]
if(m >0) temp_cost += P

if (temp_cost < cost[k][j])
cost[k][L] = temp_cost
gallons [k][j] = m


return cost, gallons

Get_Report(n, gallons, cost, g_i)
prev_gallons = 0
tot_cost = 0
order_days[n] = {0}

for(i = n; i >= i; i--)
if(gallons[i][prev_gallons] > 0)
tot_cost = cost[n][prev_gallons]
order_days[i] = gallons[i][prev_gallons]

prev_gallons += g[i] - order_days[i]

return order_days, total_cost
*/


//need to clear up discrepancies with g_i and what loop it is predecated off of.
void Inventory(vector<int> g_i, int L, int P, int c, int n, int** cost, int** gallons) {
    cost[n][L] = INFINITY;
    gallons[n][L] = -1;

    cost[0][0] = 0;

    for (int i = 1; i <= L; i++)
        cost[0][i] = INFINITY;
    
    int lower, upper, temp_cost;
    for (int k = 1; k <= n; k++) {

        for (int j = 0; j <= L; j++) {
            lower = max(0, j + g_i[k] - L);//line needs to be checked
            upper = j + g_i[k];

            for (int m = lower; m <= upper; m++) {
                temp_cost = c*(j + g_i[k] - m) + c*m + cost[k - 1][j + g_i[k] - L];
                if (m > 0) temp_cost += P;

                    if (temp_cost < cost[k][j]) {
                        cost[k][L] = temp_cost;
                        gallons[k][j] = m;
                    }
            }
        }
    }

}
//get report function
void Get_Report(int n, int** cost, int** gallons, vector<int> g_i, int &tot_cost, int order_days[]) {
        int prev_gallons = 0;
        tot_cost = 0;
        order_days[n] = { 0 };

        for (int i = n; i >= i; i--) {
            if (gallons[i][prev_gallons] > 0) {
                tot_cost = cost[n][prev_gallons];
                order_days[i] = gallons[i][prev_gallons];
            }
            prev_gallons += g_i[i] - order_days[i];
        }
}

int main() {

    ifstream fin("input.txt");

    if (fin.fail()) {
        cerr << "Error opening file." << endl;

    }

    int n, L, P, c = 0;
    fin >> n >> L >> P >> c;
    
    vector<int> g_i;
    int temp;
    while (!fin.eof()) {
        fin >> temp;
        g_i.push_back(temp);
            
    }
    
   // int cost[][] = new int[n][L];
    
    //initializing cost[][]
    int** cost = new int*[n];
    for (int i = 0; i < n; ++i)
        cost[i] = new int[L];
    
    //initializing gallons[][]
    int** gallons = new int*[n];
    for (int i = 0; i < n; ++i)
        gallons[i] = new int[L];

    int* order_days = new int[n];
    int tot_cost = 0;

    Inventory(g_i, L, P, c, n, cost, gallons);
    Get_Report(n, cost, gallons, g_i, tot_cost, order_days);

    ofstream fout("output.txt");
       

    cout << "Hello world" << endl;
    return 0;
}