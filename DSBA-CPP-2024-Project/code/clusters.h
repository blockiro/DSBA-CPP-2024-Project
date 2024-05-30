#include <vector>
#include <cmath>
#include <algorithm>
#include <map>
#include <set>
#include <random>
#include <limits>

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
   std::vector<point> clust;

  public:
   cluster(std::vector<double> clst) : clust(clust) {}

   void pointAdder(const point& pnt)
   {
    clust.push_back(pnt);
   }

   int howMany() const
   {
     return clust.size();
   }

   std::vector<point> pointGetter() const
   {
    return clust;
   }
   
};


//a function for reading the data from csv. file (sashka)
std::vector<point> read_data(std::string& path_to_file)  

{
  std::vector<point> data_vec;
  std::ifstream fileInput(path_to_file);
  std::string line;

  while(std::getline(fileInput, line))
  {
    std::stringstream ss(line);
    std::string m_str;
    std::vector<double> strow;


    while (std::getline(ss, m_str, ','))
    {
      double vr = std::stod(m_str);
      strow.push_back(vr);

    }
    data_vec.push_back(strow);

  }


double cost(vector<point>& points, vector<int>& m_ind, bool ischange = false)
{

}

vector<point> select_random_points(const vector<point>& points, int k) {
    vector<point> centroids;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, points.size() - 1);

    for (int i = 0; i < k; ++i) {
        centroids.push_back(points.at(dis(gen)));
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

void clusteringPAM(vector<point>& points) //это делаю Я
{
  select_random_points(points, CLUST_NUM);

  // counting the cost
  
  // iterating until the cost is minimum

  return ;
}


void interpreting(vector<point>& points, vector<cluster>& clusters) //это делаю Я
{
  
}
