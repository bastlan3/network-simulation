#include "network.h"
#include <algorithm>
#include "random.h"
#include "iostream"

void Network::resize(const size_t& a){
if (a!=0){
	values.resize(a,RNG.normal());
		}
	}
	
 bool Network::add_link(const size_t& a, const size_t& b){
	if ((a==b)or (a==0) or (b==0))	{
		return false;
		}
	if ((a<=size()) and (b<=size())and (not test_link(a,b))){
		 links.insert(std::pair<size_t, size_t>(a,b));
		 links.insert(std::pair<size_t, size_t>(b,a));
		return true;
		}
	return false;
	 }
 
 size_t Network::random_connect(const double& a){
	 links.clear();
	 size_t counter(0);
	 std::vector<size_t> points;
	 RandomNumbers seed;
	  for (unsigned int i(1);i<size();++i )
		points.push_back(i);
	 for (unsigned int i(1);i<=size();++i ){
		 unsigned int nbr_lien ;
		 nbr_lien= (seed.poisson(a));
		 seed.shuffle(points);
		 if (size()<nbr_lien)
			nbr_lien= size()-1;
		 if(degree(i)<=nbr_lien){
			 int deg(degree(i));
			 unsigned int k(0);
			 for( unsigned int j(0);j<=nbr_lien-deg ; ++j, k++){
				if (k>=size()){break;}
				 if ( add_link(i,points[k])){
					 counter++;
					 }else{
						 --j;
						 }
				}
			 }  
		 }	
	return counter;
	}
 
 size_t Network::set_values(const std::vector<double>& vec){
	resize(vec.size());
	values=vec;
	return size();
	 
	 }
 
 size_t Network::size() const{
	 return values.size();
	 }
 
 size_t Network::degree(const size_t &n) const{
	return neighbors(n).size();
	 }
 
 double Network::value(const size_t &n) const{
	 if (values.size()>n)
	 return values[n];
	 return 0;
	 }
 
 std::vector<double> Network::sorted_values() const{
	 std::vector <double> result;
	 result = values;
	 std::sort(result.begin(), result.end());
	 std::reverse(result.begin(), result.end());
	 return result;
	 }
 
 std::vector<size_t> Network::neighbors(const size_t& a) const{
	std::vector<size_t> neighbor;
	auto result = links.equal_range(a);
	for (auto it = result.first; it != result.second; it++)
		neighbor.push_back(it->second);
	return neighbor;
	 }

bool Network::test_link(const size_t& n,const size_t& m){
	std::vector<size_t> neighbor(neighbors(n));
	for (auto link : neighbor){
		if (link==m)
			return true;
		}
	return false;
	}	

