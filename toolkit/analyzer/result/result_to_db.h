#pragma once
#include "db/db.h"
#include "result/result_target.h"

class result_to_db : public result_target {

public:
  result_to_db(const std::string &url, const std::string &usrname,
               const std::string &passwd, const std::string &dbname,
               const std::string &request_hash);

  virtual void write_to_target(const ypc::bref &encrypted_result,
                               const ypc::bref &result_signature,
                               const ypc::bref &data_hash);
  virtual void read_from_target(ypc::bytes &encrypted_result,
                                ypc::bytes &result_signature,
                                ypc::bytes &data_hash);

protected:
  using request_db = toolkit::analyzer::request_db;
  std::unique_ptr<request_db> m_db;
  std::string m_request_hash;
};
