/*
 *
 * Copyright 2015 gRPC authors.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 */

/* Test various operations on grpc_error */

#include <assert.h>
#include <benchmark/benchmark.h>
#include <memory>

#include "src/core/lib/iomgr/error.h"
#include "src/core/lib/transport/error_utils.h"

#include "test/core/util/test_config.h"
#include "test/cpp/microbenchmarks/helpers.h"
#include "test/cpp/util/test_config.h"

#include "absl/status/status.h"

typedef void (*grpc_iomgr_cb_func)(void* arg, grpc_error* error);
typedef void (*grpc_iomgr_cb_func2)(void* arg, absl::Status error);

static int a = 0;
static int b = 0;

grpc_iomgr_cb_func f1 = [](void* x, grpc_error* y) {
  if (y == nullptr) a += 1; else b += 1;
};

grpc_iomgr_cb_func2 f2 = [](void* x, absl::Status y) {
  if (y.ok()) a += 1; else b += 1;
};

static void BM_grpc_error_noerror(benchmark::State& state) {
  grpc_error* error = nullptr;
  for (auto _ : state) {
    f1(nullptr, error);
  }
}

BENCHMARK(BM_grpc_error_noerror);

static void BM_grpc_error_error(benchmark::State& state) {
  grpc_error* error = GRPC_ERROR_CANCELLED;
  for (auto _ : state) {
    f1(nullptr, error);
  }
}

BENCHMARK(BM_grpc_error_error);

static void BM_absl_status_noerror(benchmark::State& state) {
  absl::Status status; // = absl::OkStatus();
  for (auto _ : state) {
    f2(nullptr, status);
  }
}

BENCHMARK(BM_absl_status_noerror);

static void BM_absl_status_error(benchmark::State& state) {
  absl::Status status = absl::CancelledError();
  for (auto _ : state) {
    f2(nullptr, status);
  }
}

BENCHMARK(BM_absl_status_error);

static void BM_absl_status_error_noninlined(benchmark::State& state) {
  absl::Status status = absl::CancelledError();
  status.SetPayload("a", absl::Cord());
  for (auto _ : state) {
    f2(nullptr, status);
  }
}

BENCHMARK(BM_absl_status_error_noninlined);

// Some distros have RunSpecifiedBenchmarks under the benchmark namespace,
// and others do not. This allows us to support both modes.
namespace benchmark {
void RunTheBenchmarksNamespaced() { RunSpecifiedBenchmarks(); }
}  // namespace benchmark

int main(int argc, char** argv) {
  grpc::testing::TestEnvironment env(argc, argv);
  LibraryInitializer libInit;
  ::benchmark::Initialize(&argc, argv);
  ::grpc::testing::InitTest(&argc, &argv, false);
  benchmark::RunTheBenchmarksNamespaced();
  return 0;
}
