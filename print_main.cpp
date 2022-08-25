//
//
//
//
//#include "RecommenderSystemLoader.h"
//#include "RSUsersLoader.h"
//#include <fstream>
//
//int main(){
//    Movie m("A",1999);
//    std::cout << m << std::endl;
//    auto rs = RecommenderSystemLoader::create_rs_from_movies_file
//        ("RecommenderSystemLoader_input.txt");
//    std::cout << *rs << std::endl;
//    auto users = RSUsersLoader::create_users_from_file
//        ("RSUsersLoader_file.txt",
//         std::move(rs));
////    std::ifstream file("RSUsersLoader_file.txt");
////    std::cout << file.fail() << std::endl;
////  std::ifstream file1("../RecommenderSystemLoader_input.txt",std::ios::in);
////    std::cout << file1.fail() << std::endl;
//
//    std::cout << users[0] << std::endl;
//
//
//}