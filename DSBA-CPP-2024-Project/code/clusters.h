#include <vector>
#include <cmath>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

const int CLUST_NUM = 7;

class point
{
  
};


double dist(const point &a, const point &b) /// это делаю Я
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
