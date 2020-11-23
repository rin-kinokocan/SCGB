#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera{
private:
  glm::vec3 position;
  float pitch=0;
  float yaw=0;
public:
  Camera(glm::vec3 pos):position(pos){}
  glm::mat4 GetViewMat(){
    auto direction=GetDirection();
    auto res=glm::lookAt(position,position-direction,glm::vec3(0.0f,1.0f,0.0f));
    return res;
  }
  glm::vec3 GetDirection(){
    auto pitch=glm::radians(this->pitch);
    auto yaw=glm::radians(this->yaw);
    return glm::vec3(cos(yaw)*cos(pitch),sin(pitch),sin(yaw)*cos(pitch));    
  }

  void Move(float i){
    position+=GetDirection()*i;
  }
  void SetYaw(float ang){
    yaw=ang;
  }
  void SetPitch(float ang){
    pitch=ang;
  }
  void SetPosition(glm::vec3 p){
    position=p;
  }
};
