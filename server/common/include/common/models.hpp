#ifndef COMMON_MODELS_HPP
#define COMMON_MODELS_HPP

#include <nlohmann/json.hpp>
#include <string>
#include <vector>

namespace Common {
namespace Models {

const int kDumpTab = 4;
const std::string kUsername = "usager";
const std::string kPassword = "mot_de_passe";
const std::string kEdition = "edition";
const std::string kOld = "ancien";
const std::string kNew = "nouveau";
const std::string kAcronym = "sigle";
const std::string kName = "nom";
const std::string kTrimester = "trimestre";
const std::string kResults = "resultats";
const std::string kStudentResults = "resultatsEtudiant";
const std::string kFirstName = "prenom";
const std::string kId = "matricule";
const std::string kGrade = "note";
const std::string kLastBlocks = "dernier_blocs";
const std::string kBloc = "bloc";
const std::string kNext = "suivant";
const std::string kLast = "dernier";
const std::string kInformation = "information";
const std::string kNo = "no";
const std::string kSeverity = "severite";
const std::string kTime = "heure";
const std::string kMessage = "message";
const std::string kPdf = "pdf";
const std::string kListClasses = "listeClasses";
const std::string kStudentsInfo = "listeEtudiant";
const std::string kIsAdmin = "estAdmin";
const std::string kIsEditor = "estEditeur";

template <typename T>
inline T fromStr(const std::string& str) {
  return nlohmann::json::parse(str);
}

template <typename T>
inline std::string toStr(const T& obj) {
  return static_cast<nlohmann::json>(obj).dump(kDumpTab);
}

struct LoginRequest {
  std::string username;
  std::string password;
};

// NOLINTNEXTLINE(readability-identifier-naming, google-runtime-references)
inline void to_json(nlohmann::json& j, const LoginRequest& obj) {
  j = {{kUsername, obj.username}, {kPassword, obj.password}};
}

// NOLINTNEXTLINE(readability-identifier-naming, google-runtime-references)
inline void from_json(const nlohmann::json& j, LoginRequest& obj) {
  j.at(kUsername).get_to(obj.username);
  j.at(kPassword).get_to(obj.password);
}

struct LoginResponse {
  bool edition;
};

// NOLINTNEXTLINE(readability-identifier-naming, google-runtime-references)
inline void to_json(nlohmann::json& j, const LoginResponse& obj) { j = {{kEdition, obj.edition}}; }

// NOLINTNEXTLINE(readability-identifier-naming, google-runtime-references)
inline void from_json(const nlohmann::json& j, LoginResponse& obj) { j.at(kEdition).get_to(obj.edition); }

struct RegisterResponse {
  bool isAdmin;
  bool isEdition;
};

// NOLINTNEXTLINE(readability-identifier-naming, google-runtime-references)
inline void to_json(nlohmann::json& j, const RegisterResponse& obj) { 
  j = {{kIsAdmin, obj.isAdmin}, {kIsEditor, obj.isEdition}};
}

// NOLINTNEXTLINE(readability-identifier-naming, google-runtime-references)
inline void from_json(const nlohmann::json& j, RegisterResponse& obj) { 
  j.at(kIsAdmin).get_to(obj.isAdmin); 
  j.at(kIsEditor).get_to(obj.isEdition);
}

struct PasswordRequest {
  std::string oldPwd;
  std::string newPwd;
};

// NOLINTNEXTLINE(readability-identifier-naming, google-runtime-references)
inline void to_json(nlohmann::json& j, const PasswordRequest& obj) { j = {{kOld, obj.oldPwd}, {kNew, obj.newPwd}}; }

// NOLINTNEXTLINE(readability-identifier-naming, google-runtime-references)
inline void from_json(const nlohmann::json& j, PasswordRequest& obj) {
  j.at(kOld).get_to(obj.oldPwd);
  j.at(kNew).get_to(obj.newPwd);
}

struct Result {
  std::string lastName;
  std::string firstName;
  std::string id;
  std::string grade;
};

// NOLINTNEXTLINE(readability-identifier-naming, google-runtime-references)
inline void to_json(nlohmann::json& j, const Result& obj) {
  j = {{kName, obj.lastName}, {kFirstName, obj.firstName}, {kId, obj.id}, {kGrade, obj.grade}};
}

// NOLINTNEXTLINE(readability-identifier-naming, google-runtime-references)
inline void from_json(const nlohmann::json& j, Result& obj) {
  j.at(kFirstName).get_to(obj.firstName);
  j.at(kName).get_to(obj.lastName);
  j.at(kId).get_to(obj.id);
  j.at(kGrade).get_to(obj.grade);
}

struct TransactionRequest {
  std::string acronym;
  std::string name;
  int trimester = 0;
  std::vector<Result> results;
  std::string base64Pdf;
};

// NOLINTNEXTLINE(readability-identifier-naming, google-runtime-references)
inline void to_json(nlohmann::json& j, const TransactionRequest& obj) {
  j = {{kAcronym, obj.acronym},
       {kName, obj.name},
       {kTrimester, obj.trimester},
       {kResults, obj.results},
       {kPdf, obj.base64Pdf}};
}

// NOLINTNEXTLINE(readability-identifier-naming, google-runtime-references)
inline void from_json(const nlohmann::json& j, TransactionRequest& obj) {
  j.at(kAcronym).get_to(obj.acronym);
  j.at(kName).get_to(obj.name);
  j.at(kTrimester).get_to(obj.trimester);
  j.at(kResults).get_to(obj.results);
  j.at(kPdf).get_to(obj.base64Pdf);
}

struct ClassesRequest {
  std::string acronym;
  int trimester = 0;
};

// NOLINTNEXTLINE(readability-identifier-naming, google-runtime-references)
inline void to_json(nlohmann::json& j, const ClassesRequest& obj) {
  j = {{kAcronym, obj.acronym}, {kTrimester, obj.trimester}};
}

// NOLINTNEXTLINE(readability-identifier-naming, google-runtime-references)
inline void from_json(const nlohmann::json& j, ClassesRequest& obj) {
  j.at(kAcronym).get_to(obj.acronym);
  j.at(kTrimester).get_to(obj.trimester);
}

struct StudentRequest {
  std::string acronym;
  std::string trimester;
  std::string id;
};

// NOLINTNEXTLINE(readability-identifier-naming, google-runtime-references)
inline void to_json(nlohmann::json& j, const StudentRequest& obj) {
  j = {{kAcronym, obj.acronym}, {kTrimester, obj.trimester}, {kId, obj.id}};
}

// NOLINTNEXTLINE(readability-identifier-naming, google-runtime-references)
inline void from_json(const nlohmann::json& j, StudentRequest& obj) {
  j.at(kAcronym).get_to(obj.acronym);
  j.at(kTrimester).get_to(obj.trimester);
  j.at(kId).get_to(obj.id);
}

struct StudentResult{
  std::string acronym;
  int trimester = 0;
  std::string grade;
};

// NOLINTNEXTLINE(readability-identifier-naming, google-runtime-references)
inline void to_json(nlohmann::json& j, const StudentResult& obj) {
  j = {{kAcronym, obj.acronym}, {kTrimester, obj.trimester}, {kGrade, obj.grade}}; 
}

// NOLINTNEXTLINE(readability-identifier-naming, google-runtime-references)
inline void from_json(const nlohmann::json& j, StudentResult& obj) {
  j.at(kAcronym).get_to(obj.acronym); 
  j.at(kTrimester).get_to(obj.trimester); 
  j.at(kGrade).get_to(obj.grade); 
}

struct StudentResponse{
  std::vector<StudentResult> studentResults;
};

// NOLINTNEXTLINE(readability-identifier-naming, google-runtime-references)
inline void to_json(nlohmann::json& j, const StudentResponse& obj) { j = {{kStudentResults, obj.studentResults}}; }

// NOLINTNEXTLINE(readability-identifier-naming, google-runtime-references)
inline void from_json(const nlohmann::json& j, StudentResponse& obj) { j.at(kStudentResults).get_to(obj.studentResults); }

struct GradesRequest {
  std::string acronym;
  int trimester = 0;
};

// NOLINTNEXTLINE(readability-identifier-naming, google-runtime-references)
inline void to_json(nlohmann::json& j, const GradesRequest& obj) {
  j = {{kAcronym, obj.acronym}, {kTrimester, obj.trimester}};
}

// NOLINTNEXTLINE(readability-identifier-naming, google-runtime-references)
inline void from_json(const nlohmann::json& j, GradesRequest& obj) {
  j.at(kAcronym).get_to(obj.acronym);
  j.at(kTrimester).get_to(obj.trimester);
}

struct ClassInfo {
  std::string acronym;
  std::string name;
  int trimester = 0;
};

// NOLINTNEXTLINE(readability-identifier-naming, google-runtime-references)
inline void to_json(nlohmann::json& j, const ClassInfo& obj) {
  j = {{kAcronym, obj.acronym}, {kName, obj.name}, {kTrimester, obj.trimester}};
}

// NOLINTNEXTLINE(readability-identifier-naming, google-runtime-references)
inline void from_json(const nlohmann::json& j, ClassInfo& obj) {
  j.at(kAcronym).get_to(obj.acronym);
  j.at(kName).get_to(obj.name);
  j.at(kTrimester).get_to(obj.trimester);
}

struct ListClasses {
  std::vector<Common::Models::ClassInfo> classes;
};

// NOLINTNEXTLINE(readability-identifier-naming, google-runtime-references)
inline void to_json(nlohmann::json& j, const ListClasses& obj) { j = {{kListClasses, obj.classes}}; }

// NOLINTNEXTLINE(readability-identifier-naming, google-runtime-references)
inline void from_json(const nlohmann::json& j, ListClasses& obj) { j.at(kListClasses).get_to(obj.classes); }

struct StudentInfo {
  std::string lastName;
  std::string firstName;
  std::string id;
};

// NOLINTNEXTLINE(readability-identifier-naming, google-runtime-references)
inline void to_json(nlohmann::json& j, const StudentInfo& obj) {
  j = {{kName, obj.lastName}, {kFirstName, obj.firstName}, {kId, obj.id}};
}

// NOLINTNEXTLINE(readability-identifier-naming, google-runtime-references)
inline void from_json(const nlohmann::json& j, StudentInfo& obj) {
  j.at(kName).get_to(obj.lastName);
  j.at(kFirstName).get_to(obj.firstName);
  j.at(kId).get_to(obj.id);
}

struct ListStudentInfo{
  std::vector<Common::Models::StudentInfo> studentsInfo;
};

// NOLINTNEXTLINE(readability-identifier-naming, google-runtime-references)
inline void to_json(nlohmann::json& j, const ListStudentInfo& obj) { j = {{kStudentsInfo, obj.studentsInfo}}; }

// NOLINTNEXTLINE(readability-identifier-naming, google-runtime-references)
inline void from_json(const nlohmann::json& j, ListStudentInfo& obj) { j.at(kStudentsInfo).get_to(obj.studentsInfo); }

struct ChainRequest {
  int lastBlocks;
};

// NOLINTNEXTLINE(readability-identifier-naming, google-runtime-references)
inline void to_json(nlohmann::json& j, const ChainRequest& obj) { j = {{kLastBlocks, obj.lastBlocks}}; }

// NOLINTNEXTLINE(readability-identifier-naming, google-runtime-references)
inline void from_json(const nlohmann::json& j, ChainRequest& obj) { j.at(kLastBlocks).get_to(obj.lastBlocks); }

struct ChainResponse {
  std::string bloc;
  std::unique_ptr<ChainResponse> next;
};

// NOLINTNEXTLINE(readability-identifier-naming, google-runtime-references)
inline void to_json(nlohmann::json& j, const ChainResponse& obj) {
  j = {{kBloc, obj.bloc}};
  if (obj.next) {
    j.at(kNext) = *obj.next;
  }
}

// NOLINTNEXTLINE(readability-identifier-naming, google-runtime-references)
inline void from_json(const nlohmann::json& j, ChainResponse& obj) {
  j.at(kBloc).get_to(obj.bloc);
  j.at(kNext).get_to(*obj.next);
}

struct LogsRequest {
  int last;
};

// NOLINTNEXTLINE(readability-identifier-naming, google-runtime-references)
inline void to_json(nlohmann::json& j, const LogsRequest& obj) { j = {{kLast, obj.last}}; }

// NOLINTNEXTLINE(readability-identifier-naming, google-runtime-references)
inline void from_json(const nlohmann::json& j, LogsRequest& obj) { j.at(kLast).get_to(obj.last); }

struct Information {
  int no = 0;
  std::string severity;
  std::string time;
  std::string message;
};

// NOLINTNEXTLINE(readability-identifier-naming, google-runtime-references)
inline void to_json(nlohmann::json& j, const Information& obj) {
  j = {{kNo, obj.no}, {kSeverity, obj.severity}, {kTime, obj.time}, {kMessage, obj.message}};
}

// NOLINTNEXTLINE(readability-identifier-naming, google-runtime-references)
inline void from_json(const nlohmann::json& j, Information& obj) {
  j.at(kNo).get_to(obj.no);
  j.at(kSeverity).get_to(obj.severity);
  j.at(kTime).get_to(obj.time);
  j.at(kMessage).get_to(obj.message);
}

struct LogsResponse {
  std::vector<Information> information;
};

// NOLINTNEXTLINE(readability-identifier-naming, google-runtime-references)
inline void to_json(nlohmann::json& j, const LogsResponse& obj) { j = {{kInformation, obj.information}}; }

// NOLINTNEXTLINE(readability-identifier-naming, google-runtime-references)
inline void from_json(const nlohmann::json& j, LogsResponse& obj) { j.at(kInformation).get_to(obj.information); }

struct CreateAccountRequest {
  std::string username;
  std::string password;
  bool edition = false;
};

// NOLINTNEXTLINE(readability-identifier-naming, google-runtime-references)
inline void to_json(nlohmann::json& j, const CreateAccountRequest& obj) {
  j = {{kUsername, obj.username}, {kPassword, obj.password}, {kEdition, obj.edition}};
}

// NOLINTNEXTLINE(readability-identifier-naming, google-runtime-references)
inline void from_json(const nlohmann::json& j, CreateAccountRequest& obj) {
  j.at(kUsername).get_to(obj.username);
  j.at(kPassword).get_to(obj.password);
  j.at(kEdition).get_to(obj.edition);
}

struct DeleteAccountRequest {
  std::string username;
};

// NOLINTNEXTLINE(readability-identifier-naming, google-runtime-references)
inline void to_json(nlohmann::json& j, const DeleteAccountRequest& obj) { j = {{kUsername, obj.username}}; }

// NOLINTNEXTLINE(readability-identifier-naming, google-runtime-references)
inline void from_json(const nlohmann::json& j, DeleteAccountRequest& obj) { j.at(kUsername).get_to(obj.username); }

struct ClassesResponse {
  std::vector<Result> results;
};

// NOLINTNEXTLINE(readability-identifier-naming, google-runtime-references)
inline void to_json(nlohmann::json& j, const ClassesResponse& obj) { j = {{kResults, obj.results}}; }

// NOLINTNEXTLINE(readability-identifier-naming, google-runtime-references)
inline void from_json(const nlohmann::json& j, ClassesResponse& obj) { j.at(kResults).get_to(obj.results); }

}  // namespace Models
}  // namespace Common

#endif  // COMMON_MODELS_HPP
