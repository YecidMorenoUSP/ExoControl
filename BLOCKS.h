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


    class BLOCK {
        public:
            ImGuiID ID;
            TypeBlock_ TYPE;
            int indexType = 0;

            std::string name = "DefaultBlock";
            std::string helpText;

            bool ENABLED = false;
            bool ACTIVE  = false;

            ImVec2 posBlock  = ImVec2(10,10);
            ImVec2 sizeBlock = ImVec2(100,50);
            
            struct Properties;

            int N_IN;
            int N_OUT;

            float N_IN_size ;
            float N_OUT_size;
        

        virtual void Draw(){};
        virtual void Exec(){};
        virtual BLOCK * Create(){return NULL;};
     
        void Draw2();
    };

    namespace EVENTS{
        ImGuiID ActiveBlock;
        BLOCK * LinePoints[2] = {NULL,NULL};
        int creatingLine = 0;
        ImVec2 newLinePosOUT;
        ImVec2 newLinePosIN;
    }
    std::vector<BLOCK*> ALL_BLOCKS_GUI(BLKType_COUNT,NULL);

   
    void AddBLOCK(TypeBlock_ TypeBlock);
    void DROOPBLOCK(ImGuiID ID);


}