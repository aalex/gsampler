#ifndef _APPLICATION_H_
#define _APPLICATION_H_

class Application {
    public:
        void start();
        static Application& getInstance();

    private:
        static Application* instance_;
};

#endif // _APPLICATION_H_
