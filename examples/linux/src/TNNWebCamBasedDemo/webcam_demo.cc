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

#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>

#include <iostream>
#include <string>
#include <memory>
#include <stdio.h>

#include "tnn_sdk_sample.h"
#include "worker.h"
#include "utils/utils.h"
#include "macro.h"

#include "gflags/gflags.h"

static const char help_message[] = "print a usage message.";
static const char mode_dir_message[] = "model path. recommend: ../../../../model";
static const char video_dir_message[] = "video path. recommend: ./benchmark0722/benchmark0722.mp4";

DEFINE_bool(h, false, help_message);
DEFINE_string(m, "", mode_dir_message);
DEFINE_string(v, "", video_dir_message);
DEFINE_string(i, "", "");

static void ShowUsage(const char *exe) {
    printf("usage:\n%s [-h] [-m] model_directory\n", exe);
    printf("\t -h, <help>     \t%s\n", help_message);
    printf("\t -m, <model_directory>     \t%s\n", mode_dir_message);
	printf("\t -v, <video_directory>     \t%s\n", video_dir_message);
}

using namespace TNN_NS;
//using namespace cv;
 
int main(int argc, char** argv)
{
	gflags::ParseCommandLineNonHelpFlags(&argc, &argv, true);
    if (FLAGS_h) {
        ShowUsage(argv[0]);
        return false;
    }

	int index = atoi(FLAGS_i.c_str());

	char path_input[50];
	snprintf(path_input, 50, "./video/frame/%d.png", index);
	cv::Mat frame = cv::imread(path_input);

	//namedWindow("图像");
	//imshow("图像", frame);

    Worker worker;
    auto status = worker.Init(FLAGS_m.c_str());
    if (status != TNN_OK) {
        LOGERROR(status);
        return -1;
    }

	cv::Mat frame_paint = frame.clone();
	worker.FrocessFrame(index, frame, frame_paint);

	char path[50];
	snprintf(path, 50, "./video/frame_paint/%d.png", index);
	cv::imwrite(path, frame_paint);
	cv::waitKey(0);
	return 0;
}