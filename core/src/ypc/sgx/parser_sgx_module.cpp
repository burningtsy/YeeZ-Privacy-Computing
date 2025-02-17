#include "ypc/sgx/parser_sgx_module.h"
#include "eparser_u.h"
#include "sgx_urts.h"
#include <stdexcept>

parser_sgx_module::parser_sgx_module(const char *mod_path)
    : ::stbox::sgx_module(mod_path) {}
parser_sgx_module::~parser_sgx_module() {}

stx_status parser_sgx_module::begin_parse_data_item() {
  auto retval = ecall<uint32_t>(::begin_parse_data_item);
  if (retval != SGX_SUCCESS) {
    throw std::runtime_error(std::to_string(retval));
  }
  return static_cast<stx_status>(retval);
}

stx_status parser_sgx_module::parse_data_item(const char *data, size_t len) {
  auto retval = ecall<uint32_t>(::parse_data_item, (uint8_t *)data,
                                static_cast<uint32_t>(len));
  if (retval != SGX_SUCCESS) {
    throw std::runtime_error(std::to_string(retval));
  }
  return static_cast<stx_status>(retval);
}

stx_status parser_sgx_module::end_parse_data_item() {
  auto retval = ecall<uint32_t>(::end_parse_data_item);
  if (retval != SGX_SUCCESS) {
    throw std::runtime_error(std::to_string(retval));
  }
  return static_cast<stx_status>(retval);
}

stx_status parser_sgx_module::get_enclave_hash(ypc::bref &_enclave_hash) {
  uint32_t hash_size;
  uint8_t *enclave_hash;
  stbox::buffer_length_t buf_res(&hash_size, &enclave_hash,
                                 ::get_enclave_hash_size);
  auto t = ecall<uint32_t>(::get_enclave_hash, stbox::xmem(buf_res),
                           stbox::xlen(buf_res));

  _enclave_hash = ypc::bref(enclave_hash, hash_size);
  return static_cast<stx_status>(t);
}

stx_status
parser_sgx_module::get_encrypted_result_and_signature(ypc::bref &_encrypted_res,
                                                      ypc::bref &_result_sig) {
  uint32_t res_size, sig_size;
  uint8_t *encrypted_res, *result_sig;
  stbox::buffer_length_t buf_res(&res_size, &encrypted_res,
                                 ::get_encrypted_result_size);
  stbox::buffer_length_t buf_sig(&sig_size, &result_sig,
                                 ::get_secp256k1_signature_size);
  auto t = ecall<uint32_t>(::get_encrypted_result_and_signature,
                           stbox::xmem(buf_res), stbox::xlen(buf_res),
                           stbox::xmem(buf_sig), stbox::xlen(buf_sig));
  _encrypted_res = ypc::bref(encrypted_res, res_size);
  _result_sig = ypc::bref(result_sig, sig_size);
  return static_cast<stx_status>(t);
}

stx_status parser_sgx_module::get_data_hash(ypc::bref &_data_hash) {
  uint32_t hash_size;
  uint8_t *data_hash;
  stbox::buffer_length_t buf_res(&hash_size, &data_hash, ::get_data_hash_size);
  auto t = ecall<uint32_t>(::get_data_hash, stbox::xmem(buf_res),
                           stbox::xlen(buf_res));

  _data_hash = ypc::bref(data_hash, hash_size);
  return static_cast<stx_status>(t);
}

stx_status parser_sgx_module::add_block_parse_result(
    uint16_t block_index, const uint8_t *block_result, uint32_t res_size,
    const uint8_t *data_hash, uint32_t hash_size, const uint8_t *sig,
    uint32_t sig_size) {

  auto retval = ecall<uint32_t>(
      ::add_block_parse_result, block_index, (uint8_t *)block_result, res_size,
      (uint8_t *)data_hash, hash_size, (uint8_t *)sig, sig_size);

  if (retval != SGX_SUCCESS) {
    throw std::runtime_error(std::to_string(retval));
  }
  return static_cast<stx_status>(retval);
}

stx_status parser_sgx_module::merge_parse_result(const uint8_t *encrypted_param,
                                                 uint32_t len) {
  auto retval =
      ecall<uint32_t>(::merge_parse_result, (uint8_t *)encrypted_param,
                      static_cast<uint32_t>(len));

  if (retval != SGX_SUCCESS) {
    throw std::runtime_error(std::to_string(retval));
  }
  return static_cast<stx_status>(retval);
}

bool parser_sgx_module::need_continue() {
  auto retval = ecall<uint32_t>(::need_continue);
  return retval != 0;
}
