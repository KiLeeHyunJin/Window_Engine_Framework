

using VoidPtr = void(*)();
//using RenderPtr = void(*)(HDC);

//
//template <typename ReturnType, typename... Args>
//class FunctionPtr
//{
//public:
//    using FuncPtr = ReturnType(*)(Args...);  // �Ϲ� �Լ� ������
//
//    FunctionPtr() : funcPtr(nullptr)            {}
//    FunctionPtr(FuncPtr func) : funcPtr(func)  {}
//
//    void SetFunction(FuncPtr func)         {   funcPtr = func; }
//
//    ReturnType Call(Args... args) const 
//    {
//        if (funcPtr != nullptr)
//        {
//            return funcPtr(std::forward<Args>(args)...);
//        }
//
//        assert(0);
//        //std::cout << "No function assigned!" << std::endl;
//        return ReturnType();
//    }
//
//private:
//    FuncPtr funcPtr;  // �Լ� ������ ���� (���� �Ҵ� ����)
//};
