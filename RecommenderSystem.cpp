#include "RecommenderSystem.h"
#include "Movie.h"
#include <unordered_map>
#include <cmath>
#include <map>

sp_movie RecommenderSystem::add_movie (const std::string &name, int year,
                                       const std::vector<double> &features)
{
  Movie new_movie(name, year);
  sp_movie movie_ptr = std::make_shared<Movie>(new_movie);
  movies_data.insert ({movie_ptr, features});
  return movie_ptr;
}

RecommenderSystem::RecommenderSystem()
{
}

sp_movie RecommenderSystem::get_movie (const std::string &name, int year) const
{
  for(const auto & it : movies_data)
  {
    if((((it.first)->get_name()) == name) && ((it.first)
    ->get_year
    ()==
    year))
    {
      return it.first;
    }
  }
  return nullptr;
}

std::ostream & operator<<(std::ostream& os, const
RecommenderSystem& sys )
{
  for(const auto & iter : sys.movies_data)
  {
    os <<*(iter.first);
  }
  return os;
}

rank_map normalize_rank_map(rank_map& map_rank)
{

  double sum = 0;
  int size = 0;
  for(auto& it : map_rank)
  {
    if(it.second != -1)
    {
      sum +=it.second;
      size ++;
    }
  }
  rank_map normal_rank_map(HASH_START, sp_movie_hash,
                           sp_movie_equal);
  for(const auto& it : map_rank)
  {
    if(it.second != -1)
    {
      normal_rank_map[it.first] =  it.second- (sum / size);
    }
  }
  return normal_rank_map;
}

double get_norma (const std::vector<double>& v)
{
  return sqrt (multiply_2_vec (v, v));
}

double multiply_2_vec(const std::vector<double> v1,
                                          const std::vector<double>& v2)
{
  double sum = 0.0;
  for (unsigned int i = 0; i < v1.size (); i++)
  {
    sum += v1[i] * v2[i];
  }
  return sum;
}



void multi_vec_by_scalar(std::vector<double>& v,
                                            double c)
{
  for(double & j : v)
  {
    j *= c;
  }
}

std::vector<double> sum_vec
(std::vector<std::vector<double>> v)
{
  std::vector<double> sum_vec;
  for(unsigned int j=0; j<v[0].size(); j++)
  {
    double sum =0.0;
    for(auto & i : v)
    {
      sum += i[j];
    }
    sum_vec.push_back (sum);
  }
  return sum_vec;
}

std::vector<double> RecommenderSystem::get_pref_vec (rank_map user_ranks)const
{
  rank_map user_ranks_normal (HASH_START, sp_movie_hash,
                              sp_movie_equal);
  user_ranks_normal = normalize_rank_map (user_ranks);
  std::vector<std::vector<double>> all_feats;
  for(auto &iter:user_ranks_normal)
  {
    double scalar = iter.second;
    sp_movie cur_movie = iter.first;
    std::vector<double> feature;
    auto it = movies_data.find (cur_movie);
    feature = it->second;
    multi_vec_by_scalar (feature, scalar);
    all_feats.push_back (feature);
  }
  std::vector<double> ref_vec;
  ref_vec = sum_vec (all_feats);
  return ref_vec;
}

double calculate_movie_value(std::vector<double> ref, const std::vector<double>&
    features)
{
  double value = 0.0;
  value = multiply_2_vec (ref, features);
  double norma_ref = get_norma (ref);
  double norma_f = get_norma (features);
  value = value / (norma_ref * norma_f);
  return value;
}

sp_movie RecommenderSystem::get_max_movie (const rank_map user_rank) const
{
  sp_movie max_movie = user_rank.begin()->first;
  double max_value = user_rank.begin()->second;
  for(const auto& iter:user_rank)
  {
    if(iter.second > max_value)
    {
      max_value = iter.second;
      max_movie = iter.first;
    }
  }
  return max_movie;
}

void RecommenderSystem::calculate_value_inside (std::vector<double> ref_vec,
            rank_map user_ranks, rank_map &movies_values)
const
{
  for(const auto& iter : movies_data)
  {
    if (user_ranks.find (iter.first) == user_ranks.end())
    {
      std::vector<double> features = movies_data.at(iter.first);
      double value = calculate_movie_value (ref_vec, features);
      movies_values.insert ({iter.first, value});
    }
  }
}

void RecommenderSystem::calculate_value_outside (std::vector<double> ref_vec,
                                                rank_map user_ranks,
                                                similary_k& movies_values)
const
{
  for(const auto& iter : movies_data)
  {
    if (user_ranks.find (iter.first) != user_ranks.end())
    {
      std::vector<double> features = movies_data.at(iter.first);
      double value = calculate_movie_value (ref_vec, features);
      movies_values.insert ({value, iter.first});
    }
  }
}

  sp_movie RecommenderSystem::recommend_by_content (const RSUser &user)
  {
    rank_map user_ranks (HASH_START, sp_movie_hash, sp_movie_equal);
    user_ranks = user.get_ranks ();
    std::vector<double> ref_vec = get_pref_vec (user_ranks);
    rank_map movie_value_map (HASH_START, sp_movie_hash,
                              sp_movie_equal);
    calculate_value_inside (ref_vec, user_ranks, movie_value_map);
    sp_movie movie = get_max_movie (movie_value_map);
    return movie;
  }

double
RecommenderSystem::calculate_mona (similary_k movies_rank, rank_map user_rank,
                                   int k)
{
  double sum = 0.0;
  int i=0;
  for(auto& iter: movies_rank)
  {
    if(i<k)
    {
      sum+= iter.first * user_rank[iter.second];
    }
    else
    {
      return sum;
    }
    i++;
  }
  return sum;
}

double RecommenderSystem::calculate_mehane (similary_k movies_rank, int k)
{
  double sum = 0.0;
  int i=0;
  for(auto& iter: movies_rank)
  {
    if(i<k)
    {
      sum+= iter.first;
    }
    else
    {
      return sum;
    }
    i++;
  }
return sum;
}
void RecommenderSystem::calculate_scores (const RSUser& user,
                                          rank_map& movies_values, int k)
{
  rank_map user_ranks (HASH_START, sp_movie_hash, sp_movie_equal);
  user_ranks = user.get_ranks ();
  for(auto& iter : movies_data)
  {
    if (user_ranks.find (iter.first) == user_ranks.end())
    {
      double score = predict_movie_score (user, iter.first, k);
      movies_values.insert ({iter.first, score});
    }
  }
}

sp_movie RecommenderSystem::recommend_by_cf (const RSUser &user, int k)
{
  rank_map user_ranks (HASH_START, sp_movie_hash, sp_movie_equal);
  user_ranks = user.get_ranks ();
  rank_map movie_value_map (HASH_START, sp_movie_hash,
                            sp_movie_equal);
  calculate_scores (user, movie_value_map, k);
  sp_movie movie = get_max_movie (movie_value_map);
  return movie;
}

double
RecommenderSystem::predict_movie_score (const RSUser &user, const sp_movie
&movie, int k)
{
  rank_map user_ranks (HASH_START, sp_movie_hash, sp_movie_equal);
  user_ranks = user.get_ranks ();
  std::vector<double> movie_rank = movies_data[movie];
  similary_k movie_value_map;
  calculate_value_outside (movie_rank, user_ranks, movie_value_map);
  double mona = calculate_mona (movie_value_map, user_ranks,
                                k);
  double mehane = calculate_mehane (movie_value_map,k);
  return mona / mehane;

}
