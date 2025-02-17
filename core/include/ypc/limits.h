//! should be sgx compatible
#pragma once
#include <cstdint>

namespace ypc {
constexpr static uint32_t max_item_size = 64 * 1024;
constexpr static uint32_t max_sample_size = 4 * 1024 * 1024;
constexpr static uint32_t max_data_format_size = 1 * 1024 * 1024;
} // namespace ypc
