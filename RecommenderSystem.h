
#ifndef SCHOOL_SOLUTION_RECOMMENDERSYSTEM_H
#define SCHOOL_SOLUTION_RECOMMENDERSYSTEM_H
#include "RSUser.h"
#include <map>
struct cmp_sp_movie
{
    bool operator()(const sp_movie& m1, const sp_movie& m2)const
    {
      return *m1 < *m2;
    }
};

class RecommenderSystem
{
  typedef std::multimap<double, sp_movie , std::greater<>> similary_k;
 private:
  std::map<sp_movie ,std::vector<double>, cmp_sp_movie> movies_data;

  /***
   * get user's rank map of movies and calculate his prefernce vector base
   * on his score
   * @param user_ranks
   * @return vector of double
   */
  std::vector<double> get_pref_vec(rank_map user_ranks)const;

  /**
   * pass through all movies that were ranked and calculate the value of
   * imagination
   * @param ref_vec preference vector of user
   * @param user_ranks user's movies rank
   * @param movies_values rank_map with movies imagination
   */
  void calculate_value_inside(std::vector<double> ref_vec, rank_map user_ranks,
                              rank_map& movies_values)
  const;

  /**
   * pass through all movies that were *not* ranked and calculate the value of
   * imagination
   * @param ref_vec preference vector of user
   * @param user_ranks user's movies rank
   * @param movies_values rank_map with movies imagination
   */
  void calculate_value_outside (std::vector<double> ref_vec,
                                rank_map user_ranks,similary_k& movies_values)
  const;

  /**
   * insert to movies value scores prediction for each movie - for only k top
   * movies
   * @param user
   * @param movies_values
   * @param k
   */
  void calculate_scores( const RSUser& user,
                         rank_map& movies_values, int k);

  /**
   * return the movie with the maximum value
   * @param user_rank user's rank
   * @return sp_movie with highest score
   */
  sp_movie get_max_movie(rank_map user_rank) const;

  /**
   * sum the duplication between movies similarty value and rank values-
   * only k top movies
   * @param movies_rank
   * @param user_rank
   * @param k
   * @return the result of calculation
   */
  double calculate_mona(similary_k movies_rank, rank_map user_rank, int k);

  /**
   * sum all simitary in movies rank of only top k movies
   * @param movies_rank
   * @param k
   * @return the result of calculation
   */
  double calculate_mehane(similary_k movies_rank, int k);

public:

	//explicit RecommenderSystem()
    RecommenderSystem();
    /**
     * adds a new movie to the system
     * @param name name of movie
     * @param year year it was made
     * @param features features for movie
     * @return shared pointer for movie in system
     */
	sp_movie add_movie(const std::string& name,int year,const
    std::vector<double>& features);

    /**
     * a function that calculates the movie with highest score based on movie
     * features
     * @param ranks user ranking to use for algorithm
     * @return shared pointer to movie in system
     */
	sp_movie recommend_by_content(const RSUser& user);

    /**
     * a function that calculates the movie with highest predicted score
     * based on ranking of other movies
     * @param ranks user ranking to use for algorithm
     * @param k
     * @return shared pointer to movie in system
     */
	sp_movie recommend_by_cf(const RSUser& user, int k);


    /**
     * Predict a user rating for a movie given argument using item cf
     * procedure with k most similar movies.
     * @param user_rankings: ranking to use
     * @param movie: movie to predict
     * @param k:
     * @return score based on algorithm as described in pdf
     */
	double predict_movie_score(const RSUser &user, const sp_movie &movie,
												  int k);

	/**
	 * gets a shared pointer to movie in system
	 * @param name name of movie
	 * @param year year movie was made
	 * @return shared pointer to movie in system
	 */
	sp_movie get_movie(const std::string &name, int year) const;
//    std::vector<double> get_features(sp_movie m) const;

  friend std::ostream & operator<<(std::ostream& os, const
  RecommenderSystem& sys );

};

/**
 * reduce the avrg of map_rank from all values in map rank
 * @param map_rank
 * @return the normelize map_rank
 */
rank_map normalize_rank_map(rank_map& map_rank);

void multi_vec_by_scalar(std::vector<double>& v, double c);

/***
 * sum vector of vector to 1 vector- coordinates wise
 * @return 1 dimention vector of sum
 */
std::vector<double> sum_vec(std::vector<std::vector<double>>);
/**
 * calculate scalar duplication between 2 vecs
 * @param v1
 * @param v2
 * @return double
 */
double multiply_2_vec(std::vector<double> v1, const std::vector<double>& v2);
/**
 * calculate norma of vector (by math defintion)
 * @param v
 * @return the norma
 */
double get_norma(const std::vector<double>& v);



#endif //SCHOOL_SOLUTION_RECOMMENDERSYSTEM_H
