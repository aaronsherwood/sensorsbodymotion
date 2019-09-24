//
//  cvshape.cpp
//  myDelightfulSketch
//
//  Created by aaron sherwood on 9/24/19.
//
//

#include "cvshape.hpp"

string CVShape::getLabel(){
    return labelState;
}

void CVShape::update(ofPixels pix){
    pixelsRep = pix;
    Mat src = toCv(pixelsRep);
    if (src.empty())
        ofLog()<<"Error image";
    cvtColor(src, gray, CV_BGR2GRAY);
    Canny(gray, bw, 0, 50, 5);
    
    contours.findContours(bw);
    contours.setSimplify(true);
    dst = src.clone();
    
    for (int i = 0; i < contours.size(); i++)
    {
        approxPolyDP(Mat(contours.getContour(i)), approx, arcLength(Mat(contours.getContour(i)), true)*0.02, true);
        if (std::fabs(contourArea(contours.getContour(i))) < 100 || !isContourConvex(approx))
            continue;
        if (approx.size() == 3)
        {
            labelState = "TRIANGLES";
        }
        else if (approx.size() >= 4 && approx.size() <= 6)
        {
            int vtc = approx.size();
            std::vector<double> cos;
            for (int j = 2; j < vtc+1; j++)
                cos.push_back(angle(approx[j%vtc], approx[j-2], approx[j-1]));
            std::sort(cos.begin(), cos.end());
            double mincos = cos.front();
            double maxcos = cos.back();
            if (vtc == 4 && mincos >= -0.1 && maxcos <= 0.3)
            {
                labelState = "RECTANGLE";
            }
            else if (vtc == 5 && mincos >= -0.34 && maxcos <= -0.27)
            {
                labelState = "PENTA";
            }
            else if (vtc == 6 && mincos >= -0.55 && maxcos <= -0.45){
                labelState = "HEXA";
            }
        }
        else
        {
            double area = contourArea(contours.getContour(i));
            auto r = boundingRect(contours.getContour(i));
            int radius = r.width / 2;
            if (std::abs(1 - ((double)r.width / r.height)) <= 0.2 &&
                std::abs(1 - (area / (CV_PI * std::pow(radius, 2)))) <= 0.2){
                labelState = "CIRCLE";
            }
        }
    }
}
