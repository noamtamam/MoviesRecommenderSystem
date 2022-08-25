#include "RSUsersLoader.h"
#define SPACE_WORD " "
#define SPACE_MOVIE "-"
#define LEN_SPACE 1

#define YEAR_LENGTH 4
#include <fstream>

/**
 * gets a file and insert the vecore given the name of the movie and year in
 * pairs
 * @param file
 * @param vec_movies
 */
void create_movies_vector(std::fstream&
file, std::vector<std::pair<std::string, int>>& vec_movies)
{
  std::string movie_line;
  std::getline (file, movie_line);
  size_t pos = 0;
  while ((pos = movie_line.find (SPACE_WORD))!= std::string::npos)
  {

    std::string movie_name = movie_line.substr (0, movie_line.find
        (SPACE_MOVIE));
    pos = movie_line.find (SPACE_MOVIE);
    std::string movie_year = movie_line.substr (pos+1,YEAR_LENGTH);
    int year_i = std::stoi (movie_year);
    pos = movie_line.find (SPACE_MOVIE);
    movie_line.erase (0,pos+LEN_SPACE + YEAR_LENGTH+1);
    std::pair<std::string, int> movie_pair = {movie_name,year_i};
    vec_movies.push_back (movie_pair);
  }
  std::string movie_name = movie_line.substr (0, movie_line.find
      (SPACE_MOVIE));
  pos = movie_line.find (SPACE_MOVIE);
  std::string movie_year = movie_line.substr (pos+1,YEAR_LENGTH);
  int year_i = std::stoi (movie_year);
  pos = movie_line.find (SPACE_MOVIE);
  std::pair<std::string, int> movie_pair = {movie_name,year_i};
  vec_movies.push_back (movie_pair);
}
/**
 * gets a line from a file and breack it to the movies score.
 * insert all the score to a rank map of movie and scores
 * @param file
 * @param vec_movies
 * @param score_movie_map
 * @param line
 * @param shar_rs
 */
void create_map_rank( std::vector<std::pair<std::string,
                     int>> vec_movies, rank_map& score_movie_map, std::string
                     line,std::shared_ptr<RecommenderSystem> shar_rs )
{
  int i = 0;
  size_t pos;
  while ((pos = line.find (SPACE_WORD)) != std::string::npos)
  {
    std::string score = line.substr (0, pos);
    double rate = NULL_SCORE_NUM;
    if(score != NULL_SCORE_STR)
    {
      rate = std::stod (score);
      const std::string name_movie = vec_movies[i].first;
      const int year_movie = vec_movies[i].second;
      sp_movie movie_ptr = shar_rs->get_movie (name_movie,
                                               year_movie);
      score_movie_map.insert ({movie_ptr, rate });
    }
    i++;
    line.erase (0,pos+1);
  }
  std::string score = line.substr (0, line.find (SCORE_SPACE));
  double rate = NULL_SCORE_NUM;
  if(score != NULL_SCORE_STR)
  {
    rate = std::stod (score);
    const std::string name_movie = vec_movies[i].first;
    const int year_movie = vec_movies[i].second;
    sp_movie movie_ptr = shar_rs->get_movie (name_movie,
                                             year_movie);
    score_movie_map.insert ({movie_ptr, rate });
  }
}

std::vector<RSUser>
RSUsersLoader::create_users_from_file (const std::string &users_file_path,
                     std::unique_ptr<RecommenderSystem> rs) noexcept (false)
{
  std::shared_ptr<RecommenderSystem> shar_rs = std::move(rs);
  std::vector<RSUser> users_vec;
  std::fstream file(users_file_path);
  if(!file)
  {
    throw std::runtime_error(FILE_ERROR_MESS);
  }
  std::vector<std::pair<std::string, int>> vec_movies;
  create_movies_vector(file, vec_movies);

  std::string line;
  while (std::getline (file, line))
  {
    std::string user_name = line.substr (0,line.find (SPACE_WORD));
    line.erase (0, line.find (SPACE_WORD)+LEN_SPACE);
    rank_map score_movie_map(HASH_START, sp_movie_hash,
                             sp_movie_equal ) ;
    create_map_rank (vec_movies, score_movie_map, line, shar_rs);
    RSUser new_user(user_name, score_movie_map,
                    shar_rs);
    users_vec.push_back (new_user);

  }
  return users_vec;

}
