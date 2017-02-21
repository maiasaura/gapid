// Copyright (c) 2016 Google Inc.
//
// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and/or associated documentation files (the
// "Materials"), to deal in the Materials without restriction, including
// without limitation the rights to use, copy, modify, merge, publish,
// distribute, sublicense, and/or sell copies of the Materials, and to
// permit persons to whom the Materials are furnished to do so, subject to
// the following conditions:
//
// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Materials.
//
// MODIFICATIONS TO THIS FILE MAY MEAN IT NO LONGER ACCURATELY REFLECTS
// KHRONOS STANDARDS. THE UNMODIFIED, NORMATIVE VERSIONS OF KHRONOS
// SPECIFICATIONS AND HEADER INFORMATION ARE LOCATED AT
//    https://www.khronos.org/registry/
//
// THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
// IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
// CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
// MATERIALS OR THE USE OR OTHER DEALINGS IN THE MATERIALS.

#include <memory>
#include <vector>

#include <gtest/gtest.h>

#include "opt/make_unique.h"
#include "opt/types.h"

namespace {

using namespace spvtools::opt::analysis;
using spvtools::MakeUnique;

// Fixture class providing some element types.
class SameTypeTest : public ::testing::Test {
 protected:
  virtual void SetUp() override {
    void_t_.reset(new Void());
    u32_t_.reset(new Integer(32, false));
    f64_t_.reset(new Float(64));
    v3u32_t_.reset(new Vector(u32_t_.get(), 3));
    image_t_.reset(new Image(f64_t_.get(), SpvDim2D, 1, 1, 0, 0,
                             SpvImageFormatR16, SpvAccessQualifierReadWrite));
  }

