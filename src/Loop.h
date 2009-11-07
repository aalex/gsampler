#ifndef _LOOP_H_
#define _LOOP_H_

#include <string>

class Loop 
{
    public:
        Loop(const std::string &name) : name_(name) {}
        friend std::ostream& operator<<( std::ostream& o, const Loop& s );
        std::string name() const { return name_; }
        static void recordLoop(void *data);
        static bool isRecording() { return recording_; }
        static void stopRecording() { stopped_ = true; }
        
    private:
        static bool recording_;
        static bool stopped_;
        const std::string name_;
};

#endif // _LOOP_H_
