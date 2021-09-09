#ifndef BLOCKS_H
    #include "BLOCKS.h"   
#endif

#define name_of_class  PPCAT(Block, name_of_object)
#define name_of_type   PPCAT(BLKType_, name_of_object)
#define name_of_block  STRINGIZE(name_of_object)
#define name_of_init   PPCAT(name_of_class,_INIT)
#define name_of_path   (std::string(name_of_block) + "/").c_str()


#ifndef MODELSPAR_H
    #include "BLOCK_SPAR/modelSPAR.h"
#endif


namespace BLOCKS{

 class name_of_class : public BLOCK {
        private:          

            static int count;
    
            struct VARS{
                double angle = 0;   
                bool set_ref = false;         
                struct {
                    double p1 = 2.149e-023;
                    double p2 = -3.305e-019;
                    double p3 = 1.905e-015;
                    double p4 = -4.973e-012;
                    double p5 = 5.479e-009;
                    double p6 = -2.493e-006;
                    double p7 = 0.005429;
                    double p8 = 0.4611;
                }POLY;
                double refTension = 0.0f;
                double refPosition = 0.0f;
                int ZERO_02;
                int ZERO_03;
                double tension[7]   = {0.0f};
                double tension_f[7] = {0.0f};
                double force[7]   = {0.0f};
                double force_f[7]   = {0.0f};
                double error_theta[7]   = {0.0f};
                double error_f[7]   = {0.0f};
                double Af[7] = {1.0f,-2.9213f,2.8497f,-0.9282f,0.0f,0.0f,0.0f};
                double Bf[7] = {0.00002537f,0.00007611f,0.00007611f,0.00002537f,0.0f,0.0f,0.0f};
                double int_force_error[2] = {0.0f};
                double dot_force[2] = {0.0f};
                double filt_dot_force[2] = {0.0f};
                double filtro_emg1[1];
                double filtro_emg2[1];
                double position;
                double position1;
                double kmola_aesc=320000;
                double Fl = 0.0;
                double Fl1 = 0.0;
                double Flf = 0.0;
                double Xll = 0.0;
                double passo = 0.0025;
                double theta_m = 0.0f;
                double theta_l = 0.0f;
                double velocity_d = 0.0f;
                double dot_F_est = 0.0f;
                double F_est = 0.0f;
                double force_d = 0.0f;
                double angulo_l_ant = 0.0f;
                double Kv = 0.0f;
                double Bv = 0.0f;
                double y_est_emg1 = 0.0;
                double y_est_emg2 = 0.0;
                double lim_emg_1 = 0.1;
                double lim_emg_2 = 0.1;


                int factor_de_seguridad = 7000; 
                double modo = 0;
                
            }VARS;


            struct Properties{
                
            }Properties;

            virtual void showProperties(){
                ImGui::Begin("Properties",&GUI::EVENTS::showProperties,0);            

                    if(ImGui::Button("Load Model")){
                        modelSPAR(name_of_path);
                    };

                    ImGui::InputDouble( "Kv##SPAR", &(VARS.Kv), 0.0f, 100.0f, "%.3f");
                    ImGui::InputDouble( "Bv##SPAR", &(VARS.Bv), 0.0f, 100.0f, "%.3f");

                    ImGui::InputDouble( "lim_emg_1##SPAR", &(VARS.lim_emg_1), 0.0f, 1.0f, "%.3f");
                    ImGui::InputDouble( "lim_emg_2##SPAR", &(VARS.lim_emg_2), 0.0f, 1.0f, "%.3f");

                    ShowDemoWindowWidgets();
                ImGui::End();
            }

        public:
        
            struct{
               double K_1 = 0.0,K_2 = 0.0,K_3 = 0.0, K_4 = 0.0, K_5 = 0.0, KX = 0.0;
               double mu_f = 1e10, alpha_f = 2, s = 3;
               mat K1,  K2,  K3, K;
               mat C_ff2b;
               mat A_f2b;
               mat L_f2b;
               mat omega_est2k;
               mat omega_est2k1;
               mat F_est2k1_emg1;
               mat F_est2k_emg1;
               mat F_est2k1_emg2;
               mat F_est2k_emg2;
               mat A_f2;
               mat L_f2;
               mat C_ff2;
               mat X;
               field<cube> LPr_campo;
               cube Fk,Bk,Ef,Eb,Hk,P,Q,R,M,P_f,F_f,G_f,Eg_f,Ec_f,Ed_f,Ef_f,C_f,D_f,B_f,Eb_f,M_f,N_f;
               cube Pk1;
               mat R_f,Q_f,y,u1,prob,xest;

    
            }model;

