#include <cmath>
#include <iostream>
#include "clusters.h"
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

string datafile1 = "wine-clustering.csv";
string datafile2 = "../marketing_campaign_processed.csv";

string pointfile1 = "points1.txt";
string pointfile2 = "../points2.txt";

string clustersfile1 = "clusters1.txt";
string siluettesfile1 = "siluettes1.txt";

string clustersfile2 = "../clusters2.txt";
string siluettesfile2 = "../siluettes2.txt";

double EPS = 1e-6;

void write_points(const string &outfilename, const vector<point> &points) {
  ofstream outfile(outfilename);
  if (!outfile) {
    cerr << "Error opening file: " << outfilename << endl;
    return;
  }

  for (const auto &p : points) {
    for (size_t i = 0; i < p.GetCoordinates().size(); ++i) {
      if (i > 0)
        outfile << ",";
      outfile << p.GetCoordinates()[i];
    }
    outfile << endl;
  }

  outfile.close();
}

void write_clusters(string outfilename, vector<point> &points) {
  ofstream outfile(outfilename);
  if (!outfile) {
    cerr << "Error opening file: " << outfilename << endl;
    return;
  }

  for (const auto &p : points) {
    outfile << "Cluster " << p.GetCluster() << ": ";
    for (size_t i = 0; i < p.GetCoordinates().size(); ++i) {
      if (i > 0)
        outfile << ",";
      outfile << p.GetCoordinates()[i];
    }
    outfile << endl;
  }

  outfile.close();
}

void write_siluettes(string outfilename, vector<point> &points,
                     vector<cluster> &clusters) {
  ofstream out(outfilename);
  vector<double> silhouette_scores(points.size(), 0.0);

  for (size_t i = 0; i < points.size(); ++i) {
    point &current_point = points[i];
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

void test(string input, string pointout, string clustout, string siluetteout) {

  vector<point> points = read_data(datafile1);

  write_points(pointfile1, points);

  clusteringPAM(points);
  vector<cluster> clusters = ClusterMaker(points);
  write_clusters(clustersfile1, points);
  write_siluettes(siluettesfile1, points, clusters);

  return;
}

int main() {
  test(datafile1, pointfile1, clustersfile1, siluettesfile1);
  // test(datafile2, pointfile2, clustersfile2, siluettesfile2);

  return 0;
}
