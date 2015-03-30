#include "Activity.h"
#include "Timer.h"
#include "Sound.h"
#include "Globals.h"
#include "Control.h"
#include "../Debug.h"

using namespace Core;
using namespace std;

Activity* nowFocus;
Activity* nextFocus;


namespace Core{

RndPtr pRnd;

void Goto(Activity* a)
{
    if(a != nowFocus) nextFocus = a;
}

//void ActivityDrawProc() //活动刷新一次处理
//{
    /*  取消活动间跳转动画功能   *
    if(isGotoing){  //如果正在跳转
        bool lastFinished = false;
        bool nowFinished = false;

        if(lastFocus != nullptr && !lastFinished) {
            if(lastFocus -> GetAnimationOnHide() != nullptr){
                lastFocus -> GetAnimationOnHide() -> OnNext();   //绘制上个活动
                if(lastFocus -> GetAnimationOnHide() -> Finished()) lastFinished = true;
            }else lastFinished = true;
            lastFocus -> OnDraw();
        }else lastFinished = true;

        if(nowFocus != nullptr && !nowFinished) {
            if(nowFocus -> GetAnimationOnShow() != nullptr){
                nowFocus -> GetAnimationOnShow() -> OnNext();   //绘制下个活动
                if(nowFocus -> GetAnimationOnShow() -> Finished()) nowFinished = true;
            }else nowFinished = true;
            nowFocus -> OnDraw();
        }else nowFinished = true;

        if(lastFinished && nowFinished) isGotoing = false;
    }

    //两个动画结束后关闭跳转状态
    else{
        */
        //nowFocus -> OnNext();
        //nowFocus -> OnDraw();
    //}
//}

void CoreMain(Activity& start)
{
    nowFocus = &start;
    nowFocus -> OnShow();
    /* 主循环部分 */
    SDL_Event e;
    Timer FPSKiller;
    while(1){

        /**** 如果有Goto消息则执行Goto ****/
        if(nextFocus != nullptr){
                nowFocus -> OnHide();
                nextFocus -> OnShow();
                nowFocus = nextFocus;
                nextFocus = nullptr;
        }

        /**** 处理当前帧所有的事件 ****/
        while(SDL_PollEvent(&e)){
            if (e.type == SDL_QUIT) {   //如果是退出
                nowFocus -> OnHide();
                return;
            }
            else {
                if(!(nowFocus -> m_ansList.empty()))
                    for(auto p = nowFocus -> m_ansList.begin();p != nowFocus -> m_ansList.end();++p)  //遍历控件表
                    {
                        if((*p) -> OnEvent(e,*nowFocus)) continue;  //发现有控件接受该信息后返回
                    }
                    nowFocus -> OnEvent(e);    //无控件接受消息，发送消息给活动的OnEvent()
            }
        }

        /**** 绘制 ****/
        SDL_SetRenderDrawColor(pRnd,0x00,0x00,0x00,0xFF);
        SDL_RenderClear(pRnd);
        nowFocus -> OnNext();
        nowFocus -> OnDraw();
        SDL_RenderPresent(pRnd);

        FPSKiller.WaitTimer(1000/FPS);   //FPS限制
        FPSKiller.Reset();
    }
}

void CoreInit(const string& title,const bool fullScreen,const int w,const int h)
{
    SDL_Init(SDL_INIT_AUDIO |
                SDL_INIT_EVENTS|
                SDL_INIT_VIDEO |
                SDL_INIT_TIMER);
    IMG_Init(IMG_INIT_PNG);
    TTF_Init();

    pRnd.Create(title,fullScreen,w,h);

    Sound::Init();

    nowFocus = nullptr;
    nextFocus = nullptr;
}

}

void Core::CoreQuit()
{
    pRnd.Destory();
    TTF_Quit();
    IMG_Quit();
    Sound::Quit();
    ResFile::Quit();
    cout<<"SDL_Quit() Started."<<endl;
    SDL_Quit();
    cout<<"SDL_Quited"<<endl;
}
