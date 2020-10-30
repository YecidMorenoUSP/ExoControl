#define BLOCKS_H
#define MAX_NUM_BLOCKS 100

enum TypeBlock_{
    BLKType_Default,
    BLKType_Sum,
    BLKType_Pow,
    BLKType_COUNT
};

namespace BLOCKS{

    ImGuiID getIDBLOCK(const char * str){
        ImGuiID id = ImHashStr(str);
        return id;
    }

    template <typename T>
    void runBlock(T arg){
        arg->Exec();
    }



    void Init();

    namespace EVENTS{
        ImGuiID ActiveBlock;
    }
    class BLOCK {
        public:
            ImGuiID ID;
            TypeBlock_ TYPE;
            int indexType = 0;

            std::string name = "DefaultBlock";
            std::string helpText;

            bool ENABLED = false;
            bool ACTIVE  = false;

            ImVec2 posBlock  = ImVec2(250,250);
            ImVec2 sizeBlock = ImVec2(100,50);
            
            struct Properties;
        

        virtual void Draw(){};
        virtual void Exec(){};
        virtual BLOCK * Create(){return NULL;};
     
        void Draw2();
    };

    
    std::vector<BLOCK*> ALL_BLOCKS_GUI(BLKType_COUNT,NULL);

   
    void AddBLOCK(TypeBlock_ TypeBlock);
    void DROOPBLOCK(ImGuiID ID);


}