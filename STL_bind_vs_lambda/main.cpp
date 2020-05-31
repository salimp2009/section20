#include <iostream>

struct Event
{
    
    void EventDispatch(Event& other)
    {
        std::cout<<"EventcallBack: "<<other.name<<'\n';
    }
    
    std::string name{"KeyEvent"};
};

class Window
{
public:
  Window()=default;  
  Window(int w, int h): mWidth{w}, mHeight{h} {}
  
  void init() {
      mWidth=1280;
      mHeight=640;
  }
  
  int getWidth() const {return mWidth;}
  int getHeight() const {return mHeight;}
  
  void Eventcallback(std::function<void(Event& e)>)
  {
      
      Event().EventDispatch(e);

  
private:
  int mWidth;
  int mHeight;
};

class Application
{
public:
    Application() 
    {
        m_Window->Eventcallback(Application::onEvent(e));
    }
    
    void onEvent(Event& e)
    {
        Event a_e;
        a_e.EventDispatch(e);
    }
    
    Window& getWindow() const { return m_Window; }
    
private:
 Window* m_Window;
    
};

int main()
{

    return 0;
}
