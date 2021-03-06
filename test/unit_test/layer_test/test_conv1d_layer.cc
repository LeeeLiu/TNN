// Tencent is pleased to support the open source community by making TNN available.
//
// Copyright (C) 2020 THL A29 Limited, a Tencent company. All rights reserved.
//
// Licensed under the BSD 3-Clause License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// https://opensource.org/licenses/BSD-3-Clause
//
// Unless required by applicable law or agreed to in writing, software distributed
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.

#include "test/unit_test/layer_test/layer_test.h"
#include "test/unit_test/unit_test_common.h"
#include "test/unit_test/utils/network_helpers.h"
#include "tnn/utils/cpu_utils.h"
#include "tnn/utils/dims_utils.h"

namespace TNN_NS {

class Conv1DLayerTest : public LayerTest,
                      public ::testing::WithParamInterface<
                          std::tuple<int, int, int, int, int, int, int, int, int, DataType, ActivationType>> {};

INSTANTIATE_TEST_SUITE_P(LayerTest, Conv1DLayerTest,
                         ::testing::Combine(  // batch
                             testing::Values(1),
                             // channel
                             testing::Values(4, 15, 32, 63, 128, 1023),
                             // hw
                             testing::Values(4, 15, 32, 63, 128, 1023),
                             // group
                             testing::Values(1),
                             // kernel
                             testing::Values(1, 2),
                             // dilation
                             testing::Values(1),
                             // stride
                             testing::Values(1, 2),
                             // pads
                             testing::Values(0),
                             // pad type
                             testing::Values(-1),
                             // data_type
                             testing::Values(DATA_TYPE_FLOAT, DATA_TYPE_HALF),
                             // activation_type
                             testing::Values(ActivationType_None, ActivationType_ReLU, ActivationType_ReLU6,
                                             ActivationType_SIGMOID_MUL)));

TEST_P(Conv1DLayerTest, Conv1DLayer) {
    // get param
    int batch             = std::get<0>(GetParam());
    int channel_per_group = std::get<1>(GetParam());
    int input_size        = std::get<2>(GetParam());
    int group             = std::get<3>(GetParam());
    int channel           = group * channel_per_group;
    int kernel            = std::get<4>(GetParam());
    int dilation          = std::get<5>(GetParam());
    int stride            = std::get<6>(GetParam());
    int pad               = std::get<7>(GetParam());
    int pad_type          = std::get<8>(GetParam());
    auto dtype            = std::get<9>(GetParam());
    int activation_type   = std::get<10>(GetParam());
    DeviceType dev        = ConvertDeviceType(FLAGS_dt);

    if(CheckDataTypeSkip(dtype)) {
        GTEST_SKIP();
    }

    if (activation_type == ActivationType_SIGMOID_MUL && DEVICE_CUDA == dev) {
        GTEST_SKIP();
    }

    if (activation_type == ActivationType_ReLU6 && DEVICE_X86 == dev) {
        GTEST_SKIP();
    }
    if (activation_type == ActivationType_SIGMOID_MUL && DEVICE_X86 == dev) {
        GTEST_SKIP();
    }

    // param
    std::shared_ptr<ConvLayerParam> param(new ConvLayerParam());
    param->name            = "Conv1D";
    param->input_channel   = channel;
    param->output_channel  = channel;
    param->group           = group;
    param->kernels         = {kernel};
    param->dialations      = {dilation};
    param->strides         = {stride};
    param->pads            = {pad, pad};
    param->pad_type        = pad_type;
    param->bias            = 1;
    param->activation_type = activation_type;

    // generate interpreter
    Precision precision         = SetPrecision(dev, dtype);
    std::vector<int> input_dims = {batch, channel, input_size};
    auto interpreter            = GenerateInterpreter("Convolution1D", {input_dims}, param);
    Run(interpreter, precision);
}

}  // namespace TNN_NS
