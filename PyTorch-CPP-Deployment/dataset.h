#pragma once

#include <vector>
#include <tuple>
#include <torch/torch.h>
#include <opencv2/opencv.hpp>
#include <sstream>
#include <fstream>
#include "folder_reader.h"

class image_dataset : public torch::data::Dataset<image_dataset>
{
    private:
        std::vector<std::tuple<std::string>> path_to_files;
    public:
        explicit image_dataset(std::string& file_name) : path_to_files(folder_to_file(file_name)){};

        torch::data::Example<> get(size_t index) override {
            std::string file_location = std::get<0>(path_to_files[index]);
            //reads the image in RGB Format
            cv::Mat img = cv::imread(file_location,1);
            //resizes the image to fit the model input dimension
	        cv::resize(img, img, cv::Size(224,224), 0, 0, cv::INTER_LINEAR);
            //normalizes the image between values 0 and 1
	        cv::normalize(img, img, 0, 1, cv::NORM_MINMAX);
            //creates tensor from image array
            torch::Tensor img_tensor = torch::from_blob(img.data, {img.rows, img.cols, 3}, torch::kF32).clone();
            //reshapes the tensor to format C,H,W
            img_tensor = img_tensor.permute({2,0,1});
            return {img_tensor, img_tensor};
        };

        torch::optional<size_t> size() const override {
            return path_to_files.size();
        };
};