            name_of_class(){
                name = name_of_block;
                TYPE = name_of_type;

                N_IN  = 7;
                
                N_OUT = 1;

                sizeBlock = ImVec2(100,200);
                
                N_IN_size  = sizeBlock.y/(float)(N_IN+1.0f);
                N_OUT_size = sizeBlock.y/(float)(N_OUT+1.0f);

                posIn.insert(posIn.begin(),N_IN+1,ImVec2(0,0));
                posOut.insert(posOut.begin(),N_OUT+1,ImVec2(0,0)); 

                arma::fmat auxOut ;
                auxOut << 0.0f;
            
                

                OUT_ARMA.insert(OUT_ARMA.begin(),N_OUT+1,auxOut); 
                IN_ARMA.insert(IN_ARMA.begin(),N_IN+1,new arma::fmat);            
            
                
                return;
                /*
                    (*IN_ARMA[1])[0]) -> EMG1
                    (*IN_ARMA[2])[0]) -> EMG2
                    (*IN_ARMA[3])[0]) -> Velocidad actual del motor, Leer de la EPOS
                */

            }

            virtual void Exec() override{
                if(SIM::EVENTS::time_index == FIRST_LAP){
                     model.K1.load(std::string(name_of_path)+"K1.dat");
                     model.K2.load(std::string(name_of_path)+"K2.dat");
                     model.K3.load(std::string(name_of_path)+"K3.dat");
                     model.C_ff2b.load(std::string(name_of_path)+"C_ff2b.dat");
                     model.A_f2b.load(std::string(name_of_path)+"A_f2b.dat");
                     model.L_f2b.load(std::string(name_of_path)+"L_f2b.dat");
                     model.omega_est2k.load(std::string(name_of_path)+"omega_est2k.dat");
                     model.omega_est2k1.load(std::string(name_of_path)+"omega_est2k1.dat");
                     model.F_est2k1_emg1.load(std::string(name_of_path)+"F_est2k1_emg1.dat");
                     model.F_est2k_emg1.load(std::string(name_of_path)+"F_est2k_emg1.dat");
                     model.F_est2k1_emg2.load(std::string(name_of_path)+"F_est2k1_emg2.dat");
                     model.F_est2k_emg2.load(std::string(name_of_path)+"F_est2k_emg2.dat");
                     model.A_f2.load(std::string(name_of_path)+"A_f2.dat");
                     model.L_f2.load(std::string(name_of_path)+"L_f2.dat");
                     model.C_ff2.load(std::string(name_of_path)+"C_ff2.dat");

                     model.Pk1.load(std::string(name_of_path)+"Pk1.dat");
                     model.R_f.load(std::string(name_of_path)+"R_f.dat");
                     model.Q_f.load(std::string(name_of_path)+"Q_f.dat");
                     model.F_f.load(std::string(name_of_path)+"F_f.dat");
                     model.G_f.load(std::string(name_of_path)+"G_f.dat");
                     model.Ef_f.load(std::string(name_of_path)+"Ef_f.dat");
                     model.Eg_f.load(std::string(name_of_path)+"Eg_f.dat");
                     model.Ec_f.load(std::string(name_of_path)+"Ec_f.dat");
                     model.Ed_f.load(std::string(name_of_path)+"Ed_f.dat");
                     model.C_f.load(std::string(name_of_path)+"C_f.dat");
                     model.D_f.load(std::string(name_of_path)+"D_f.dat");
                     model.B_f.load(std::string(name_of_path)+"B_f.dat");
                     model.Eb_f.load(std::string(name_of_path)+"Eb_f.dat");
                     model.y.load(std::string(name_of_path)+"y.dat");
                     model.u1.load(std::string(name_of_path)+"u1.dat");
                     model.M_f.load(std::string(name_of_path)+"M_f.dat");
                     model.N_f.load(std::string(name_of_path)+"N_f.dat");
                     model.prob.load(std::string(name_of_path)+"prob.dat");
                     model.xest.load(std::string(name_of_path)+"xest.dat");
                     
                     GUI::LOG_MSG = GUI::LOG_MSG + "\nTodos os .dat foram carregados \n" ;

                    //  model.LPr_campo.load(std::string(name_of_path)+"LPr_campo.dat");
                     return;
                }
                if(SIM::EVENTS::time_index == LAST_LAP){
                    return;
                }
                
                //Variables de entrada al bloque
                double emg_signal1   = as_scalar(arma::abs((*IN_ARMA[1])));
                double emg_signal2   = as_scalar(arma::abs((*IN_ARMA[2])));
                double Analog1       = as_scalar(arma::abs((*IN_ARMA[3])));
                double Analog2       = as_scalar(arma::abs((*IN_ARMA[4])));

                double theta_d       = as_scalar(arma::abs((*IN_ARMA[5])));
                int    encoder_m     = as_scalar(arma::abs((*IN_ARMA[6])));
                int    encoder_l     = as_scalar(arma::abs((*IN_ARMA[7])));
                return;

                if(!VARS.set_ref){
                    // Esperar 0.5s;
                    VARS.refTension = (Analog1 + Analog2)/2;
                    VARS.refPosition = ( VARS.POLY.p1*pow(VARS.refTension,7) + 
                                         VARS.POLY.p2*pow(VARS.refTension,6) + 
                                         VARS.POLY.p3*pow(VARS.refTension,5) + 
                                         VARS.POLY.p4*pow(VARS.refTension,4) + 
                                         VARS.POLY.p5*pow(VARS.refTension,3) + 
                                         VARS.POLY.p6*pow(VARS.refTension,2) + 
                                         VARS.POLY.p7*VARS.refTension        + 
                                         VARS.POLY.p8 )/1000;	
                    VARS.ZERO_02 =  encoder_m;
                    VARS.ZERO_02 =  encoder_l;       
                    VARS.set_ref = true;
                }
                
                VARS.theta_m =  (double(encoder_m - VARS.ZERO_02)/4096)*2*3.1416;
                VARS.theta_l =  (double(encoder_l - VARS.ZERO_03)/4096)*2*3.1416;

                VARS.tension[0] = (Analog1 + Analog2) * 0.5f;

                //---------------------------- FILTRO IIR CHEBIS. TYPE I 3th Or. Fs = 1000 Hz - Fc = 10 Hz E_inf = 0.1dB--------------------------------------//
                VARS.tension_f[0] =   - VARS.Af[1]*VARS.tension_f[1] - 
                                        VARS.Af[2]*VARS.tension_f[2] - 
                                        VARS.Af[3]*VARS.tension_f[3] - 
                                        VARS.Af[4]*VARS.tension_f[4] - 
                                        VARS.Af[5]*VARS.tension_f[5] - 
                                        VARS.Af[6]*VARS.tension_f[6] +
                                        VARS.Bf[0]*VARS.tension[0]   + 
                                        VARS.Bf[1]*VARS.tension[1]   + 
                                        VARS.Bf[2]*VARS.tension[2]   + 
                                        VARS.Bf[3]*VARS.tension[3]   + 
                                        VARS.Bf[4]*VARS.tension[4]   + 
                                        VARS.Bf[5]*VARS.tension[5]   + 
                                        VARS.Bf[6]*VARS.tension[6];
                //------------------------------------------------------------------------------------------------------------------------------------------//
                
                VARS.position  = ( VARS.POLY.p1*pow(VARS.tension_f[0],7) + 
                                   VARS.POLY.p2*pow(VARS.tension_f[0],6) + 
                                   VARS.POLY.p3*pow(VARS.tension_f[0],5) + 
                                   VARS.POLY.p4*pow(VARS.tension_f[0],4) + 
                                   VARS.POLY.p5*pow(VARS.tension_f[0],3) + 
                                   VARS.POLY.p6*pow(VARS.tension_f[0],2) + 
                                   VARS.POLY.p7*VARS.tension_f[0]        + 
                                   VARS.POLY.p8 )/1000;	
                VARS.position1  =( VARS.POLY.p1*pow(VARS.tension[0],7) + 
                                   VARS.POLY.p2*pow(VARS.tension[0],6) + 
                                   VARS.POLY.p3*pow(VARS.tension[0],5) + 
                                   VARS.POLY.p4*pow(VARS.tension[0],4) + 
                                   VARS.POLY.p5*pow(VARS.tension[0],3) + 
                                   VARS.POLY.p6*pow(VARS.tension[0],2) + 
                                   VARS.POLY.p7*VARS.tension[0]        + 
                                   VARS.POLY.p8 )/1000;	

                VARS.Fl  = -VARS.kmola_aesc * ( VARS.refPosition - VARS.position ); // N filtrada con media movil
                VARS.Fl1 = -VARS.kmola_aesc * ( VARS.refPosition - VARS.position1 ); // N sin filtro
                
                VARS.Xll = (VARS.passo*(double(encoder_m)/4096)/2) - ( VARS.refPosition - VARS.position1 );
                
                VARS.force[0]   = VARS.Fl1;
                VARS.force_f[0] = VARS.Fl1;

                // ------------------- Controladores ------------------------------------------------------------ //

                //------ Control de impedancia discreto ------------
                VARS.error_theta[0] = theta_d - VARS.theta_l;

                double omega_l = 33.33*( ( (VARS.passo*VARS.velocity_d)/(2*3.1416*2) ) - (VARS.dot_F_est/VARS.kmola_aesc) );
                model.omega_est2k1=model.A_f2b*model.omega_est2k + model.L_f2b*(omega_l - as_scalar(model.C_ff2b*model.omega_est2k));
                double omega_l_est = as_scalar(model.C_ff2b*model.omega_est2k)*1.3; 
                model.omega_est2k = model.omega_est2k1;
                omega_l=omega_l_est;

                VARS.force_d = (VARS.Kv*(theta_d - VARS.theta_l) - VARS.Bv*(omega_l)) ;  
                // VARS.force_d = 0*100 + VARS.force_d + 0*100*setpoints_force; //100

                VARS.angulo_l_ant = VARS.theta_l;
                
                VARS.error_f[0] = VARS.force_d - VARS.force_f[0];
                VARS.int_force_error[0] = VARS.int_force_error[1] + VARS.error_f[0]*double(SIM::EVENTS::Ts);

                if (VARS.velocity_d >= VARS.factor_de_seguridad){VARS.velocity_d = VARS.factor_de_seguridad;}
                else if (VARS.velocity_d <= -VARS.factor_de_seguridad){VARS.velocity_d = -VARS.factor_de_seguridad;}

                VARS.dot_force[0] =  0.9048*VARS.dot_force[1] + 100*(VARS.force_f[0] - VARS.force_f[1]); //0.369*dot
                VARS.filt_dot_force[0] = 0.9048*VARS.filt_dot_force[1] + 0.09516*VARS.dot_force[1];

                if(VARS.y_est_emg1 > VARS.lim_emg_1 || VARS.y_est_emg2 > VARS.lim_emg_2){
                    VARS.modo = 2;
                    model.K = model.K2;
                }else{
                    VARS.modo = 3;
                    model.K = model.K3;
                }

                VARS.filtro_emg1[0] = emg_signal1;
                model.F_est2k1_emg1 = model.A_f2*model.F_est2k_emg1 + model.L_f2*(VARS.filtro_emg1[0] - as_scalar(model.C_ff2*model.F_est2k_emg1));
                VARS.y_est_emg1 = as_scalar(model.C_ff2*model.F_est2k_emg1);
                model.F_est2k_emg1 = model.F_est2k1_emg1;

                VARS.filtro_emg2[0] = emg_signal2;
                model.F_est2k1_emg2 = model.A_f2*model.F_est2k_emg2 + model.L_f2*(VARS.filtro_emg2[0] - as_scalar(model.C_ff2*model.F_est2k_emg2));
                VARS.y_est_emg2 = as_scalar(model.C_ff2*model.F_est2k_emg2);
                model.F_est2k_emg2 = model.F_est2k1_emg2;

                model.X(0,0) = VARS.dot_force[0];
                model.X(1,0) = VARS.force_f[0];
                model.X(2,0) = VARS.theta_l;
                model.X(3,0) = VARS.int_force_error[0];
          
                model.KX = as_scalar(model.K*model.X);
       
                model.K_1 = as_scalar(model.K(0,0));
                model.K_2 = as_scalar(model.K(0,1));
                model.K_3 = as_scalar(model.K(0,2));
                model.K_4 = as_scalar(model.K(0,3));

                model.y = VARS.force_f[0];
                model.u1 = model.K(0,0)*model.xest(0,0) + 
                           model.K(0,1)*model.xest(1,0) + 
                           model.K(0,2)*model.X(2,0)    + 
                           model.K(0,3)*model.X(3,0);

                cube x_cube(2,1,1);
                mat xest_act = model.xest;
                model.LPr_campo = rkf_slsm(model.Pk1, model.R_f, model.Q_f, model.F_f, model.G_f, model.Ef_f, model.Eg_f, model.Ec_f, model.Ed_f, model.C_f, model.D_f, model.B_f, model.Eb_f, model.xest, model.y, model.u1, model.M_f, model.N_f, model.mu_f, model.alpha_f, model.s, model.prob, VARS.modo);

                x_cube = model.LPr_campo(1,0);
                model.xest = x_cube.slice(0);   

                VARS.dot_F_est = as_scalar(model.xest(0,0));
                VARS.F_est = as_scalar(model.xest(1,0));

                VARS.velocity_d = as_scalar(model.u1);

                OUT_ARMA[1] = VARS.velocity_d;

                VARS.force[6] = VARS.force[5];
                VARS.force[5] = VARS.force[4];
                VARS.force[4] = VARS.force[3];
                VARS.force[3] = VARS.force[2];
                VARS.force[2] = VARS.force[1];
                VARS.force[1] = VARS.force[0];
                VARS.force_f[6] = VARS.force_f[5];
                VARS.force_f[5] = VARS.force_f[4];
                VARS.force_f[4] = VARS.force_f[3];
                VARS.force_f[3] = VARS.force_f[2];
                VARS.force_f[2] = VARS.force_f[1];
                VARS.force_f[1] = VARS.force_f[0];
                VARS.tension[6] = VARS.tension[5];
                VARS.tension[5] = VARS.tension[4];
                VARS.tension[4] = VARS.tension[3];
                VARS.tension[3] = VARS.tension[2];
                VARS.tension[2] = VARS.tension[1];
                VARS.tension[1] = VARS.tension[0];
                VARS.tension_f[6] = VARS.tension_f[5];
                VARS.tension_f[5] = VARS.tension_f[4];
                VARS.tension_f[4] = VARS.tension_f[3];
                VARS.tension_f[3] = VARS.tension_f[2];
                VARS.tension_f[2] = VARS.tension_f[1];
                VARS.tension_f[1] = VARS.tension_f[0];
                VARS.error_f[6] = VARS.error_f[5];
                VARS.error_f[5] = VARS.error_f[4];
                VARS.error_f[4] = VARS.error_f[3];
                VARS.error_f[3] = VARS.error_f[2];
                VARS.error_f[2] = VARS.error_f[1];
                VARS.error_f[1] = VARS.error_f[0];
                VARS.error_theta[2] = VARS.error_theta[1];
                VARS.error_theta[1] = VARS.error_theta[0];


                VARS.dot_force[1] = VARS.dot_force[0];
                VARS.filt_dot_force[1] = VARS.filt_dot_force[0];

                VARS.int_force_error[1] = VARS.int_force_error[0];
            }
            
