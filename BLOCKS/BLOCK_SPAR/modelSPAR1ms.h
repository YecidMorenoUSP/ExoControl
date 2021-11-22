#ifndef MODELSPAR_H
    #define MODELSPAR_H  

#include <direct.h>

void modelSPAR(std::string path){
    _mkdir(path.c_str());
    std::cout<<"Iniciado";
    mat LKP,L,K,X,Cref,I3,Kref,Mnum;
    mat L_kalman,C_kalman,Y_kalman;
    double alpha,mu,beta; 
    int Nk=15000/4;

    
    cube Fk(4,4,3);
    
    mat Fk_1;
    Fk_1.zeros(4,4);

    Fk_1(0,0) =  0.016313941052918;
    Fk_1(1,0) =  0.000488510367508;
    Fk_1(2,0) = -0.000000050886497;
    Fk_1(3,0) = -0.000000752989061;

    Fk_1(0,1) = -4.318501501849671;
    Fk_1(1,1) = 0.993343469026164;
    Fk_1(2,1) = 0.000000693388643;
    Fk_1(3,1) = -0.001994502043676;

    Fk_1(0,2) = 0;
    Fk_1(1,2) = 0;
    Fk_1(2,2) = 1;
    Fk_1(3,2) = 0;

    Fk_1(0,3) = 0;
    Fk_1(1,3) = 0;
    Fk_1(2,3) = 0;
    Fk_1(3,3) = 1;


    Fk.slice(0) = Fk_1;

    mat Fk_2;
    Fk_2.zeros(4,4);
    
    Fk_2(0,0) =  0.799430491833627 ;
    Fk_2(1,0) =  0.001796532507281;
    Fk_2(2,0) = -0.000000187138803;
    Fk_2(3,0) = -0.000001863399284;

    Fk_2(0,1) = -12.282984664612931;
    Fk_2(1,1) =  0.987259843763329;
    Fk_2(2,1) =  0.000001327099608;
    Fk_2(3,1) = -0.001991352850606;

    Fk_2(0,2) = 0;
    Fk_2(1,2) = 0;
    Fk_2(2,2) = 1;
    Fk_2(3,2) = 0;

    Fk_2(0,3) = 0;
    Fk_2(1,3) = 0;
    Fk_2(2,3) = 0;
    Fk_2(3,3) = 1;

    Fk.slice(1) = Fk_2;


    mat Fk_3;
    Fk_3.zeros(4,4);
    
    Fk_3(0,0) =   0.663101913644911;
    Fk_3(1,0) =   0.001650422455473;
    Fk_3(2,0) =  -0.000000171919006;
    Fk_3(3,0) =  -0.000001762677493;

    Fk_3(0,1) = -25.242691627974363;
    Fk_3(1,1) =  0.973040402935565;
    Fk_3(2,1) =  0.000002808291361;
    Fk_3(3,1) = -0.001981441702912;

    Fk_3(0,2) = 0;
    Fk_3(1,2) = 0;
    Fk_3(2,2) = 1;
    Fk_3(3,2) = 0;

    Fk_3(0,3) = 0;
    Fk_3(1,3) = 0;
    Fk_3(2,3) = 0;
    Fk_3(3,3) = 1;

    Fk.slice(2) = Fk_3;

    
    cube Bk(4,1,3);
    
    mat Bk_1,Bk_2,Bk_3;
    
    Bk_1.zeros(4,1);
    Bk_1(0,0) = 62.199631569473361 ;
    Bk_1(1,0) =  0.095874407806971;
    Bk_1(2,0) =  0.000003275994444;
    Bk_1(3,0) = -0.000079187388866;
    Bk.slice(0) = Bk_1;
    
    Bk_2.zeros(4,1);
    Bk_2(0,0) = 11.957587926943695;
    Bk_2(1,0) = 0.012402648262021;
    Bk_2(2,0) = 0.000011970969397;
    Bk_2(3,0) = -0.000008418071993;
    Bk.slice(1) = Bk_2;
    

    Bk_3.zeros(4,1);
    Bk_3(0,0) =19.731297050016813 ;
    Bk_3(1,0) =0.021073339795413 ;
    Bk_3(2,0) =0.000011067772362 ;
    Bk_3(3,0) = -0.000014506348134;
    Bk.slice(2) = Bk_3;


    cube Ef(1,4,3);
    mat Ef_1, Ef_2, Ef_3;
    
    Ef_1.zeros(1,4);
    Ef_1(0,0) = -0.3;     // derivada fuerza
    Ef_1(0,1) = -99.2;    // fuerza     
    Ef_1(0,2) = 0;        // theta carga
    Ef_1(0,3) = 2616;     // integral error fuerza
    Ef.slice(0) = Ef_1;


    
    Ef_2.zeros(1,4);
    Ef_2(0,0) = -0.6*0.01*100;      // derivada fuerza
    Ef_2(0,1) = -99.2*5;            // fuerza  
    Ef_2(0,2) = 108*1.2;            // theta carga
    Ef_2(0,3) = 6673*0.5*2*0.8*0.9; //  integral error fuerza
    Ef.slice(1) = Ef_2;

    Ef_3.zeros(1,4);
    Ef_3(0,0) = -0.2*5*4;//4// 0.2*5*2 mejor  //-0.2*5*0.01 full // derivada fuerza -0.6 *0.1   5 10
    Ef_3(0,1) = -31.8*15;//18 //20  //26           // fuerza  2.3 2.7   6 10 8   7 8  4  6 10
    Ef_3(0,2) = 57*0.1*5*4*16;//20 //16      //0.5       // theta carga    2.  2.5 0.7  0.3     -57*0.1 kv grande //hay que probar un punto intermedio aqui  vamos aqui -57*0.1*5*  16  32 64
    Ef_3(0,3) = 6673*1;//0.5 //1  //0.9       //  integral error fuerza 6673*0.5  0.4  0.35 0.4 0.3 0.1  0.1 0.7
    Ef.slice(2) = Ef_3;
   

    cube Eb(1,1,3);
    mat Eb_1, Eb_2, Eb_3;
    
    Eb_1.zeros(1,1);
    Eb_1(0,0) =  -118.6592140461666;
    Eb.slice(0) = Eb_1;

    Eb_2.zeros(1,1);
    Eb_2(0,0) =  -59.329607023083298;
    Eb.slice(1) = Eb_2;

    Eb_3.zeros(1,1);
    Eb_3(0,0) =  -47.463685618466641*0.6*5;//4 //-59.329607023083298;//0.8   1.2  2
    Eb.slice(2) = Eb_3;

    
    cube Hk(4,1,3);
    mat Hk_1,Hk_2,Hk_3;

    Hk_1.zeros(4,1);
    Hk_1(0,0) = -1187.7;
    Hk_1(1,0) = -10.3;    
    Hk_1(2,0) = 1e5;
    Hk_1(3,0) = 10;
    Hk_1 = Hk_1*0.0001;
    Hk.slice(0) = Hk_1;



     Hk_2.zeros(4,1);
    Hk_2(0,0) = -0.0594;
    Hk_2(1,0) = -0.0005;
    Hk_2(2,0) = 5;
    Hk_2(3,0) = 0.0005;
    Hk.slice(1) = Hk_2;

    Hk_3.zeros(4,1);
    Hk_3(0,0) = -0.0594;
    Hk_3(1,0) = -0.0005;
    Hk_3(2,0) = 5;
    Hk_3(3,0) = 0.0005;
    Hk.slice(2) = Hk_3;


    cube P(16,Nk,3);
    mat P_1, P_slice0_mat, P_2, P_slice1_mat, P_3, P_slice2_mat;
    P_slice0_mat.zeros(16,Nk);
    P_slice1_mat.zeros(16,Nk);
    P_slice2_mat.zeros(16,Nk);

    P_1.zeros(16,1);
    P_1(0,0) = 1e10;
    P_1(1,0) = 0;
    P_1(2,0) = 0;
    P_1(3,0) = 0;
    

    P_1(4,0) = 0;
    P_1(5,0) = 1e10;
    P_1(6,0) = 0;
    P_1(7,0) = 0;
   
    
    P_1(8,0) = 0;
    P_1(9,0) = 0;
    P_1(10,0) = 1e10;
    P_1(11,0) = 0;
    
    
    P_1(12,0) = 0;
    P_1(13,0) = 0;
    P_1(14,0) = 0;
    P_1(15,0) = 1e10;
    

    
    
    P_slice0_mat.submat(0,0,15,0) = P_1;
    P.slice(0) = P_slice0_mat; 
    //submat( first_row, first_col, last_row, last_col )
    
    P_2.zeros(16,1);
 
    P_2(0,0) = 1e10;
    P_2(1,0) = 0;
    P_2(2,0) = 0;
    P_2(3,0) = 0;
    

    P_2(4,0) = 0;
    P_2(5,0) = 1e10;
    P_2(6,0) = 0;
    P_2(7,0) = 0;
   
    
    P_2(8,0) = 0;
    P_2(9,0) = 0;
    P_2(10,0) = 1e10;
    P_2(11,0) = 0;
    
    
    P_2(12,0) = 0;
    P_2(13,0) = 0;
    P_2(14,0) = 0;
    P_2(15,0) = 1e10;
    



    P_slice1_mat.submat(0,0,15,0) = P_2;
    P.slice(1) = P_slice1_mat; 

    P_3.zeros(16,1);


 
    P_3(0,0) = 1e10;
    P_3(1,0) = 0;
    P_3(2,0) = 0;
    P_3(3,0) = 0;
    

    P_3(4,0) = 0;
    P_3(5,0) = 1e10;
    P_3(6,0) = 0;
    P_3(7,0) = 0;
   
    
    P_3(8,0) = 0;
    P_3(9,0) = 0;
    P_3(10,0) = 1e10;
    P_3(11,0) = 0;
    
    
    P_3(12,0) = 0;
    P_3(13,0) = 0;
    P_3(14,0) = 0;
    P_3(15,0) = 1e10;
    


    
    P_slice2_mat.submat(0,0,15,0) = P_3;
    P.slice(2) = P_slice2_mat;


    
    mat columnas,filas,matrices;

    cube Q(4,4,3);
    mat Q_1,Q_2,Q_3;

    Q_1.eye(4,4);
    Q.slice(0) = Q_1*1e9;

    Q_2.eye(4,4);
    Q.slice(1) = Q_2*1e9;
    
    Q_3.eye(4,4);
    Q.slice(2) = Q_3*1e9;

    
    cube R(1,1,3);
    mat R_1,R_2,R_3;

    R_1.zeros(1,1);
    R_1(0,0) = 1*0.1f;
    R.slice(0) = R_1;

    R_2.zeros(1,1);
    R_2(0,0) = 1*0.1f;
    R.slice(1) = R_2;

    R_3.zeros(1,1);
    R_3(0,0) = 1;
    R.slice(2) = R_3;
    


    cube M(1,4,3);
    mat M_1,M_2,M_3;

    M_1.zeros(1,4);
    M.slice(0) = M_1;

    M_2.zeros(1,4);
    M.slice(1) = M_2;

    M_3.zeros(1,4);
    M.slice(2) = M_3;
    
    int s = 3;

    mat prob; 
    prob.zeros(3,3);
    

    prob(0,0) = 0.99;   prob(0,1) = 0.01;   prob(0,2) = 0.000; // 
    prob(1,0) = 0.00;   prob(1,1) = 0.60;   prob(1,2) = 0.400; // 
    prob(2,0) = 0.00;   prob(2,1) = 0.40;   prob(2,2) = 0.600; // 


   

    L.zeros(4,4);
    K.zeros(1,4);
    
    X.zeros(4,1);



    ///////////////  MARKOVIANO //////////////////
    
    
      field<cube> RLQR(3,1);
      cube RLQR_Pr(16,Nk,3);
      cube RLQR_Kr(4,Nk,3);
      cube RLQR_Lr(16,Nk,3);
      
      mat RLQR_Pr_mat_modo1, RLQR_Pr_mat_modo2, RLQR_Pr_mat_modo3;
      mat RLQR_Kr_mat_modo1, RLQR_Kr_mat_modo2, RLQR_Kr_mat_modo3;
      mat RLQR_Lr_mat_modo1, RLQR_Lr_mat_modo2, RLQR_Lr_mat_modo3;
      
      RLQR_Pr_mat_modo1.zeros(16,Nk);
      RLQR_Pr_mat_modo2.zeros(16,Nk);
      RLQR_Pr_mat_modo3.zeros(16,Nk);
      
      RLQR_Kr_mat_modo1.zeros(4,Nk);
      RLQR_Kr_mat_modo2.zeros(4,Nk);
      RLQR_Kr_mat_modo3.zeros(4,Nk);

      RLQR_Lr_mat_modo1.zeros(16,Nk);
      RLQR_Lr_mat_modo2.zeros(16,Nk);
      RLQR_Lr_mat_modo3.zeros(16,Nk);


      RLQR = rlqr_slsm(Fk, Ef, Bk, Eb, Hk, P, Q, R, M, s, prob, Nk);
      
      RLQR_Pr = RLQR(0,0);
      RLQR_Kr = RLQR(1,0);
      RLQR_Lr = RLQR(2,0);

      RLQR_Pr_mat_modo1 = RLQR_Pr.slice(0);
      RLQR_Pr_mat_modo1.save(path+"Pr_modo1.dat", arma_ascii);

      RLQR_Pr_mat_modo2 = RLQR_Pr.slice(1);
      RLQR_Pr_mat_modo2.save(path+"Pr_modo2.dat", arma_ascii);

      RLQR_Pr_mat_modo3 = RLQR_Pr.slice(2);
      RLQR_Pr_mat_modo3.save(path+"Pr_modo3.dat", arma_ascii);



      RLQR_Kr_mat_modo1 = RLQR_Kr.slice(0);
      RLQR_Kr_mat_modo1.save(path+"Kr_modo1.dat", arma_ascii);

      RLQR_Kr_mat_modo2 = RLQR_Kr.slice(1);
      RLQR_Kr_mat_modo2.save(path+"Kr_modo2.dat", arma_ascii);

      RLQR_Kr_mat_modo3 = RLQR_Kr.slice(2);
      RLQR_Kr_mat_modo3.save(path+"Kr_modo3.dat", arma_ascii);

      RLQR_Lr_mat_modo1 = RLQR_Lr.slice(0);
      RLQR_Lr_mat_modo1.save(path+"Lr_modo1.dat", arma_ascii);

      RLQR_Lr_mat_modo2 = RLQR_Lr.slice(1);
      RLQR_Lr_mat_modo2.save(path+"Lr_modo2.dat", arma_ascii);

      RLQR_Lr_mat_modo3 = RLQR_Lr.slice(2);
      RLQR_Lr_mat_modo3.save(path+"Lr_modo3.dat", arma_ascii);


      
      mat K1a, K2a, K3a;
      mat K1,  K2,  K3;

      K1a = RLQR_Kr_mat_modo1.submat(0,Nk-2,3,Nk-2);
      K2a = RLQR_Kr_mat_modo2.submat(0,Nk-2,3,Nk-2);
      K3a = RLQR_Kr_mat_modo3.submat(0,Nk-2,3,Nk-2);

      K1 = K1a.t();
      K1.save(path+"K1.dat", arma_ascii);
      
      K2 = K2a.t();
      K2.save(path+"K2.dat", arma_ascii);

      K3 = K3a.t();
      K3.save(path+"K3.dat", arma_ascii);

      double modo_s = 0.0;
      int modo = 0, modov = 0;


      //////////////// FINAL MARKOVIANO ////////////////////


   
     /////////////////////////////////////////////
    /////// DECLARACION VARIABLES RKF MARKOV///////////

   // mat  R_f, Q_f, G_f, Ef_f, Eg_f, Ec_f, Ed_f, C_f, D_f, B_f, Eb_f, xest, y, u1, M_f, N_f;
    mat  R_f, Q_f, xest, y, u1;
    double mu_f, alpha_f;
    

    cube P_f(2,2,3);

    mat P_f1;
    P_f1.eye(2,2);
    P_f1 = 1e15*P_f1;
    P_f.slice(0) = P_f1;

    mat P_f2;
    P_f2.eye(2,2);
    P_f2 = 1e15*P_f2;
    P_f.slice(1) = P_f2;

    mat P_f3;
    P_f3.eye(2,2);
    P_f3 = 1e15*P_f3;
    P_f.slice(2) = P_f3;

    


    R_f.eye(1,1);
    R_f=0.1*R_f;

    Q_f.eye(2,2);
    Q_f(0,0) = 1 ;
    Q_f(1,1) = 1*1;
    

    cube F_f(2,2,3);
    
    mat F_f1;
    F_f1.zeros(2,2);

    F_f1(0,0)=Fk_1(0,0);
    F_f1(0,1)=Fk_1(0,1);
    F_f1(1,0)=Fk_1(1,0);
    F_f1(1,1)=Fk_1(1,1);
    
    F_f.slice(0) = F_f1;


    mat F_f2;
    F_f2.zeros(2,2);

    F_f2(0,0)=Fk_2(0,0);
    F_f2(0,1)=Fk_2(0,1);
    F_f2(1,0)=Fk_2(1,0);
    F_f2(1,1)=Fk_2(1,1);
    
    F_f.slice(1) = F_f2;


    mat F_f3;
    F_f3.zeros(2,2);

    F_f3(0,0)=Fk_3(0,0);
    F_f3(0,1)=Fk_3(0,1);
    F_f3(1,0)=Fk_3(1,0);
    F_f3(1,1)=Fk_3(1,1);
    
    F_f.slice(2) = F_f3;



    cube G_f(2,2,3);
    
    mat G_f1;
    G_f1.zeros(2,2);


  

    G_f1(0,0) = 0.0937915519811;
    G_f1(1,0) = 0.0001445701410;

    G_f1(0,1) = 248.7898186342412;
    G_f1(1,1) = 0.3834842092806;

    G_f.slice(0) = G_f1;

    mat G_f2;
    G_f2.zeros(2,2);

    G_f2(0,0) = 212.1366798264865;
    G_f2(1,0) = 0.2200323877554;

 
    G_f2(0,1) = 281.3550100457339;
    G_f2(1,1) = 0.2918270179299;

    G_f.slice(1) = G_f2;
    
    mat G_f3;
    G_f3.zeros(2,2);

    G_f3(0,0) = 743.8523742975691;
    G_f3(1,0) = 0.7944461938544;


    G_f3(0,1) = 98.6564852500840;
    G_f3(1,1) = 0.1053666989771;

    G_f.slice(2) = G_f3;
    


    cube Eg_f(1,2,3);
    
    mat Eg_f1;
    Eg_f1.zeros(1,2);

    Eg_f1(0,0)=-118000;
    Eg_f1(0,1)=-118000;
     
    Eg_f.slice(0) = Eg_f1;


    mat Eg_f2;
    Eg_f2.zeros(1,2);

    Eg_f2(0,0)=-59300;
    Eg_f2(0,1)=-59300;
     
    Eg_f.slice(1) = Eg_f2;


    mat Eg_f3;
    Eg_f3.zeros(1,2);

    Eg_f3(0,0)=-47460;
    Eg_f3(0,1)=-47460;
     
    Eg_f.slice(2) = Eg_f3;


    cube Ec_f(1,2,3);
    
    mat Ec_f1;
    Ec_f1.zeros(1,2);
    Ec_f.slice(0) = Ec_f1;


    mat Ec_f2;
    Ec_f2.zeros(1,2);
    Ec_f.slice(1) = Ec_f2;


    mat Ec_f3;
    Ec_f3.zeros(1,2);
    Ec_f.slice(2) = Ec_f3;


    cube Ed_f(1,1,3);
    
    mat Ed_f1;
    Ed_f1.zeros(1,1);
    Ed_f.slice(0) = Ed_f1;


    mat Ed_f2;
    Ed_f2.zeros(1,1);
    Ed_f.slice(1) = Ed_f2;

    mat Ed_f3;
    Ed_f3.zeros(1,1);
    Ed_f.slice(2) = Ed_f3;

  
    cube Ef_f(1,2,3);

    mat Ef_f1;
    Ef_f1.zeros(1,2);
    Ef_f1(0,0)=Ef_1(0,0);
    Ef_f1(0,1)=Ef_1(0,1);

    Ef_f.slice(0) = Ef_f1;

    mat Ef_f2;
    Ef_f2.zeros(1,2);
    Ef_f2(0,0)=Ef_2(0,0);
    Ef_f2(0,1)=Ef_2(0,1);

    Ef_f.slice(1) = Ef_f2;

    mat Ef_f3;
    Ef_f3.zeros(1,2);
    Ef_f3(0,0)=Ef_3(0,0);
    Ef_f3(0,1)=Ef_3(0,1);

    Ef_f.slice(2) = Ef_f3;

   cube C_f(1,2,3);

    mat C_f1;
    C_f1.zeros(1,2);
    C_f1(0,1)=1;

    C_f.slice(0) = C_f1;

    C_f.slice(1) = C_f1;

    C_f.slice(2) = C_f1;


    
    cube D_f(1,1,3);

    mat D_f1;
    D_f1.eye(1,1);
    D_f.slice(0) = D_f1;
    D_f.slice(1) = D_f1;  
    D_f.slice(2) = D_f1;



   cube B_f(2,1,3);

    mat B_f1;
    B_f1.zeros(2,1);
    B_f1(0,0)=54.970289073749612;
    B_f1(1,0)=0.036116275747391;  
    B_f.slice(0) = B_f1;

    mat B_f2;
    B_f2.zeros(2,1);
    B_f2(0,0)=6.312602030986299;
    B_f2(1,0)=0.003213133195749;  
    B_f.slice(1) = B_f2;

    mat B_f3;
    B_f3.zeros(2,1);
    B_f3(0,0)=10.872081142022878;
    B_f3(1,0)=0.005613321525887;  
    B_f.slice(2) = B_f3;



    cube Eb_f(1,1,3);
    Eb_f.slice(0) = Eb_1;
    Eb_f.slice(1) = Eb_2;
    Eb_f.slice(2) = Eb_3;
   


              

    xest.zeros(2,1);

    y.zeros(1,1);

    u1.zeros(1,1);

    


    cube M_f(2,1,3);

    mat M_f1;
    M_f1.zeros(2,1);
    M_f1(0,0)=Hk_1(0,0)*10000;
    M_f1(1,0)=Hk_1(1,0)*10000;
    M_f.slice(0) = M_f1;

    mat M_f2;
    M_f2.zeros(2,1);
    M_f2(0,0)=Hk_2(0,0)*10000/10000;
    M_f2(1,0)=Hk_2(1,0)*10000/10000;
    M_f.slice(1) = M_f2;

    mat M_f3;
    M_f3.zeros(2,1);
    M_f3(0,0)=Hk_3(0,0)*10000/10000;
    M_f3(1,0)=Hk_3(1,0)*10000/10000;
    M_f.slice(2) = M_f3;



    cube N_f(1,1,3);
    mat N_f1;
    N_f1.eye(1,1);
    N_f.slice(0) = N_f1;
    N_f.slice(1) = N_f1;
    N_f.slice(2) = N_f1;


    mu_f = 1e10;
    alpha_f = 2;

    

      cube  LPPr;
         

   int npf = D_f1.n_rows;
   int mkf = D_f1.n_cols;
   int nxf = G_f1.n_rows;
   int muf = G_f1.n_cols;
   int nrf = Eg_f1.n_rows;
   mat xk, xk1, Pk;
   cube Pk1;

   
field<cube> LPr_campo(4,1);
//CAMPO1(0,0) = xkf;
    /////////////////////////////////////////////////////////////////////////////
    /////  Convergencia de riccati  /////////////////////////////
      //re_sul
//CAMPO1(1,0) = xk1f;
//CAMPO1(2,0) = Pkf;
//CAMPO1(3,0) = Pk1f;

  // LPPr.zeros(nxf,nxf+1);  //nx,nx+1

   Pk1=P_f;


   

   for(int cont_est=0;cont_est<7500;cont_est++){

    LPr_campo= rkf_slsm(Pk1,R_f,Q_f,F_f,G_f,Ef_f,Eg_f,Ec_f,Ed_f,C_f,D_f,B_f,Eb_f,xest,y,u1,M_f,N_f,mu_f,alpha_f,s,prob,s+1);
    Pk1=LPr_campo(3,0);

    }

  //  Beep(440,500); //  hertz (C5) for 500 milliseconds     
  //  Beep(440,500); //  hertz (C5) for 500 milliseconds     
  //  Beep(523,1000); //  hertz (C5) for 500 milliseconds     

  // juego(theta_d,theta_d*0.2); //esta se ventana puede mandar por ejemplo 
                                 //antes de calcular los controles  
	                             //incluso con instrucciones del juego

                               //DEBE IR EN OTRO  LA DO PERO AHUN NO SE EN DONE


   //////////////////dados kalman nominal  fc=0.01Hz////////////////////////////////
             
    mat A_f2;
    A_f2.zeros(4,4);

    A_f2(0,0)=0.999920001999973;
    A_f2(1,0)=0.000062497500042;
    A_f2(2,0)=0.000000000976536;
    A_f2(3,0)=0.000000000000003;
    
    A_f2(0,1)=-0.000038398720019;
    A_f2(1,1)=0.999999998800027;
    A_f2(2,1)=0.000031249999988;
    A_f2(3,1)=0.000000000122070;

    A_f2(0,2)= -0.000016383385610;
    A_f2(1,2)=-0.000000000511987;
    A_f2(2,2)=0.999999999999995;
    A_f2(3,2)=0.000007812500000 ;

    A_f2(0,3)=-0.000010485340577;
    A_f2(1,3)=-0.000000000327671;
    A_f2(2,3)= -0.000000000000003;
    A_f2(3,3)=1;

    mat B_ff2;
    B_ff2.zeros(4,1);

    B_ff2(0,0)=0.000124995000083332;
    B_ff2(1,0)=0.000000003906145835;
    B_ff2(2,0)=0.000000000000040689;
    B_ff2(3,0)=0;
    
    

    mat C_ff2;
    C_ff2.zeros(1,4);

    C_ff2(0,0)=0;
    C_ff2(0,1)=0;
    C_ff2(0,2)=0;
    C_ff2(0,3)=0.08388608000000;


    mat L_f2;
    L_f2.zeros(4,1);

    L_f2(0,0)=  7.639229067423566;
    L_f2(1,0)= 10.056132155241448 ;
    L_f2(2,0)=  2.179062351700384;
    L_f2(3,0)=  0.064956631607747;

    mat F_est2k1;
    F_est2k1.zeros(4,1);

    mat F_est2k;
    F_est2k.zeros(4,1);

     mat F_est2k1_Th;
    F_est2k1_Th.zeros(4,1);

    mat F_est2k_Th;
    F_est2k_Th.zeros(4,1);

    mat F_est2k1_emg1;
    F_est2k1_emg1.zeros(4,1);

    mat F_est2k1_emg2;
    F_est2k1_emg2.zeros(4,1);

    mat F_est2k_emg1;
    F_est2k_emg1.zeros(4,1);

    mat F_est2k_emg2;
    F_est2k_emg2.zeros(4,1);


   //////////////////dados kalman nominal  sensor de velocidad////////////////////////////////
             
    mat A_f2b;
    A_f2b.zeros(4,4);

    A_f2b(0,0)=0.4031;
    A_f2b(1,0)=0.3466;
    A_f2b(2,0)=0.0509;
    A_f2b(3,0)=0.0023;
    
    A_f2b(0,1)=-0.3025;
    A_f2b(1,1)=0.9135;
    A_f2b(2,1)=0.2482;
    A_f2b(3,1)=0.0161;

    A_f2b(0,2)=-0.1421;
    A_f2b(1,2)=-0.0413;
    A_f2b(2,2)=0.9963;
    A_f2b(3,2)=0.1279;

    A_f2b(0,3)=-0.0509;
    A_f2b(1,3)=-0.015;
    A_f2b(2,3)=-0.0014;
    A_f2b(3,3)=1;

    mat B_ff2b;
    B_ff2b.zeros(4,1);

    B_ff2b(0,0)=0;
    B_ff2b(1,0)=0;
    B_ff2b(2,0)=0;
    B_ff2b(3,0)=0;
    
    

    mat C_ff2b;
    C_ff2b.zeros(1,4);

    C_ff2b(0,0)=0;
    C_ff2b(0,1)=0;
    C_ff2b(0,2)=0;
    C_ff2b(0,3)=4.7029; 
    

    mat L_f2b;
    L_f2b.zeros(4,1);

    L_f2b(0,0)= -0.0008 ;
    L_f2b(1,0)= -0.0073;
    L_f2b(2,0)= 0.0065 ;
    L_f2b(3,0)= 0.0217 ;

    mat omega_est2k1;
    omega_est2k1.zeros(4,1);

    mat omega_est2k;
    omega_est2k.zeros(4,1);

    C_ff2b.save(path+"C_ff2b.dat", arma_ascii);
    A_f2b.save(path+"A_f2b.dat", arma_ascii);
    L_f2b.save(path+"L_f2b.dat", arma_ascii);
    omega_est2k.save(path+"omega_est2k.dat", arma_ascii);
    omega_est2k1.save(path+"omega_est2k1.dat", arma_ascii);
    

    F_est2k1_emg1.save(path+"F_est2k1_emg1.dat", arma_ascii);
    F_est2k_emg1.save(path+"F_est2k_emg1.dat", arma_ascii);
    F_est2k1_emg2.save(path+"F_est2k1_emg2.dat", arma_ascii);
    F_est2k_emg2.save(path+"F_est2k_emg2.dat", arma_ascii);
    A_f2.save(path+"A_f2.dat", arma_ascii);
    L_f2.save(path+"L_f2.dat", arma_ascii);
    C_ff2.save(path+"C_ff2.dat", arma_ascii);
    
    R_f.save(path+"R_f.dat", arma_ascii);
    Q_f.save(path+"Q_f.dat", arma_ascii);
    F_f.save(path+"F_f.dat", arma_ascii);
    G_f.save(path+"G_f.dat", arma_ascii);
    Ef_f.save(path+"Ef_f.dat", arma_ascii);
    Eg_f.save(path+"Eg_f.dat", arma_ascii);
    Ec_f.save(path+"Ec_f.dat", arma_ascii);
    Ed_f.save(path+"Ed_f.dat", arma_ascii);
    C_f.save(path+"C_f.dat", arma_ascii);
    D_f.save(path+"D_f.dat", arma_ascii);
    B_f.save(path+"B_f.dat", arma_ascii);
    Eb_f.save(path+"Eb_f.dat", arma_ascii);
    y.save(path+"y.dat", arma_ascii);
    u1.save(path+"u1.dat", arma_ascii);
    M_f.save(path+"M_f.dat", arma_ascii);
    N_f.save(path+"N_f.dat", arma_ascii);
    prob.save(path+"prob.dat", arma_ascii);
    xest.save(path+"xest.dat", arma_ascii);
    Pk1.save(path+"Pk1.dat", arma_ascii);
    // LPr_campo.save(path+"LPr_campo.dat", arma_ascii);

    std::cout<<"Terminado";


      

}

#endif