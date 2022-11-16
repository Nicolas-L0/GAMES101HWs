#include <chrono>
#include <iostream>
#include <opencv2/opencv.hpp>

const int point_num = 8;

std::vector<cv::Point2f> control_points;

void mouse_handler(int event, int x, int y, int flags, void *userdata) 
{
    if (event == cv::EVENT_LBUTTONDOWN && control_points.size() < point_num) 
    {
        std::cout << "Left button of the mouse is clicked - position (" << x << ", "
        << y << ")" << '\n';
        control_points.emplace_back(x, y);
    }     
}

void naive_bezier(const std::vector<cv::Point2f> &points, cv::Mat &window) 
{
    auto &p_0 = points[0];
    auto &p_1 = points[1];
    auto &p_2 = points[2];
    auto &p_3 = points[3];

    for (double t = 0.0; t <= 1.0; t += 0.001) 
    {
        auto point = std::pow(1 - t, 3) * p_0 + 3 * t * std::pow(1 - t, 2) * p_1 +
                 3 * std::pow(t, 2) * (1 - t) * p_2 + std::pow(t, 3) * p_3;

        window.at<cv::Vec3b>(point.y, point.x)[2] = 255;  //BGR
    }
}

cv::Point2f recursive_bezier(const std::vector<cv::Point2f> &control_points, float t) 
{
    // TODO: Implement de Casteljau's algorithm

    //递归直到最后一个点，得到该t值时目标曲线上动点的坐标，将其返回；
    if (control_points.size() == 1)
        return control_points[0];

    std::vector<cv::Point2f> _points;

    for (int i = 0; i < control_points.size() - 1; i++)
    {   
        cv::Point2f point = cv::Point2f((1 - t) * control_points[i].x + t * control_points[i + 1].x,
                                        (1 - t) * control_points[i].y + t * control_points[i + 1].y);
        _points.push_back(point);
    }
    

    // 递归
    return recursive_bezier(_points, t);

}

void bezier(const std::vector<cv::Point2f> &control_points, cv::Mat &window) 
{
    // TODO: Iterate through all t = 0 to t = 1 with small steps, and call de Casteljau's 
    // recursive Bezier algorithm.
    for (double t = 0.f; t <= 1.0; t += 0.001)
    {
        cv::Point2f point = recursive_bezier(control_points, t);
        window.at<cv::Vec3b>(point.y, point.x)[1] = 255;  //BGR

        //AA ref: https://games-cn.org/forums/topic/%E4%BD%9C%E4%B8%9A%E5%9B%9B%E5%BE%97%E5%88%B0%E8%BF%99%E6%A0%B7%E7%9A%84%E7%BB%93%E6%9E%9C%E6%98%AF%E5%90%A6%E6%BB%A1%E8%B6%B3%E8%A6%81%E6%B1%82%EF%BC%9F/
        float x = (floor(point.x) + ceil(point.x))/2;
        float y = (floor(point.y) + ceil(point.y))/2;
        float dist = std::sqrt(std::pow(point.x - x, 2) + std::pow(point.y - y, 2));
        float x_var[4] = {+1.0, -1.0, 0.0, 0.0};
        float y_var[4] = {0.0, 0.0, +1.0, -1.0};
        for (int i = 0; i < 4; i++)
        {
            float x_neibor = x + x_var[i];
            float y_neibor = y + y_var[i];
            if(x_neibor >= 0 && x_neibor <= 700 && y_neibor >= 0 && y_neibor <= 700)
            {
                float weight = dist / std::sqrt((std::pow(x_neibor - point.x, 2) + std::pow(y_neibor - point.y, 2)));
                window.at<cv::Vec3b>(y_neibor, x_neibor)[1] = std::max(float(window.at<cv::Vec3b>(y_neibor, x_neibor)[1]), 255 * weight);
            }
        }
        
    }
}

int main() 
{
    cv::Mat window = cv::Mat(700, 700, CV_8UC3, cv::Scalar(0));
    cv::cvtColor(window, window, cv::COLOR_BGR2RGB);
    cv::namedWindow("Bezier Curve", cv::WINDOW_AUTOSIZE);

    cv::setMouseCallback("Bezier Curve", mouse_handler, nullptr);

    int key = -1;
    while (key != 27) 
    {
        for (auto &point : control_points) 
        {
            cv::circle(window, point, 3, {255, 255, 255}, 3);
        }

        if (control_points.size() == point_num) 
        {
            //naive_bezier(control_points, window);
            bezier(control_points, window);

            cv::imshow("Bezier Curve", window);
            cv::imwrite("my_bezier_curve.png", window);
            key = cv::waitKey(0);

            return 0;
        }

        cv::imshow("Bezier Curve", window);
        key = cv::waitKey(20);
    }

return 0;
}
