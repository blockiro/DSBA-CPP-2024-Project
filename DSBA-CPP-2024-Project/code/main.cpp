#include <cmath>
#include <iostream>
#include "clusters.h"
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

string datafile1 = "../Mall_Customers.csv";
string datafile2 = "../marketing_campaign_processed.csv";

string pointfile1 = "../points1.txt";
string pointfile2 = "../points2.txt";

string clustersfile1 = "../clusters1.txt";
string siluettesfile1 = "../siluettes1.txt";

string clustersfile2 = "../clusters2.txt";
string siluettesfile2 = "../siluettes2.txt";

double EPS = 1e-6;



void write_points(string outfilename, vector<point>& points)
{
  ofstream outfile(outfilename);
    if (!outfile) {
        cerr << "Error opening file: " << outfilename << endl;
        return;
    }

    for (const auto& p : points) {
        for (size_t i = 0; i < p.GetCoordinates().size(); ++i) {
            if (i > 0) outfile << ",";
            outfile << p.GetCoordinates()[i];
        }
        outfile << endl;
    }

    outfile.close();
}


void write_clusters(string outfilename, vector<point>& points)
{
  ofstream outfile(outfilename);
    if (!outfile) {
        cerr << "Error opening file: " << outfilename << endl;
        return;
    }

    for (const auto& p : points) {
        outfile << "Cluster " << p.GetCluster() << ": ";
        for (size_t i = 0; i < p.GetCoordinates().size(); ++i) {
            if (i > 0) outfile << ",";
            outfile << p.GetCoordinates()[i];
        }
        outfile << endl;
    }

    outfile.close();
}

void write_siluettes(string outfilename, vector<point>& points, vector<cluster>& clusters)
{
    ofstream out(outfilename);
    vector<double> silhouette_scores(points.size(), 0.0);

    for (size_t i = 0; i < points.size(); ++i) {
        point& current_point = points[i];
        int current_cluster = -1;
        double a = 0.0, b = numeric_limits<double>::max();

        for (size_t j = 0; j < clusters.size(); ++j) {
            const auto& cl = clusters[j].pointGetter();
            if (find(cl.begin(), cl.end(), current_point) != cl.end()) {
                current_cluster = j;
                break;
            }
        }

        if (current_cluster != -1) {
            const auto& cl = clusters[current_cluster].pointGetter();
            for (const auto& p : cl) {
                if (p != current_point) {
                    a += dist(current_point, p);
                }
            }
            a /= (cl.size() - 1);
        }

        for (size_t j = 0; j < clusters.size(); ++j) {
            if (j == current_cluster) continue;
            double distance = 0.0;
            const auto& cl = clusters[j].pointGetter();
            for (const auto& p : cl) {
                distance += dist(current_point, p);
            }
            distance /= cl.size();
            if (distance < b) b = distance;
        }

        silhouette_scores[i] = (b - a) / max(a, b);
    }

    for (const auto& score : silhouette_scores) {
        out << score << endl;
    }
    out.close();
}

void test(string input, string pointout, string clustout, string siluetteout)
{

  vector<point> points = read_data(datafile1);
  
  write_points(pointout, points);
  
  clusteringPAM(points);
  vector<cluster> clusters = ClusterMaker(points);
  write_clusters(clustout, points);
  //...
  write_siluettes(siluetteout,points, clusters);
  
  return;
}



void matrix_processing(string filename)
{
  ifstream in(filename);
  ofstream out(filename.substr(0, filename.size()-4) + "_processed.csv");

  string s;
  getline(in, s);
  out << s << endl;
  vector<vector<string> > M;

  for(;getline(in, s) ;)
  {
    stringstream ss(s);
    string x;
    for(; ss >> x;)
    {
      if (x == "Graduation")
      {
        out << "2 ";
      }
      else if (x == "2n")
      {
        ss >> x;
        out << "1 ";
      }
      else if (x == "Basic")
      {
        out << "0 ";
      }
      else if (x == "Master")
      {
        out << "3 ";
      }
      else if (x == "PhD")
      {
        out << "4 ";
      }
      else if (x == "Together")
      {
        out << "3 ";
      }
      else if (x == "Single")
      {
        out << "0 ";
      }
      else if (x == "Alone")
      {
        out << "0 ";
      }
      else if (x == "Absurd" or x == "YOLO")
      {
        out << "5 ";
      }
      else if (x == "Married")
      {
        out << "4 ";
      }
      else if (x == "Divorced")
      {
        out << "1 ";
      }
      else if (x == "Widow")
      {
        out << "2 ";
      }
      else if (x.size() == 10 && x[2] == '-')
      {
        //cout << x << endl;
        int days = 10*(x[0] - '0') + (x[1] - '0') + 30*( 10*(x[3] - '0') + (x[4] - '0') ) + 365*( (x[6]-'0')*1000 + (x[7] - '0')*100 + (x[8] - '0')*10 + (x[9]-'0'));
        out << days << " ";
      }
      else
      {
        out << x << " ";
      }
    }
    out << endl;
  }
  
  out.close();
  in.close();
}

int main()
{
  //matrix_processing("marketing_campaign.csv");
  //test(datafile1, pointfile1, clustersfile1, siluettesfile1);
  test(datafile2, pointfile2, clustersfile2, siluettesfile2);
 
  return 0;
}
