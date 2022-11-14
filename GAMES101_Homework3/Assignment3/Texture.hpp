//
// Created by LEI XU on 4/27/19.
//

#ifndef RASTERIZER_TEXTURE_H
#define RASTERIZER_TEXTURE_H
#include "global.hpp"
#include <eigen3/Eigen/Eigen>
#include <opencv2/opencv.hpp>
class Texture{
private:
    cv::Mat image_data;

public:
    Texture(const std::string& name)
    {
        image_data = cv::imread(name);
        cv::cvtColor(image_data, image_data, cv::COLOR_RGB2BGR);
        width = image_data.cols;
        height = image_data.rows;
    }

    int width, height;

    Eigen::Vector3f getColor(float u, float v)
    {
        // to solve uv > 1 or < 0, ref: https://games-cn.org/forums/topic/zuoye3uvzuobiaoquzhifanwei/
        u = std::clamp(u, 0.f, 1.f);
        v = std::clamp(v, 0.f, 1.f);

        auto u_img = u * width;
        auto v_img = (1 - v) * height;
        auto color = image_data.at<cv::Vec3b>(v_img, u_img);
        return Eigen::Vector3f(color[0], color[1], color[2]);
    }

    Eigen::Vector3f getColorBilinear(float u,float v)
    {
        auto u_img = u * width;
        auto v_img = (1 - v) * height;
        //auto color = image_data.at<cv::Vec3b>(v_img, u_img);  //aatention, v before u!

        Eigen::Vector2f u00 {floor(u_img + 0.5) - 0.5, floor(v_img + 0.5) - 0.5};
        Eigen::Vector2f u01 {floor(u_img + 0.5) - 0.5, floor(v_img + 0.5) + 0.5};
        Eigen::Vector2f u10 {floor(u_img + 0.5) + 0.5, floor(v_img + 0.5) - 0.5};
        Eigen::Vector2f u11 {floor(u_img + 0.5) + 0.5, floor(v_img + 0.5) + 0.5};

        float s = u_img - u00.x();
        float t = v_img - u00.y();

        auto u00_color = image_data.at<cv::Vec3b>(u00.y(), u00.x());
        auto u01_color = image_data.at<cv::Vec3b>(u01.y(), u01.x());
        auto u10_color = image_data.at<cv::Vec3b>(u10.y(), u10.x());
        auto u11_color = image_data.at<cv::Vec3b>(u11.y(), u11.x());

        auto u0_color = u00_color + s * (u10_color - u00_color);
        auto u1_color = u01_color + s * (u11_color - u01_color);
        auto color = u0_color + t * (u1_color - u0_color);

        return Eigen::Vector3f(color[0], color[1], color[2]);
    }

};
#endif //RASTERIZER_TEXTURE_H
