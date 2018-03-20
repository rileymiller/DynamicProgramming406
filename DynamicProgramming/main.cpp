#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>


using namespace std;

void Inventory(vector<int> g_i, int L, int P, int c, int n, vector<vector<int>> &cost, vector<vector<int>> &gallons) {
	for (int i = 0; i <= n; i++) {
		vector<int> tempVec;
		vector<int> tempVecTwo;
		for (int j = 0; j <= L; j++) {
			tempVec.push_back(999999);//initialize costs to infinity
			tempVecTwo.push_back(-1);//initialize order sizes to -1
		}
		gallons.push_back(tempVecTwo);
		cost.push_back(tempVec);
	}
	cost[0][0] = 0;
    
    int lower, upper, temp_cost;
    for (int k = 1; k <= n; k++) {

        for (int j = 0; j <= L; j++) {
            lower = max(0, j + g_i[k] - L);//least amount that needs to be ordered
            upper = j + g_i[k];//the most that can be ordered

            for (int m = lower; m <= upper; m++) {
                temp_cost = c*(j + g_i[k] - m) + cost[k - 1][j + g_i[k] - m];//cost which is the prev day holding cost + prev day cumulative cost
                if (m > 0) temp_cost += P; //add delivery cost if applicable
                    if (temp_cost < cost[k][j]) {
                        cost[k][j] = temp_cost;
                        gallons[k][j] = m;
                    }
            }
        }
    }

}
//get report function
void Get_Report(int n, vector<vector<int>> &cost, vector<vector<int>> &gallons, vector<int> g_i, int &tot_cost, vector<int> &order_days, ofstream &fout ) {
        int prev_gallons = 0;
        tot_cost = 0;

        for (int i = n; i >= 1; i--) {
            if (gallons[i][prev_gallons] > 0) {
				if (i == n) {
					tot_cost = cost[n][prev_gallons];//total cost is accumulated in the last day
				}
				order_days[i] = gallons[i][prev_gallons];
            }
            prev_gallons += g_i[i] - order_days[i];
        }
		int numDays = 0;
		for (int i = 0; i <= n; i++) {
			if (order_days[i] > 0) {
				numDays++;
			}
		}
		fout << tot_cost << endl;
		fout << numDays << endl;
		//print out the days and gallons ordered
		for (int i = 1; i <= n; i++) {
			if (order_days[i] > 0) {
				fout << i << " " << order_days[i] << endl;
			}
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
	g_i.push_back(0);
    while (!fin.eof()) {
        fin >> temp;
        g_i.push_back(temp);
            
    }
	
    vector<vector<int>> cost;

	vector<vector<int>> gallons;

	vector<int> order_days;
	for (int i = 0; i <= n; i++) {
		order_days.push_back(0);
	}
    int tot_cost = 0;
	ofstream fout("output.txt");
    Inventory(g_i, L, P, c, n, cost, gallons);
    Get_Report(n, cost, gallons, g_i, tot_cost, order_days, fout);

    cout << "Hello world" << endl;
    return 0;
}