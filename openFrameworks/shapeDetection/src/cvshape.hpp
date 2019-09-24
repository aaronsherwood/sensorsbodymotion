//
//  cvshape.hpp
//  myDelightfulSketch
//
//  Created by aaron sherwood on 9/24/19.
//
//

#ifndef cvshape_hpp
#define cvshape_hpp

#include <stdio.h>

#include "ofMain.h"
#include "ofxCv.h"

using namespace ofxCv;
using namespace cv;

class CVShape{
public:
    Mat gray;
    Mat bw;
    Mat dst;
    ofPixels pixelsRep;
    string labelState;
//    vector<vector<Point2f> > contours;
    ContourFinder contours;
    vector<Point2f> approx;
    
    static double angle(Point2f pt1, Point2f pt2, Point2f pt0)
    {
        double dx1 = pt1.x - pt0.x;
        double dy1 = pt1.y - pt0.y;
        double dx2 = pt2.x - pt0.x;
        double dy2 = pt2.y - pt0.y;
        return (dx1*dx2 + dy1*dy2)/sqrt((dx1*dx1 + dy1*dy1)*(dx2*dx2 + dy2*dy2) + 1e-10);
    }
    
    string getLabel();
    void update(ofPixels pix);
    
};

#endif /* cvshape_hpp */


