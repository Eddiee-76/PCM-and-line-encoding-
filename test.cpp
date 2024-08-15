#include <iostream>
#include <vector>
#include<map>
#include<cmath>
using namespace std;
int main()
{
    map<float, vector<int>> mp;
vector<int> bits(8,0);
vector<int> bi(8,0);
  mp[0]=bits;
  cout<<mp[0][0];
  bi=mp[0];
  cout<<bi[7];
  cout<<sin(1.64);

}