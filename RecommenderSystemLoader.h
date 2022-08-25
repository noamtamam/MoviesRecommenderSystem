
#ifndef RECOMMENDERSYSTEMLOADER_H
#define RECOMMENDERSYSTEMLOADER_H

#define SCORE_MESG "invalid score!"
#define LOOWER_BOND 1
#define UPPER_BOND_SCORE 10
#define FILE_ERROR_MESS "cant open file!"
#include "RecommenderSystem.h"
typedef std::unique_ptr<RecommenderSystem> rec_sys_ptr;
class RecommenderSystemLoader {

 private:

 public:
  RecommenderSystemLoader () = delete;
  /**
   * loads movies by the given format for movies with their feature's score
   * @param movies_file_path a path to the file of the movies
   * @return smart pointer to a RecommenderSystem which was created with
   * those movies
   */
  static rec_sys_ptr create_rs_from_movies_file
	  (const std::string &movies_file_path) noexcept (false);
};

#endif //RECOMMENDERSYSTEMLOADER_H
