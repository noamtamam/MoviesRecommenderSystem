
// don't change those includes
#include "RSUser.h"
#include "Movie.h"
#include "RecommenderSystem.h"



std::string RSUser::get_name () const
{
  return _user_name;
}
void RSUser::add_movie_to_rs (const std::string &name, int year,
                        const std::vector<double> &features, double rate)
{

  sp_movie movie_inside = _recommender_sys->get_movie (name, year);
  if(movie_inside != nullptr)
  {
    _movies_rank.insert ({movie_inside, rate});
  }
  sp_movie movie_ptr = _recommender_sys->add_movie (name, year, features);

  _movies_rank.insert ({movie_ptr, rate});

}
rank_map RSUser::get_ranks () const
{
  return _movies_rank;
}

bool comp_movie(const sp_movie& m1, const sp_movie& m2)
{
  return *m1 < *m2;
}

std::ostream& operator <<(std::ostream& os, const
RSUser& user)
{
  os<<"name: " << user._user_name<<std::endl;
  os<<*(user._recommender_sys)<<std::endl;
  return os;
}

sp_movie RSUser::get_recommendation_by_content() const
{
  return _recommender_sys->recommend_by_content (*this);
}

double
RSUser::get_prediction_score_for_movie (const std::string &name, int year,
                                        int k) const
{
  sp_movie movie = _recommender_sys->get_movie (name, year);
  return _recommender_sys->predict_movie_score (*this, movie, k);

}
sp_movie RSUser::get_recommendation_by_cf (int k) const
{
  return _recommender_sys->recommend_by_cf (*this, k);
}



