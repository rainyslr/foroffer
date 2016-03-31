#include <iostream>
#include <vector> 
#include <map>

using namespace std;

int main()
{
	
	int nleg;
	while(cin >> nleg)
	{
		map<int, int> nlength;
		int len;
		for(int i = 0;i < nleg; ++ i)
		{
			cin >> len;
			nlength[i] = len;
		}

		vector<int> npay;
		int pay;
		for(int i = 0;i < nleg; ++ i)
		{
			cin >> pay;
			npay.push_back(pay);
		}
		int nleastPay = 0;
		bool firstcal = true;
		for (int i = 0; i < nleg; i++) {
			map<int, int> templength = nlength;
			int n = nleg;
			int pay = 0;
			int numOfsameLenth = 0;
			for (int j = 0; j < nleg; j++) {
				if (nlength[j] == nlength[i])
					numOfsameLenth++;
				else if (nlength[j] > nlength[i]) {
					pay += npay[j];
					templength.erase(j);
					n--;
				}
			}
			//map<int, int>::iterator ip = templength.begin();
			bool firstCountmin = true;
			int minPay = 0;
			int choseNum = 0;
			while (numOfsameLenth <= n / 2) {
				for (map<int, int>::iterator ip = templength.begin();
						ip != templength.end(); ip++) {
					if(nlength[i]==ip->second)
						continue;
					if (firstCountmin) {
						minPay = npay[ip->first];
						choseNum = ip->first;
						firstCountmin = false;
					}
					else if (npay[ip->first] < minPay) {
						minPay = npay[ip->first];
						choseNum = ip->first;
					}
				}
				pay += minPay;
				templength.erase(choseNum);
				n--;
			}
			if (firstcal) {
				nleastPay = pay;
				firstcal = false;
			} else if (pay < nleastPay) {
				nleastPay = pay;

			}
		}
		cout << nleastPay << endl;
	}
	return 0;	
} 