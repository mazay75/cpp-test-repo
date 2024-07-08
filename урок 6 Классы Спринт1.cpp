#include <iostream>

using namespace std;

/* Допишите класс в соответствии с требованиями задания*/
class TV {
    bool statusTV_=0; //состояние телевизора (если 0, то выключен, если 1, то включен)
    int current_channel_=1;// текущий канал. При первом включении==1




public:
    // Включает телевизор.
    void TurnOn() {
        if (statusTV_==0) {statusTV_=1;}
    }

    // Выключает телевизор
    void TurnOff() {
       if (statusTV_==1) {statusTV_=0;}
    }

    // Возвращает true, если телевизор включен и false, если телевизор выключен
    bool IsTurnedOn() {
       if (statusTV_==1) {return true;}
        return false;
    }

    // Возвращает номер текущего канала, либо 0, если телевизор был выключен.
    // Номер канала не сбрасывается при выключении и повторном включении.
    // При первом включении телевизор показывает канал №1.
    int GetCurrentChannel() {
      if (!IsTurnedOn())  {return 0;}
        return current_channel_;
    }

    // Выбирает канал с указанным номером. Номер канала должен быть в диапазоне [1..99].
    // Если указан недопустимый номер канала, либо телевизор выключен, возвращает false и не меняет
    // текущий канал. В противном случае возвращает true.
    bool SelectChannel(int channel) {
      //  current_channel_=channel;
       if (channel >= 1 && channel <=99 && IsTurnedOn()) {current_channel_=channel; return true;}
        return false;
    }
};

int main() {
    TV tv;
    cout << tv.IsTurnedOn() << ", channel:"s << tv.GetCurrentChannel() << endl;
    tv.TurnOn();
    cout << tv.IsTurnedOn() << ", channel: "s << tv.GetCurrentChannel() << endl;
    tv.SelectChannel(25);
    cout << tv.IsTurnedOn() << ", channel: "s << tv.GetCurrentChannel() << endl;
    tv.TurnOff();
    cout << tv.IsTurnedOn() << ", channel: "s << tv.GetCurrentChannel() << endl;
}