            virtual BLOCK * Create(){
                return new name_of_class();
            }
            
            virtual void DrawADD(){
                
                //draw_list->AddCircleFilled(LOCAL.posBlock_Global.Min,5,GUI::getColorU32(GUICol_Amarillo));
                ImGui::End();

                ImGui::Begin((" "+name).c_str(),&GUI::EVENTS::showBlocks,0);       
                ImDrawList* draw_list = ImGui::GetWindowDrawList();
                ImGuiWindow* windowCur = ImGui::GetCurrentWindow();          
                ImVec2 cur = windowCur->DC.CursorPos;   
                
                // static ImVec2 dim1 = GUI::Texture[GUITex_SPAR1].dimensions * 0.5;
                // ImGui::SetCursorPos(windowCur->Size - ImVec2(windowCur->Size.x/2.f - dim1.x/2.0f + 96,20.0f + windowCur->Size.y/2.f + dim1.y/2.0f));
                // ImGui::Image((void*)GUI::Texture[GUITex_SPAR1].texture,dim1);
                
                
                cur.x += windowCur->InnerRect.GetWidth()/2.0;
                cur.y += (windowCur->InnerRect.GetHeight() / 2.0);

              

                static ImVec2 dim1 = GUI::Texture[GUITex_SPAR1].dimensions * 0.5f;
                ImVec2 offset = ImVec2(50,1.6);
                ImageRotatedPivoted((void*)GUI::Texture[GUITex_SPAR1].texture, cur  + ImVec2(18,-46) , dim1, VARS.angle, offset); 

                static ImVec2 dim2 = GUI::Texture[GUITex_SPAR2].dimensions * 0.5;
                ImGui::SetCursorPos(windowCur->Size - ImVec2(windowCur->Size.x/2.f + dim2.x/2.0f,windowCur->Size.y/2.f + dim2.y/2.0f));
                ImGui::Image((void*)GUI::Texture[GUITex_SPAR2].texture,dim2);

                

                ImGui::End();
                ImGui::Begin("Block logic",&GUI::EVENTS::showBlocks,0);     
            }    
            
    };

    void name_of_init(){
        ALL_BLOCKS_GUI[name_of_type] = new name_of_class();
        GUI::LOG_MSG =GUI::LOG_MSG + "\n   " + STRINGIZE(name_of_class)   + ": Cargado " ;
    }
 
 

};
