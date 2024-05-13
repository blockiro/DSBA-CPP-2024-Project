#include <vector>
#include <cmath>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

const int CLUST_NUM = 7;

class point
{
  private:
    std::vector<double> coordinates;

  public:
    point(std::vector<double> coord) : coordinates(coord) {}

    std::vector<double> GetCoordinates() const {
        return coordinates;
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

double cost(vector<point>& points, vector<int>& m_ind, bool ischange = false)
{

}


void clusteringPAM(vector<point>& points) //это делаю Я
{
  // generating CLUST_NUM random medoids

  // counting the cost
  
  // iterating until the cost is minimum

  return ;
}


void interpreting(vector<point>& points, vector<cluster>& clusters) //это делаю Я
{
  
}
