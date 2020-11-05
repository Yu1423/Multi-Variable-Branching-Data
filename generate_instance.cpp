#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <numeric>
#include <glob.h>
#include <sys/stat.h>





using namespace std;

//Uncorrelated instances
void Uncor(int n, int R, int H, int k, string folder){
	string filename = folder + "Uncorrelated_" + to_string(n) + "_" + to_string(R) + "_" + to_string(k) + ".txt";
	ofstream file(filename);
	
	file << n << endl;
	vector<double> w, p;
	for (int i=0; i<n; ++i){
		int tmp = rand() % R + 1;
		w.push_back(tmp);
		tmp = rand() % R + 1;
		p.push_back(tmp);
	}
	
	for (int i=0; i<n; ++i){
		file << p[i] << " ";
	}
	file << endl;
	for (int i=0; i<n; ++i){
		file << w[i]<<"  ";
	}
	file << endl;
	file << accumulate(w.begin(), w.end(), 0)*(1.0*k/(H+1));
	file.close();
}


//Weakly correlated instances
void Weak(int n, int R, int H, int k, string folder){
	string filename = folder + "Weak_" + to_string(n) + "_" + to_string(R) + "_" + to_string(k) + ".txt";
	ofstream file(filename);
	
	file <<   n  << endl;
	vector<double> w, p;
	for (int i=0; i<n; ++i){
		int tmp = rand() % R + 1;
		w.push_back(tmp);
		
		int tmp2 = rand() % (R / 5 + 1);
		p.push_back(tmp - R/10 + tmp2);
	}
	
	for (int i=0; i<n; ++i){
		file << p[i] << " ";
	}
	file <<  endl;
	for (int i=0; i<n; ++i){
		file << w[i]<<"  ";
	}
	file << endl;
	file << accumulate(w.begin(), w.end(), 0)*(1.0*k/(H+1));
	file.close();
}



//Strongly correlated instances
void Strong(int n, int R, int H, int k, string folder){
	string filename = folder + "Strong_" + to_string(n) + "_" + to_string(R) + "_" + to_string(k) + ".txt";
	ofstream file(filename);
	
	file <<   n  << endl;
	vector<double> w, p;
	for (int i=0; i<n; ++i){
		int tmp = rand() % R + 1;
		w.push_back(tmp);
		p.push_back(tmp + R/10);
	}
	for (int i=0; i<n; ++i){
		file << p[i] << " ";
	}
	file <<  endl;
	for (int i=0; i<n; ++i){
		file << w[i]<<"  ";
	}
	file << endl;
	file << accumulate(w.begin(), w.end(), 0)*(1.0*k/(H+1));
	file.close();
}




string getFileName(const string& s) {
	
	char sep = '/';
	
#ifdef _WIN32
	sep = '\\';
#endif
	
	size_t i = s.rfind(sep, s.length());
	if (i != string::npos) {
		return(s.substr(i+1, s.length() - i));
	}
	
	return("");
}


bool IsPathExist(const string &s)
{
  struct stat buffer;
  return (stat (s.c_str(), &buffer) == 0);
}






int main(){
	
	glob_t glob_result;
	glob("./data/*", GLOB_TILDE, NULL, &glob_result);
	string foldername = "./data/";
	
	if(IsPathExist(foldername)){
		// empty the folder
		cout << "Empty the folder " <<  foldername << endl;
		for (int k=0; k<glob_result.gl_pathc; ++k){
			string filename = getFileName(glob_result.gl_pathv[k]);
			string fullfilename = foldername + filename;
			remove(fullfilename.c_str());
		}
	}
	else{
		int check = mkdir(foldername.c_str(), 0777);
		if (check){
			cout << "Unable to create a folder to hold the data." << endl;
			return -1;
		}
		else
			cout << "Folder " <<  foldername << " created." << endl;
	
	}
	
	int N[4] = {100,200,500,1000}, Ns[4] = {20,30,40,50};
	int R[2] = {1000,10000}, H = 100;
	
	for(int i = 0; i < 4; ++ i){
		for(int j = 0; j < 2; ++ j){
			for (int k = 1; k <= H; ++k){
				Uncor(N[i], R[j], H, k, foldername);
				Weak(N[i], R[j], H, k, foldername);
				Strong(Ns[i], R[j], H, k, foldername);
			}
		}
	}
	cout << "Data generation completed." << endl;


	return 0;
}
	
