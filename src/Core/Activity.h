#pragma once

#include <list>
#include "SDLbase.h"

namespace Core{
    class Activity;
    class Control;
    class Animation;

    class Activity
    {
    friend void Core::CoreMain(Activity&);
    private:
        std::list<Control*> m_ansList;

    protected:
        void RegControl(Control&);
    public:
        virtual void OnShow(){};    //当Goto到这个活动时执行
        virtual void OnHide(){};    //当Goto出这个活动时执行

        virtual void OnDraw()=0;    //绘制活动
        //为方便起见，建议OnDraw只进行绘制，不进行逻辑动作和动画处理
        //逻辑和动画请放到OnNext中
        //该函数不能含有运行时间过长的代码

        virtual void OnEvent(const SDL_Event&){};
        //当没有控件接受消息时，回调此函数

        virtual void OnEvent(Control*,const Uint32){};
        //当有控件接收消息时，由Control调用此函数，并传入控件给的消息

        virtual void OnNext() {};   //请求下一帧，执行逻辑和动画
        //该函数不能含有运行时间过长的代码，如果需要，请开辟线程
    };
}