#pragma once
namespace ACGCross{

namespace Galgame{

class GameMenuBtn:public Core::Control
{
private:
    Core::Texture m_btn;

    bool m_visible_l;

    int m_x,
         m_y,
         m_stat,
         m_showstat;

    Core::Timer m_timer;

    SDL_Rect m_rect;

public:
    GameMenuBtn(){};
    void OnNext();
    void OnDraw();
    void Init(const std::string& menuBtn);  //必须先Init，否则可能出错
    void Destory();
    void Hide();
    void Show();
    void SetPos(int x,int y);
    bool GetVisible(){return m_visible_l;}
    bool OnEvent (const SDL_Event& e,Core::Activity&);
};

}
}
