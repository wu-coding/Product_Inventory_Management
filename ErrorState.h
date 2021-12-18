#ifndef ERRORSTATE_H
#define ERRORSTATE_H
namespace AMA {
    class ErrorState {
        
        char* errorStore;

        public:
        explicit ErrorState(const char* errorMessage = nullptr);
        virtual ~ErrorState();
        void clear();
        bool isClear() const;
        void message(const char* str);
        const char* message()const;	
        friend std::ostream& operator<<(std::ostream& os, const ErrorState& passError);

        ErrorState(const ErrorState& em) = delete;
        ErrorState& operator=(const ErrorState& em) = delete;
    };
}
#endif