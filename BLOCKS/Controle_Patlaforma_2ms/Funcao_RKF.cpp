// Função Filtro de Kalman robusto


mat RKF(mat P_f, mat R_f, mat Q_f, mat F_f, mat G_f, mat Ef_f, mat Eg_f, mat Ec_f, mat Ed_f, mat C_f, mat D_f, mat B_f, mat Eb_f, mat xest, mat y, mat u, mat M_f, mat N_f, double mu_f, double alpha_f){
   
   double SEL = 1;
   int np, mk, nx, mu, nr;
   double lambda_h;
   mat SIGMA1, SIGMA2;
   mat I_NX, I_NR, I_NP,I_MU;
   mat Z_NX_NR, Z_NR_NX, Z_NR_NP,Z_NP_NR,Z_NX_NX,Z_NX_MU,Z_NX_MK,Z_MU_NX,Z_MU_MK,Z_MK_NX,Z_MK_MU,Z_MU_MU,Z_MK_MK;
   mat Z_NR_1,Z_NX_1,Z_MU_1,Z_MK_1;
   mat Z_NX_NXpNR,Z_NX_NPpNR,Z_MU_NXpNR,Z_MU_NPpNR,Z_MK_NXpNR,Z_MK_NPpNR;
   mat Z_NXpNR_NX,Z_NXpNR_MU,Z_NXpNR_MK;
   mat Z_NXpNR_NPpNR;
   mat Z_NPpNR_NX,Z_NPpNR_MU,Z_NPpNR_MK,Z_NPpNR_NXpNR;
   mat I_k,I_MK;

   mat SIGMA1_row1, SIGMA1_row2,SIGMA2_row1, SIGMA2_row2;
   mat G_k, F_k, D_k, C_k, B_k,y_k;
   mat Xf1,Xf2,Xf3,Xf4,Xf5,Xf6,Xf7,Xf8,Xf9,Xf10,Xf11,X;

   
   np = D_f.n_rows;
   mk = D_f.n_cols;
   nx = G_f.n_rows;
   mu = G_f.n_cols;
   nr = Eg_f.n_rows;

   
   I_NX.eye(nx,nx);
   I_NR.eye(nr,nr);
   I_NP.eye(np,np);
   I_MU.eye(mu,mu);
   I_MK.eye(mk,mk);
   Z_NX_NR.zeros(nx,nr);
   Z_NR_NX.zeros(nr,nx);
   Z_NR_NP.zeros(nr,np);
   Z_NP_NR.zeros(np,nr);
   Z_NX_NX.zeros(nx,nx);

   Z_NR_1.zeros(nr,1);
   Z_NX_1.zeros(nx,1);
   Z_MU_1.zeros(mu,1);
   Z_MK_1.zeros(mk,1);

   Z_NX_MU.zeros(nx,mu);
   Z_NX_MK.zeros(nx,mk);
   Z_MU_MK.zeros(mu,mk);
   Z_MU_NX.zeros(mu,nx);
   Z_MK_NX.zeros(mk,nx);
   Z_MK_MU.zeros(mk,mu);
   Z_MU_MU.zeros(mu,mu);
   Z_MK_MK.zeros(mk,mk);

   Z_NX_NXpNR.zeros(nx,(nx+nr));
   Z_NX_NPpNR.zeros(nx,(np+nr));
   Z_MU_NXpNR.zeros(mu,(nx+nr));
   Z_MU_NPpNR.zeros(mu,(np+nr));
   Z_MK_NXpNR.zeros(mk,(nx+nr));
   Z_MK_NPpNR.zeros(mk,(np+nr));

   Z_NXpNR_NX.zeros((nx+nr),nx);
   Z_NXpNR_MU.zeros((nx+nr),mu);
   Z_NXpNR_MK.zeros((nx+nr),mk);

   Z_NXpNR_NPpNR.zeros((nx+nr),(np+nr));

   Z_NPpNR_NX.zeros((np+nr),nx);
   Z_NPpNR_MU.zeros((np+nr),mu);
   Z_NPpNR_MK.zeros((np+nr),mk);
   Z_NPpNR_NXpNR.zeros((np+nr),(nx+nr));

   mat mat_norm; 
   mat_norm.zeros(2,2);
   mat_norm(0,0) = as_scalar(M_f.t()*M_f);
   mat_norm(1,1) = as_scalar(N_f.t()*N_f);

   lambda_h =(1+alpha_f)*norm(mu_f*mat_norm,2);

   SIGMA1_row1 = join_rows(pow(mu_f,-1)*I_NX - pow(lambda_h,-1)*M_f*M_f.t(),Z_NX_NR);
   SIGMA1_row2 = join_rows(Z_NR_NX,pow(lambda_h,-1)*I_NR);
   
   SIGMA2_row1 = join_rows(pow(mu_f,-1)*I_NP - pow(lambda_h,-1)*N_f*N_f.t(),Z_NP_NR);
   SIGMA2_row2 = join_rows(Z_NR_NP,pow(lambda_h,-1)*I_NR);

   SIGMA1 = join_cols(SIGMA1_row1,SIGMA1_row2);
   SIGMA2 = join_cols(SIGMA2_row1,SIGMA2_row2);
   
   I_k.zeros((nx+nr),nx);
   I_k = join_cols(I_NX,Z_NR_NX);
      
   G_k = join_cols(G_f,Eg_f);
   F_k = join_cols(F_f,Ef_f);
   D_k = join_cols(D_f,Ed_f);
   C_k = join_cols(C_f,Ec_f);
   B_k = join_cols(B_f,Eb_f);

   y_k = join_cols(y,Z_NR_1);

   ///////np = 1, mk = 1, nx = 2, mu = 2, nr = 1 
   Xf1 =  join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(P_f,           Z_NX_MU),    Z_NX_MK),    Z_NX_NX),                 Z_NX_NXpNR),     Z_NX_NPpNR),     I_NX),       Z_NX_MU),    Z_NX_MK),    Z_NX_NX),  Z_NX_NX);
   Xf2 =  join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(Z_MU_NX,       Q_f),        Z_MU_MK),    Z_MU_NX),                 Z_MU_NXpNR),     Z_MU_NPpNR),     Z_MU_NX),    I_MU),       Z_MU_MK),    Z_MU_NX),  Z_MU_NX);
   Xf3 =  join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(Z_MK_NX,       Z_MK_MU),    R_f),        Z_MK_NX),                 Z_MK_NXpNR),     Z_MK_NPpNR),     Z_MK_NX),    Z_MK_MU),    I_MK),       Z_MK_NX),  Z_MK_NX);
   Xf4 =  join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(Z_NX_NX,       Z_NX_MU),    Z_NX_MK),    (SEL*pow(mu_f,-1)*I_NX)), Z_NX_NXpNR),     Z_NX_NPpNR),     I_NX),       Z_NX_MU),    Z_NX_MK),    -1*I_NX),  Z_NX_NX);
   Xf5 =  join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(Z_NXpNR_NX,    Z_NXpNR_MU), Z_NXpNR_MK), Z_NXpNR_NX),              (SEL*SIGMA1)),   Z_NXpNR_NPpNR),  Z_NXpNR_NX), G_k),        Z_NXpNR_MK), F_k),      (-1*I_k));
   Xf6 =  join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(Z_NPpNR_NX,    Z_NPpNR_MU), Z_NPpNR_MK), Z_NPpNR_NX),              Z_NPpNR_NXpNR),  SEL*SIGMA2),     Z_NPpNR_NX), Z_NPpNR_MU), D_k),        C_k),      Z_NPpNR_NX);
   Xf7 =  join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(I_NX,          Z_NX_MU),    Z_NX_MK),    I_NX),                    Z_NX_NXpNR),     Z_NX_NPpNR),     Z_NX_NX),    Z_NX_MU),    Z_NX_MK),    Z_NX_NX),  Z_NX_NX);
   Xf8 =  join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(Z_MU_NX,       I_MU),       Z_MU_MK),    Z_MU_NX),                 G_k.t()),        Z_MU_NPpNR),     Z_MU_NX),    Z_MU_MU),    Z_MU_MK),    Z_MU_NX),  Z_MU_NX);
   Xf9 =  join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(Z_MK_NX,       Z_MK_MU),    I_MK),       Z_MK_NX),                 Z_MK_NXpNR),     D_k.t()),        Z_MK_NX),    Z_MK_MU),    Z_MK_MK),    Z_MK_NX),  Z_MK_NX);
   Xf10 = join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(Z_NX_NX,       Z_NX_MU),    Z_NX_MK),    -1*I_NX),                 F_k.t()),        C_k.t()),        Z_NX_NX),    Z_NX_MU),    Z_NX_MK),    Z_NX_NX),  Z_NX_NX);
   Xf11 = join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(join_rows(Z_NX_NX,       Z_NX_MU),    Z_NX_MK),    Z_NX_NX),                 -1*I_k.t()),         Z_NX_NPpNR),     Z_NX_NX),    Z_NX_MU),    Z_NX_MK),    Z_NX_NX),  Z_NX_NX);

   X = join_cols(join_cols(join_cols(join_cols(join_cols(join_cols(join_cols(join_cols(join_cols(join_cols(Xf1,Xf2),Xf3),Xf4),Xf5),Xf6),Xf7),Xf8),Xf9),Xf10),Xf11);

   mat Xif1  = join_rows(join_rows(Z_NX_1, Z_NX_NX),    Z_NX_NX);
   mat Xif2  = join_rows(join_rows(Z_MU_1, Z_MU_NX),    Z_MU_NX);
   mat Xif3  = join_rows(join_rows(Z_MK_1, Z_MK_NX),    Z_MK_NX);
   mat Xif4  = join_rows(join_rows(-xest,  Z_NX_NX),    Z_NX_NX);
   mat Xif5  = join_rows(join_rows(-B_k*u, Z_NXpNR_NX), Z_NXpNR_NX);
   mat Xif6  = join_rows(join_rows(y_k,    Z_NPpNR_NX), Z_NPpNR_NX);
   mat Xif7  = join_rows(join_rows(Z_NX_1, Z_NX_NX),    Z_NX_NX);
   mat Xif8  = join_rows(join_rows(Z_MU_1, Z_MU_NX),    Z_MU_NX);
   mat Xif9  = join_rows(join_rows(Z_MK_1, Z_MK_NX),    Z_MK_NX);
   mat Xif10 = join_rows(join_rows(Z_NX_1, -I_NX),      Z_NX_NX);
   mat Xif11 = join_rows(join_rows(Z_NX_1, Z_NX_NX),    -I_NX);


  mat Xi = join_cols(join_cols(join_cols(join_cols(join_cols(join_cols(join_cols(join_cols(join_cols(join_cols(Xif1,Xif2),Xif3),Xif4),Xif5),Xif6),Xif7),Xif8),Xif9),Xif10),Xif11);
   
  mat Zeta_f1  = join_rows(Z_NX_NX,Z_NX_NX);
  mat Zeta_f2  = join_rows(Z_MU_NX,Z_MU_NX);
  mat Zeta_f3  = join_rows(Z_MK_NX,Z_MK_NX);
  mat Zeta_f4  = join_rows(Z_NX_NX,Z_NX_NX);
  mat Zeta_f5  = join_rows(Z_NXpNR_NX,Z_NXpNR_NX);
  mat Zeta_f6  = join_rows(Z_NPpNR_NX,Z_NPpNR_NX);
  mat Zeta_f7  = join_rows(Z_NX_NX,Z_NX_NX);
  mat Zeta_f8  = join_rows(Z_MU_NX,Z_MU_NX);
  mat Zeta_f9  = join_rows(Z_MK_NX,Z_MK_NX);
  mat Zeta_f10 = join_rows(I_NX,Z_NX_NX);
  mat Zeta_f11 = join_rows(Z_NX_NX,I_NX);

  mat Zeta = join_cols(join_cols(join_cols(join_cols(join_cols(join_cols(join_cols(join_cols(join_cols(join_cols(Zeta_f1,Zeta_f2),Zeta_f3),Zeta_f4),Zeta_f5),Zeta_f6),Zeta_f7),Zeta_f8),Zeta_f9),Zeta_f10),Zeta_f11);
  
  mat LPP = Zeta.t()*inv(X)*Xi;

  // mat X_dim;
 // X_dim.zeros(2,1);
  
   //X_dim(0,0) = np;
   //X_dim(1,0) = mk;
   //X_dim(2,0) = nx;
   //X_dim(3,0) = mu;
   //X_dim(4,0) = nr;
   
  // X_dim(0,0) = xk.n_rows; 
  // X_dim(1,0) = xk.n_cols;

   //re_sul
   //return X_dim;
   return LPP;
}
