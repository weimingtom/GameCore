#include <string>
#include <vector>
#include <list>
#include "Core.h"

namespace ACGCross {
namespace Galgame {

class TextBox
{
    enum Stat{
        NOEVENT,    //����
        TXT_SHOWING,    //������ʾ��
        TXT_KILLING,    //����������
        TXT_STOPSPEAK,  //ǿ����ʾ������

        RECT_HIDING,    //����ȫ������
        RECT_SHOWING,   //����ȫ����ʾ
        RECT_HIDE   ////ȫ������
    };
    public:
        TextBox();
        ~TextBox();

        //����ӿ�
        void SetEffectSpeed(int time);
        void SetColor(int r,int g,int b);
        void SetFont(Core::Font&);
        void SetHeight(int h);  //������ͬʱ���ſ���
        //������;�в��룬���Ǳ����Ȼ��������С��ÿһ��ֻ������ͬ��С�����������̹���

        //�ı��ӿ�
        void Br();  //����
        void Clear();
        void AddText(const std::wstring&);  //׷���ı�
        void AddPic(const std::string& file,const int fps,const int time);   //׷�ӱ���ͼ
        //�ļ������ļ��а�����֡�������򣩣�ms/֡ ��λ�Ĳ����ٶ�

        //ϵͳ�ӿ�
        void OnNext();
        void OnDraw();
        inline bool Finished()
        {return m_stat == NOEVENT || m_stat == RECT_HIDE;};
        void Init();
        void Destroy();

        //�Ի��ӿ�
        void SetSpeed(int time);
        void StopSpeak();

        //���ֿ�ӿ�
        void SetRect(int x,int y,int w,int h);
        void Hide();
        void Show();
        Stat GetStatus(){return m_stat;};

        //ǿ���������ֽӿڣ�û�ж���Ч��
        std::list<Core::Texture>::iterator ForceAddText(const std::wstring&);
        std::list<Core::Texture>::iterator ForceAddPic(const std::string& file,const int fps,const int time);
        //���ص��������õ�����ָ�������ı��ĵ�һ���ֵĵ�����

        std::list<Core::Texture>::iterator GetTextEnd()
        {return m_text.end();}

        void ForceClear();  //ǿ��ɾ������



    protected:
    private:
        std::vector<int> m_lineWord;    //ÿ��������
        std::list<Core::Texture> m_text;  //����
        Core::Font* m_font;  //����
        int m_r,m_g,m_b,    //��ɫ
            m_fpsSpeed, //FPS/�� �ٶ�
            m_fpsEffectSpeed;   //FPS��Ч�ٶ�
        Stat m_stat; //״̬
        Uint32 m_nowFps;   //FPS������
        SDL_Rect m_rect;    //���ֿ�λ��
        int m_word_h;  //���ֳ���
        std::list<Core::Texture>::iterator m_showing_word; //��ʾ�е�����
        Uint32 m_fpsCounter; //FPS�ļ����ؼ���

        int m_linePos;  //�����Ѿ���ʾ�������rect��������
        int m_heiPos;  //�����Ѿ���ʾ�������rect��������

        struct TextPicInfo{
            std::list<Core::Texture>::iterator tex;
            int fpsCount;
            int nowFps;
            int fpsCounter;
            int fpsTime;
        };
        std::list<TextPicInfo> m_tpiv;
};

} // namespace Galgame
} // namespace ACGCross