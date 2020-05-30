
class TestContainer{
private:
  std::vector<AATextData> textures;
  TestContainer(){
    textures.pushup(AATextData("filename1.txt"));
    textures.pushup(AATextData("filename2.txt"));
  }
public:
};

class TestTitleScene:public BaseView{
private:
  Menu menu;
  AAtext logo;// comes from low level API
public:
  void Draw(){
    logo.Draw();
    menu.Draw();
    cursor.Draw();
  }
  void AssignController(BaseController* controller){
    this->controller=controller;
    menu.AssignController(controller);
  }
  TestTitleScene():logo("logofile.txt"){
    menu.addOption("Start");
    menu.addOption("Exit");
  }
};

int main(){
  Boundary boundary(10,10,20,20);
  AAtextData dat("filename2.txt");
  AAtext aa("filename.txt",boundary);
  AAtext aa2(dat);
  aa.Draw(0,0,boundary);
  aa2.Draw(0,0);
  aa.Draw(10,0,nullptr);
  return 0;
}
