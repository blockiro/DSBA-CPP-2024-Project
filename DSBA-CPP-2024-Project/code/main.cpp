#include <cmath>
#include <iostream>
#include "clusters.h"
#include <fstream>
#include <sstream>
#include <map>
#include <algorithm>
#include <limits>
#include <vector>

using namespace std;


string datafile1 = "wine-clustering.csv";
string datafile2 = "../marketing_campaign_processed.csv";
string pointfile1 = "points1.txt"; string pointfile2 = "../points2.txt";
string clustersfile1 = "clusters1.txt"; string siluettesfile1 = "siluettes1.txt";
string clustersfile2 = "../clusters2.txt"; string siluettesfile2 = "../siluettes2.txt";

double EPS = 1e-6;

void write_points(const string &outfilename, const vector<point> &points) {
  // Open the output file stream
  ofstream outfile(outfilename);
  // Check if the file was successfully opened
  if (!outfile) {
    cerr << "Error opening file: " << outfilename << endl;
    return;
  }
// Iterate over each point in the points vector
  for (const auto &p : points) {
    // Iterate over each coordinate in the current point
    for (size_t i = 0; i < p.GetCoordinates().size(); ++i) {
      if (i > 0){
        outfile << ",";
      }
        // Write the coordinate to the file
      outfile << p.GetCoordinates()[i];
    }
    outfile << endl;
  }

  outfile.close();
}

void write_clusters(const string &outfilename, const vector<point> &points) {
  ofstream outfile(outfilename);
  if (!outfile) {
    cerr << "Error opening file: " << outfilename << endl;
    return;
  }
// Iterate over each point in the points vector
  for (const auto &p : points) {
    // Write the cluster ID of the current point to the file
    outfile << "Cluster " << p.GetCluster() << ": ";
    // Iterate over each coordinate in the current point
    for (size_t i = 0; i < p.GetCoordinates().size(); ++i) {
      if (i > 0){
        outfile << ",";
      }
      // Write the coordinate to the file
      outfile << p.GetCoordinates()[i];
    }
    outfile << endl;
  }

  outfile.close();
}

void write_silhouettes(const string &outfilename, const vector<point> &points,
                       const vector<cluster> &clusters) {
  ofstream out(outfilename);
  vector<double> silhouette_scores(points.size(), 0.0);

  for (size_t i = 0; i < points.size(); ++i) {
    const point &current_point = points[i];
    int current_cluster = -1;
    double a = 0.0, b = numeric_limits<double>::max();

    for (size_t j = 0; j < clusters.size(); ++j) {
      const auto &cl = clusters[j].pointGetter();
      if (find(cl.begin(), cl.end(), current_point) != cl.end()) {
        current_cluster = j;
        break;
      }
    }

    if (current_cluster != -1) {
      const auto &cl = clusters[current_cluster].pointGetter();
      for (const auto &p : cl) {
        if (p != current_point) {
          a += dist(current_point, p);
        }
      }
      a /= (cl.size() - 1);
    }

    for (size_t j = 0; j < clusters.size(); ++j) {
      if (j == current_cluster)
        continue;
      double distance = 0.0;
      const auto &cl = clusters[j].pointGetter();
      for (const auto &p : cl) {
        distance += dist(current_point, p);
      }
      distance /= cl.size();
      if (distance < b)
        b = distance;
    }

    silhouette_scores[i] = (b - a) / max(a, b);
  }

  vector<double> final_score(CLUST_NUM, 0.0);
  vector<int> counter(CLUST_NUM, 0);
  for (size_t i = 0; i < points.size(); i++) {
    final_score[points[i].GetCluster()] += silhouette_scores[i];
    counter[points[i].GetCluster()] += 1;
  }
  for (size_t i = 0; i < final_score.size(); i++) {
    if (counter[i] > 0) {
      final_score[i] /= counter[i];
    } else {
      final_score[i] = 0;
    }
  }
  int k = 0;
  for (const auto &score : final_score) {
    out << "Cluster " << k << ": " << score << endl;
    k++;
  }
  out.close();
}

void test(const string &input, const string &pointout, const string &clustout, const string &siluetteout) {
  vector<point> points = read_data(input);  

  write_points(pointout, points);

  clusteringPAM(points);  
  vector<cluster> clusters = ClusterMaker(points);  
  write_clusters(clustout, points);
  write_silhouettes(siluetteout, points, clusters);
}

int main() {
  while (true) {
    std::cout << "Here is a program that implements the K-Means clustering algorithm for a given dataset.\nPlease enter the path to your data file: ";
    std::string path_to;
    std::cin >> path_to;

    test(datafile1, pointfile1, clustersfile1, siluettesfile1);

    std::cout << "If you want to exit, enter 'Exit'. To continue clustering, enter 'Clusterize': ";
    std::string decision;
    std::cin >> decision;

    if (decision == "Exit") {
      break;
    }
  }

  return 0;
}

