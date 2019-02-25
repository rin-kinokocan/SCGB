#pragma once
#include "Geometry.hpp"

namespace scgb{
  class WindowInfo{
  public:
    const std::shared_ptr<Geometry> geometry;
    const std::shared_ptr<Coordinate> coordinate;
    const std::shared_ptr<Geometry> boundary;
    const std::shared_ptr<Coordinate> origin;
    WindowInfo(Geometry* geo,Coordinate* coord,Geometry* bound=nullptr,Coordinate* ori=nullptr)
      :geometry(geo),coordinate(coord),boundary(bound),origin(ori){
    }
    WindowInfo(WindowInfo &wi,Geometry *geo,Coordinate *coord)
      :geometry(geo),coordinate(coord),boundary(wi.geometry),origin(wi.coordinate){
    }

  };  
}
