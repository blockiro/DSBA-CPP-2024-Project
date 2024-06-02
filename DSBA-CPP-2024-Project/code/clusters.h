#include <vector>
#include <cmath>
#include <algorithm>
#include <map>
#include <set>
#include <random>
#include <limits>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


using namespace std;

const int CLUST_NUM = 7;

class point
{
  private:
    vector<double> coordinates;
    int cluster;
    double minDist;

  public:
    point(vector<double> coord) : coordinates(coord), cluster(-1), minDist(numeric_limits<double>::max()){}

    vector<double> GetCoordinates() const {
          return coordinates;
      }
    
    void SetCluster(int clust)
    {
      cluster = clust;
    }
    void SetMinDist (double ds)
    {
      minDist = ds;
    }
    void SetCoordinates(vector<double> crd)
    {
      coordinates = crd;
    }
    double GetMinDist() const
    {
      return minDist;
    }
    int GetCluster() const
    {
      return cluster;
    }
    bool operator==(const point& other) const {
        return coordinates == other.coordinates;
    }
    bool operator!=(const point& other) const {
        return !(*this == other);
    }
};


double dist(const point &a, const point &b)
{
// предположим что point это вектор с значениями из одной строчки датасета
// нам нужно использовать формулу типо abs(a^2 - b^2)
// далее, пробегая по векторам, делаем финальную сумму из ячеек abs(a^2 - b^2)
// и делаем sqrt

  double sum = 0.0;
    for (size_t i = 0; i < a.GetCoordinates().size(); ++i) {
        double diff = a.GetCoordinates()[i] - b.GetCoordinates()[i];
        sum += diff * diff;
    }
    return sqrt(sum);
}


struct cluster 
{
  protected:
    vector<point> clust;

  public:
   cluster(vector<double> clst) : clust(clust) {}

   void pointAdder(const point& pnt)
   {
    clust.push_back(pnt);
   }

   int howMany() const
   {
     return clust.size();
   }

   vector<point> pointGetter() const
   {
    return clust;
   }
   
};


//a function for reading the data from csv. file (sashka)
vector<point> read_data(string& path_to_file)  
{
  vector<point> data_vec;
  ifstream fileInput(path_to_file);
  string line;

  while(getline(fileInput, line))
  {
    stringstream ss(line);
    string m_str;
    vector<double> strow;


    while (getline(ss, m_str, ','))
    {
      double vr = stod(m_str);
      strow.push_back(vr);

    }
    data_vec.push_back(strow);

  }
  return data_vec;
}


//a function that calculates the total distance between all points and centroids
double cost(vector<point>& points, vector<point> centroids)
{
  double cst = 0.0;
  for (size_t i = 0; i < points.size(), ++i;)
  {
    cst +=  dist(points[i], centroids[points[i].GetCluster()]);
  }

  return cst;
}


vector<point> select_random_points(const vector<point>& points, int k) {
    vector<point> centroids;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, points.size() - 1);

    for (int i = 0; i < k; ++i) {
        centroids.push_back(points.at(dis(gen)));
        centroids[i].SetCluster(i);
    }

    return centroids;
}

void assign_points_to_clusters(vector<point>& points, const vector<point>& medoids) {
    for (auto& p : points) {
        double min_dist = numeric_limits<double>::max();;
        int best_cluster = -1;
        for (size_t i = 0; i < medoids.size(); ++i) {
            double d = dist(p, medoids[i]);
            if (d < min_dist) {
                min_dist = d;
                best_cluster = i;
            }
        }
        p.SetCluster(best_cluster);
        p.SetMinDist(min_dist);
    }
}


vector<point> recalculating_centroids(const vector<point>& points, int id)
{
  int dimension = points[0].GetCoordinates().size(); //размерность вектора (точки)
  int id = CLUST_NUM; //количество кластеров
  vector<point> upd_centrs(id);
  vector<int> counts(id, 0);

  for (const auto& point : points)  //перебираем точки, считаем количество кластеров
  {
    // тут пришлось написать геттер в классе поинт шобы достать оттуда айди кластера
    int clst_id = point.GetCluster();
    counts[clst_id]++;
    const vector<double>& coordinates = point.GetCoordinates();
    upd_centrs[clst_id].SetCoordinates(coordinates);
  
  }

  //тут находим среднее, делим сумму координат на количество точек в каждом кластере
  for (int i = 0; i < id; ++i)
  {
    if (counts[i] > 0)
    {
      vector<double> coord_p = upd_centrs[i].GetCoordinates();
      for (int m; m < dimension; ++m)
      {
        coord_p[m] /= counts[i];
      }
      upd_centrs[i].SetCoordinates(coord_p);
    }
  }
  //в результате получаем новый центроид для каждого кластера шоб не втыкали


  return upd_centrs;
}


void clusteringPAM(vector<point>& points) //это делаю Я
{
  double cst;
  vector<point> centroids(CLUST_NUM);
  centroids = select_random_points(points, CLUST_NUM);
  assign_points_to_clusters(points, centroids);

  // counting the cost
  cst = cost(points,centroids);
  
  // iterating until the cost is minimum
  bool checker = true;
  std::vector<point> upd_centrs(CLUST_NUM);
  while (checker)
  {
    upd_centrs = recalculating_centroids(points, CLUST_NUM);
    assign_points_to_clusters(points, upd_centrs);
    double cst_new = cost(points,upd_centrs);
    if (cst_new < cst)
    {
      checker = false;
    }
    else
    {
      cst = cst_new;
    }
  }
  return ;
}



vector<cluster> ClusterMaker(vector<point>& points)
{
  vector<cluster> clusters(CLUST_NUM);
  for(size_t i = 0; i < points.size(); i++)
  {
    clusters[points[i].GetCluster()].pointAdder(points[i]);
  }
  return clusters;
}
//(katya)