  // Element types to be used for constructing other types for testing.
  std::unique_ptr<Type> void_t_;
  std::unique_ptr<Type> u32_t_;
  std::unique_ptr<Type> f64_t_;
  std::unique_ptr<Type> v3u32_t_;
  std::unique_ptr<Type> image_t_;
};

#define TestMultipleInstancesOfTheSameType(ty, ...)                       \
  TEST_F(SameTypeTest, MultiSame##ty) {                                   \
    std::vector<std::unique_ptr<Type>> types;                             \
    for (int i = 0; i < 10; ++i) types.emplace_back(new ty(__VA_ARGS__)); \
    for (size_t i = 0; i < types.size(); ++i) {                           \
      for (size_t j = 0; j < types.size(); ++j) {                         \
        EXPECT_TRUE(types[i]->IsSame(types[j].get()))                     \
            << "expected '" << types[i]->str() << "' is the same as '"    \
            << types[j]->str() << "'";                                    \
      }                                                                   \
    }                                                                     \
  }
TestMultipleInstancesOfTheSameType(Void);
TestMultipleInstancesOfTheSameType(Bool);
TestMultipleInstancesOfTheSameType(Integer, 32, true);
TestMultipleInstancesOfTheSameType(Float, 64);
TestMultipleInstancesOfTheSameType(Vector, u32_t_.get(), 3);
TestMultipleInstancesOfTheSameType(Matrix, v3u32_t_.get(), 4);
TestMultipleInstancesOfTheSameType(Image, f64_t_.get(), SpvDimCube, 0, 0, 1, 1,
                                   SpvImageFormatRgb10A2,
                                   SpvAccessQualifierWriteOnly);
TestMultipleInstancesOfTheSameType(Sampler);
TestMultipleInstancesOfTheSameType(SampledImage, image_t_.get());
TestMultipleInstancesOfTheSameType(Array, u32_t_.get(), 10);
TestMultipleInstancesOfTheSameType(RuntimeArray, u32_t_.get());
TestMultipleInstancesOfTheSameType(Struct, std::vector<Type*>{u32_t_.get(),
                                                              f64_t_.get()});
TestMultipleInstancesOfTheSameType(Opaque, "testing rocks");
TestMultipleInstancesOfTheSameType(Pointer, u32_t_.get(), SpvStorageClassInput);
TestMultipleInstancesOfTheSameType(Function, u32_t_.get(),
                                   {f64_t_.get(), f64_t_.get()});
TestMultipleInstancesOfTheSameType(Event);
TestMultipleInstancesOfTheSameType(DeviceEvent);
TestMultipleInstancesOfTheSameType(ReserveId);
TestMultipleInstancesOfTheSameType(Queue);
TestMultipleInstancesOfTheSameType(Pipe, SpvAccessQualifierReadWrite);
TestMultipleInstancesOfTheSameType(ForwardPointer, 10, SpvStorageClassUniform);
TestMultipleInstancesOfTheSameType(PipeStorage);
TestMultipleInstancesOfTheSameType(NamedBarrier);
#undef TestMultipleInstanceOfTheSameType

TEST(Types, AllTypes) {
  // Types in this test case are only equal to themselves, nothing else.
  std::vector<std::unique_ptr<Type>> types;

  // Forward Pointer
  types.emplace_back(new ForwardPointer(10000, SpvStorageClassInput));
  types.emplace_back(new ForwardPointer(20000, SpvStorageClassInput));

  // Void, Bool
  types.emplace_back(new Void());
  auto* voidt = types.back().get();
  types.emplace_back(new Bool());
  auto* boolt = types.back().get();

  // Integer
  types.emplace_back(new Integer(32, true));
  auto* s32 = types.back().get();
  types.emplace_back(new Integer(32, false));
  types.emplace_back(new Integer(64, true));
  types.emplace_back(new Integer(64, false));
  auto* u64 = types.back().get();

  // Float
  types.emplace_back(new Float(32));
  auto* f32 = types.back().get();
  types.emplace_back(new Float(64));

  // Vector
  types.emplace_back(new Vector(s32, 2));
  types.emplace_back(new Vector(s32, 3));
  auto* v3s32 = types.back().get();
  types.emplace_back(new Vector(u64, 4));
  types.emplace_back(new Vector(f32, 3));
  auto* v3f32 = types.back().get();

  // Matrix
  types.emplace_back(new Matrix(v3s32, 3));
  types.emplace_back(new Matrix(v3s32, 4));
  types.emplace_back(new Matrix(v3f32, 4));

  // Images
  types.emplace_back(new Image(s32, SpvDim2D, 0, 0, 0, 0, SpvImageFormatRg8,
                               SpvAccessQualifierReadOnly));
  auto* image1 = types.back().get();
  types.emplace_back(new Image(s32, SpvDim2D, 0, 1, 0, 0, SpvImageFormatRg8,
                               SpvAccessQualifierReadOnly));
  types.emplace_back(new Image(s32, SpvDim3D, 0, 1, 0, 0, SpvImageFormatRg8,
                               SpvAccessQualifierReadOnly));
  types.emplace_back(new Image(voidt, SpvDim3D, 0, 1, 0, 1, SpvImageFormatRg8,
                               SpvAccessQualifierReadWrite));
  auto* image2 = types.back().get();

  // Sampler
  types.emplace_back(new Sampler());

  // Sampled Image
  types.emplace_back(new SampledImage(image1));
  types.emplace_back(new SampledImage(image2));

  // Array
  types.emplace_back(new Array(f32, 100));
  types.emplace_back(new Array(f32, 42));
  auto* a42f32 = types.back().get();
  types.emplace_back(new Array(u64, 24));

  // RuntimeArray
  types.emplace_back(new RuntimeArray(v3f32));
  types.emplace_back(new RuntimeArray(v3s32));
  auto* rav3s32 = types.back().get();

  // Struct
  types.emplace_back(new Struct(std::vector<Type*>{s32}));
  types.emplace_back(new Struct(std::vector<Type*>{s32, f32}));
  auto* sts32f32 = types.back().get();
  types.emplace_back(new Struct(std::vector<Type*>{u64, a42f32, rav3s32}));

  // Opaque
  types.emplace_back(new Opaque(""));
  types.emplace_back(new Opaque("hello"));
  types.emplace_back(new Opaque("world"));

  // Pointer
  types.emplace_back(new Pointer(f32, SpvStorageClassInput));
  types.emplace_back(new Pointer(sts32f32, SpvStorageClassFunction));
  types.emplace_back(new Pointer(a42f32, SpvStorageClassFunction));

  // Function
  types.emplace_back(new Function(voidt, {}));
  types.emplace_back(new Function(voidt, {boolt}));
  types.emplace_back(new Function(voidt, {boolt, s32}));
  types.emplace_back(new Function(s32, {boolt, s32}));

  // Event, Device Event, Reserve Id, Queue,
  types.emplace_back(new Event());
  types.emplace_back(new DeviceEvent());
  types.emplace_back(new ReserveId());
  types.emplace_back(new Queue());

  // Pipe, Forward Pointer, PipeStorage, NamedBarrier
  types.emplace_back(new Pipe(SpvAccessQualifierReadWrite));
  types.emplace_back(new Pipe(SpvAccessQualifierReadOnly));
  types.emplace_back(new ForwardPointer(1, SpvStorageClassInput));
  types.emplace_back(new ForwardPointer(2, SpvStorageClassInput));
  types.emplace_back(new ForwardPointer(2, SpvStorageClassUniform));
  types.emplace_back(new PipeStorage());
  types.emplace_back(new NamedBarrier());

  for (size_t i = 0; i < types.size(); ++i) {
    for (size_t j = 0; j < types.size(); ++j) {
      if (i == j) {
        EXPECT_TRUE(types[i]->IsSame(types[j].get()))
            << "expected '" << types[i]->str() << "' is the same as '"
            << types[j]->str() << "'";
      } else {
        EXPECT_FALSE(types[i]->IsSame(types[j].get()))
            << "expected '" << types[i]->str() << "' is different to '"
            << types[j]->str() << "'";
      }
    }
  }
}

TEST(Types, IntWidth) {
  std::vector<uint32_t> widths = {1, 2, 4, 8, 16, 32, 48, 64, 128};
  std::vector<std::unique_ptr<Integer>> types;
  for (uint32_t w : widths) {
    types.emplace_back(new Integer(w, true));
  }
  for (size_t i = 0; i < widths.size(); i++) {
    EXPECT_EQ(widths[i], types[i]->width());
  }
}

TEST(Types, FloatWidth) {
  std::vector<uint32_t> widths = {1, 2, 4, 8, 16, 32, 48, 64, 128};
  std::vector<std::unique_ptr<Float>> types;
  for (uint32_t w : widths) {
    types.emplace_back(new Float(w));
  }
  for (size_t i = 0; i < widths.size(); i++) {
    EXPECT_EQ(widths[i], types[i]->width());
  }
}

TEST(Types, VectorElementCount) {
  auto s32 = MakeUnique<Integer>(32, true);
  for (uint32_t c : {2, 3, 4}) {
    auto s32v = MakeUnique<Vector>(s32.get(), c);
    EXPECT_EQ(c, s32v->element_count());
  }
}

TEST(Types, MatrixElementCount) {
  auto s32 = MakeUnique<Integer>(32, true);
  auto s32v4 = MakeUnique<Vector>(s32.get(), 4);
  for (uint32_t c : {1, 2, 3, 4, 10, 100}) {
    auto s32m = MakeUnique<Matrix>(s32v4.get(), c);
    EXPECT_EQ(c, s32m->element_count());
  }
}

}  // anonymous namespace