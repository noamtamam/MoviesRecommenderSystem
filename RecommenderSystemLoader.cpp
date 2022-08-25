#include "RecommenderSystemLoader.h"
#include <fstream>
#define SPACE_WORD " "
#define SPACE_MOVIE "-"
#define LEN_SPACE 1

rec_sys_ptr RecommenderSystemLoader::create_rs_from_movies_file
(const std::string& movies_file_path) noexcept (false)
{
  RecommenderSystem sys_rec;
  std::fstream file;
  file.open(movies_file_path);
  if(!file)
  {
    throw std::runtime_error(FILE_ERROR_MESS);
  }
  std::string line;
  while (std::getline(file,line))
  {
    size_t pos =0;
    std::string movie_name = line.substr (0,
                                          line.find (SPACE_MOVIE));
    pos = line.find (SPACE_MOVIE);
    std::string movie_year = line.substr (pos+LEN_SPACE, 
                                          line.find (SPACE_WORD));
    line.erase (0, line.find (SPACE_WORD) + LEN_SPACE);
    int i_year = std::stoi (movie_year);
    std::vector<double> festures;
    while ((pos = line.find (SPACE_WORD)) != std::string::npos)
    {
        std::string score = line.substr (0,pos);
        double f_score = std::stod (score);
        if(f_score < LOOWER_BOND || f_score > UPPER_BOND_SCORE)
        {
          throw std::runtime_error(SCORE_MESG);
        }
        festures.push_back (f_score);
        line.erase (0,pos+LEN_SPACE);
    }
    double f_score = std::stod (line);
    festures.push_back (f_score);
    sys_rec.add_movie (movie_name, i_year, festures);
  }
  file.close();
  std::unique_ptr<RecommenderSystem> ptr_sys =
      std::make_unique<RecommenderSystem>(sys_rec);
  return ptr_sys;
}