#include <TMB.hpp>
template<class Type>
Type objective_function<Type>::operator() ()
{ 
  DATA_SCALAR(n);
  DATA_SCALAR(epsilon_a);
  DATA_SCALAR(epsilon_r);
  DATA_SCALAR(A);
  DATA_SCALAR(eta_m);
  DATA_SCALAR(a);
  DATA_SCALAR(Winf);
  DATA_SCALAR(Wfs);
  DATA_INTEGER(M);
  DATA_SCALAR(u);
  DATA_INTEGER(selType);
  DATA_SCALAR(sigmab);
  DATA_SCALAR(sigmaa);
  DATA_VECTOR(sel3params);
  Type G1, G2, mesh, OP, wla, wlb;
  if(selType == 3) {
    G1 = sel3params(0);
    G2 = sel3params(1);
    mesh = sel3params(2);
    OP = sel3params(3);
    wla = sel3params(4);
    wlb = sel3params(5);  
  }
  PARAMETER(logF);
  Type Fmsy = exp(logF);
  ADREPORT(Fmsy);
  vector<Type> g(M);
  vector<Type> m(M);
  vector<Type> psi_F(M);
  vector<Type> psi_m(M);
  vector<Type> N(M);
  vector<Type> ww(M);
  vector<Type> delta(M);
  Type cumsum;
  Type w_r;
  Type B;
  Type Rrel;
  Type Y;
  
  w_r=0.001;
  ww(0) = w_r;
  g(0)=A * pow(ww(0),n) * (1 - pow(ww(0)/Winf, 1-n) * (epsilon_a ));
  m(0) = a * A * pow(ww(0), n - 1);
  N(0)=1/g(0); 
  psi_m(0) = 0;

  for(int i=1; i<M; i++) {
    ww(i) = exp(log(w_r) + i * (log(Winf) - log(w_r)) / (M - 1.0));
    delta(i) = ww(i) - ww(i-1);
    psi_m(i) = 1 / (1 + pow(ww(i)/(eta_m * Winf),-10));
    if(selType == 1) {
      psi_F(i) = 1 / (1 + pow(ww(i)/(Wfs),-u));  
    } else if (selType == 2){
      if(ww(i) <= Wfs) {
        psi_F(i) = exp( - pow( ((ww(i) - Wfs)/ Winf), 2) / (2 * pow(sigmab, 2))); 
      } else {
        psi_F(i) = exp( - pow( ((ww(i) - Wfs)/ Winf), 2) / (2 * pow(sigmaa, 2)));
      }
    } else if (selType == 3) {
      psi_F(i) = exp(- pow((pow(ww(i) / wla, 1 / wlb) * G1 + G2) /(2 * mesh) - OP, 2) / (2 * pow( sigmaa, 2)));
    }
    
    m(i) = a * A * pow(ww(i), n - 1) + Fmsy * psi_F(i);
    g(i) = A * pow(ww(i),n) * (1 - pow(ww(i)/Winf, 1-n) * (epsilon_a + (1-epsilon_a)*psi_m(i)));
    cumsum += (m(i-1))/g(i-1) * delta(i);
    N(i)=exp(-cumsum)/g(i);
    
  } 
  delta(M-1) = 0;
  B = (psi_m * N * ww * delta).sum();
  Rrel = 1 - (pow(Winf,1-n) * w_r / (epsilon_r * (1 - epsilon_a) * A * B));
  Y =  Fmsy * Rrel * (psi_F * N * ww * delta).sum();
  return - Y;
}
