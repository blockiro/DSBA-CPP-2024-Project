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


//a function that calculates the total distance between all points and centroids
double cost(vector<point>& points, vector<int>& m_ind, bool ischange = false, std::vector<int>& clusters)
{
  double cst = 0.0;
  for (size_t i = 0; i < points.size(), ++i;)
  {
    cst +=  dist(points[i], points[m_ind[clusters[i]]]);
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

//(katya)
void write_siluettes(string outfilename, vector<point>& points, vector<cluster>& clusters)
{
    ofstream out(outfilename);
    vector<double> silhouette_scores(points.size(), 0.0);

    for (size_t i = 0; i < points.size(); ++i) {
        const point& current_point = points[i];
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
