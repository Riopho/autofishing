#ifndef __SINGLETON__
#define __SINGLETON__
template <class T>
class singleton
{
    public:
        static T* Instance()
        {
            if (nullptr == _instance)
            {
                _instance = new T;
            }
            return _instance;
        }

    private:
        static T* _instance;
};
template <class T>
T* singleton<T>::_instance = nullptr;

#endif
