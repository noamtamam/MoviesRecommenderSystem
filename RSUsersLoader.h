
#ifndef SCHOOL_SOLUTION_USERFACTORY_H
#define SCHOOL_SOLUTION_USERFACTORY_H
//#define FILE_ERROR_MESS "can't open the file!"
#define NULL_SCORE "NA"
#define SCORE_SPACE "\r"
#define NULL_SCORE_STR NULL_SCORE
#define NULL_SCORE_NUM -1
#include "RSUser.h"
#include "RecommenderSystemLoader.h"
class RSUsersLoader
{
private:


public:
    RSUsersLoader() = delete;
    /**
     *
     * loads users by the given format with their movie's ranks
     * @param users_file_path a path to the file of the users and their
     * movie ranks
     * @param rs RecommendingSystem for the Users
     * @return vector of the users created according to the file
     */
    static std::vector<RSUser> create_users_from_file(const std::string&
    users_file_path, std::unique_ptr<RecommenderSystem> rs) noexcept(false);

};


#endif //SCHOOL_SOLUTION_USERFACTORY_H
