extern "C" {
#include "caffe/swlayers/sw_conv_layer_impl.h"
}
#include "caffe/swlayers/conv_layer_impl.hpp"
#include <math.h>
//#include <iostream>
//using namespace std;
#include <stdio.h>
#include "athread.h"

void test_forward_pad_float() {
  int Ni, No, B, Co, Ro, Ci, Ri, K, pad;
  Ni = 512;
  No = 512;
  B  = 128;
  K  = 1;
  pad = 3;
  Ci = 8;
  Ri = 8;
  Co = Ci+2*pad-K+1;
  Ro = Ri+2*pad-K+1;

  int in_size     = Ni*B*Ci*Ri;
  int weight_size = Ni*No*K*K;
  int out_size    = No*B*Co*Ro;

  float* in = (float*)malloc(sizeof(float)*in_size);
  float* weight = (float*)malloc(sizeof(float)*weight_size);
  float* out = (float*)malloc(sizeof(float)*out_size);
  float* out_ref = (float*)malloc(sizeof(float)*out_size);

  for( int i = 0; i < in_size; ++i )
    in[i] = rand()/(float)RAND_MAX;

  for( int i = 0; i < weight_size; ++i )
    weight[i] = rand()/(float)RAND_MAX;

  for( int i = 0; i < out_size; ++i ) {
    out_ref[i] = 0;
    out[i] = 0;
  }


  for( int st = 0; st < 1; ++st ){
    sw_conv_forward_pad_impl_f(
        in,
        weight,
        out,
        Ci,
        Ri,
        K,
        Ni,
        No,
        B,
        pad);
    printf("sw version pad conv OK\n");

    conv_forward_pad_impl<float>(
        in,
        weight,
        out_ref,
        Ci,
        Ri,
        K,
        Ni,
        No,
        B,
        pad);
    printf("inner loop OK!\n");
  }
  //if(!athread_halt())
  //  printf("athread halt not OK!\n");

  float sum = 0, sum_ref = 0;
  for( int i = 0; i < out_size; ++i ) {
   if( fabs(out_ref[i] - out[i]) > 1e-4 )
     printf("%f vs %f\n", out_ref[i], out[i]);
   sum += out[i];
   sum_ref += out_ref[i];
  }
  printf("sum %f vs sum_ref %f athread forward OK!\n", sum, sum_ref);

  free(out_ref);
  free(out);
  free(in);
  free(weight);

}

void test_forward_pad() {
  int Ni, No, B, Co, Ro, Ci, Ri, K, pad;
  Ni = 512;
  No = 512;
  B  = 128;
  K  = 1;
  pad = 3;
  Ci = 8;
  Ri = 8;
  Co = Ci+2*pad-K+1;
  Ro = Ri+2*pad-K+1;

  int in_size     = Ni*B*Ci*Ri;
  int weight_size = Ni*No*K*K;
  int out_size    = No*B*Co*Ro;

  double* in = (double*)malloc(sizeof(double)*in_size);
  double* weight = (double*)malloc(sizeof(double)*weight_size);
  double* out = (double*)malloc(sizeof(double)*out_size);
  double* out_ref = (double*)malloc(sizeof(double)*out_size);

  for( int i = 0; i < in_size; ++i )
    in[i] = rand()/(double)RAND_MAX;

  for( int i = 0; i < weight_size; ++i )
    weight[i] = rand()/(double)RAND_MAX;

  for( int i = 0; i < out_size; ++i ) {
    out_ref[i] = 0;
    out[i] = 0;
  }


  for( int st = 0; st < 1; ++st ){
    sw_conv_forward_pad_impl_d(
        in,
        weight,
        out,
        Ci,
        Ri,
        K,
        Ni,
        No,
        B,
        pad);
    printf("sw version pad conv OK\n");

    conv_forward_pad_impl<double>(
        in,
        weight,
        out_ref,
        Ci,
        Ri,
        K,
        Ni,
        No,
        B,
        pad);
    printf("inner loop OK!\n");
  }
  //if(!athread_halt())
  //  printf("athread halt not OK!\n");

  double sum = 0, sum_ref = 0;
  for( int i = 0; i < out_size; ++i ) {
   if( fabs(out_ref[i] - out[i]) > 1e-4 )
     printf("%lf vs %lf\n", out_ref[i], out[i]);
   sum += out[i];
   sum_ref += out_ref[i];
  }
  printf("sum %lf vs sum_ref %lf athread forward OK!\n", sum, sum_ref);

  free(out_ref);
  free(out);
  free(in);
  free(weight);

}

void test_forward() {
  int Ni, No, B, Co, Ro, Ci, Ri, K;
  Ni = 128;
  No = 256;
  B  = 128;
  Co = 2;
  Ro = 2;
  K  = 3;
  Ci = Co + K - 1;
  Ri = Ro + K - 1;

  int in_size     = Ni*B*Ci*Ri;
  int weight_size = Ni*No*K*K;
  int out_size    = No*B*Co*Ro;

  double* in = (double*)malloc(sizeof(double)*in_size);
  double* weight = (double*)malloc(sizeof(double)*weight_size);
  double* out = (double*)malloc(sizeof(double)*out_size);
  double* out_ref = (double*)malloc(sizeof(double)*out_size);

  for( int i = 0; i < in_size; ++i )
    in[i] = rand()/(double)RAND_MAX;

  for( int i = 0; i < weight_size; ++i )
    weight[i] = rand()/(double)RAND_MAX;


  for( int st = 0; st < 1; ++st ){
    sw_conv_forward_impl_d(
        in,
        weight,
        out,
        Ci,
        Ri,
        K,
        Ni,
        No,
        B);

    conv_forward_impl<double>(
        in,
        weight,
        out_ref,
        Ci,
        Ri,
        K,
        Ni,
        No,
        B);
    printf("inner loop OK!\n");
  }
  //if(!athread_halt())
  //  printf("athread halt not OK!\n");

  double sum = 0, sum_ref = 0;
  for( int i = 0; i < out_size; ++i ) {
   if( fabs(out_ref[i] - out[i]) > 1e-4 )
     printf("%lf vs %lf\n", out_ref[i], out[i]);
   sum += out[i];
   sum_ref += out_ref[i];
  }
  free(out_ref);
  free(out);
  free(in);
  free(weight);
  printf("sum %lf vs sum_ref %lf athread forward OK!\n", sum, sum_ref);

}

int test_backward() {
  int Ni, No, B, Co, Ro, Ci, Ri, K;
  Ni = 128;
  No = 128;
  B  = 128;
  Co = 2;
  Ro = 2;
  K  = 3;
  Ci = Co + K - 1;
  Ri = Ro + K - 1;

  int in_size     = Ni*B*Ci*Ri;
  int weight_size = Ni*No*K*K;
  int out_size    = No*B*Co*Ro;

  double* in = (double*)malloc(sizeof(double)*in_size);
  double* in_diff = (double*)malloc(sizeof(double)*in_size);
  double* in_diff_ref = (double*)malloc(sizeof(double)*in_size);
  double* weight_diff = (double*)malloc(sizeof(double)*weight_size);
  double* weight_diff_ref = (double*)malloc(sizeof(double)*weight_size);
  double* weight = (double*)malloc(sizeof(double)*weight_size);
  double* out_diff = (double*)malloc(sizeof(double)*out_size);

  for( int i = 0; i < in_size; ++i )
    in[i] = rand()/(double)RAND_MAX;
  for( int i = 0; i < weight_size; ++i )
    weight[i] = rand()/(double)RAND_MAX;
  for( int i = 0; i < out_size; ++i )
    out_diff[i] = rand()/(double)RAND_MAX;

  sw_conv_backward_impl_d(
        in,
        out_diff,
        weight,
        in_diff,
        weight_diff,
        Ci,
        Ri,
        K,
        Ni,
        No,
        B);

  conv_backward_impl<double>(
        in,
        out_diff,
        weight,
        in_diff_ref,
        weight_diff_ref,
        Ci,
        Ri,
        K,
        Ni,
        No,
        B);

  for( int i = 0; i < in_size; ++i )
    if(fabs(in_diff[i] - in_diff_ref[i]) > 1e-4)
      printf("in_diff %lf vs ref %lf\n", in_diff[i], in_diff_ref[i]);

  for( int i = 0; i < weight_size; ++i )
    if(fabs(weight_diff[i] - weight_diff_ref[i]) > 1e-4)
      printf("weight_diff %lf vs ref %lf\n", weight_diff[i], weight_diff_ref[i]);
  printf("backward test OK!");

  free(in);
  free(in_diff);
  free(in_diff_ref);
  free(weight_diff);
  free(weight_diff_ref);
  free(weight);
  free(out_diff);


}

int test_backward_pad_float() {
  int Ni, No, B, Co, Ro, Ci, Ri, K;
  int pad = 1;
  Ni = 128;
  No = 128;
  B  = 128;
  Ci = 4;
  Ri = 4;
  K  = 3;
  //for mem alloc
  Co = Ci - K+1 + 2*pad;
  Ro = Ri - K+1 + 2*pad;

  int in_size     = Ni*B*Ci*Ri;
  int weight_size = Ni*No*K*K;
  int out_size    = No*B*Co*Ro;

  float* in = (float*)malloc(sizeof(float)*in_size);
  float* in_diff = (float*)malloc(sizeof(float)*in_size);
  float* in_diff_ref = (float*)malloc(sizeof(float)*in_size);
  float* weight_diff = (float*)malloc(sizeof(float)*weight_size);
  float* weight_diff_ref = (float*)malloc(sizeof(float)*weight_size);
  float* weight = (float*)malloc(sizeof(float)*weight_size);
  float* out_diff = (float*)malloc(sizeof(float)*out_size);

  for( int i = 0; i < in_size; ++i )
    in[i] = rand()/(float)RAND_MAX;
  for( int i = 0; i < weight_size; ++i )
    weight[i] = rand()/(float)RAND_MAX;
  for( int i = 0; i < out_size; ++i )
    out_diff[i] = rand()/(float)RAND_MAX;
  sw_conv_backward_pad_impl_f(
        in,
        out_diff,
        weight,
        in_diff,
        weight_diff,
        Ci,
        Ri,
        K,
        Ni,
        No,
        B,
        pad);

  conv_backward_pad_impl<float>(
        in,
        out_diff,
        weight,
        in_diff_ref,
        weight_diff_ref,
        Ci,
        Ri,
        K,
        Ni,
        No,
        B,
        pad);

  for( int i = 0; i < in_size; ++i )
    if(fabs(in_diff[i] - in_diff_ref[i]) > 1e-2)
      printf("in_diff %f vs ref %f\n", in_diff[i], in_diff_ref[i]);
  for( int i = 0; i < weight_size; ++i )
    if(fabs(weight_diff[i] - weight_diff_ref[i]) > 1e-2)
      printf("weight_diff %f vs ref %f\n", weight_diff[i], weight_diff_ref[i]);
  printf("backward test OK!");

  free(in);
  free(in_diff);
  free(in_diff_ref);
  free(weight_diff);
  free(weight_diff_ref);
  free(weight);
  free(out_diff);
}

int test_backward_pad() {
  int Ni, No, B, Co, Ro, Ci, Ri, K;
  int pad = 1;
  Ni = 128;
  No = 128;
  B  = 128;
  Ci = 4;
  Ri = 4;
  K  = 3;
  //for mem alloc
  Co = Ci - K+1 + 2*pad;
  Ro = Ri - K+1 + 2*pad;

  int in_size     = Ni*B*Ci*Ri;
  int weight_size = Ni*No*K*K;
  int out_size    = No*B*Co*Ro;

  double* in = (double*)malloc(sizeof(double)*in_size);
  double* in_diff = (double*)malloc(sizeof(double)*in_size);
  double* in_diff_ref = (double*)malloc(sizeof(double)*in_size);
  double* weight_diff = (double*)malloc(sizeof(double)*weight_size);
  double* weight_diff_ref = (double*)malloc(sizeof(double)*weight_size);
  double* weight = (double*)malloc(sizeof(double)*weight_size);
  double* out_diff = (double*)malloc(sizeof(double)*out_size);

  for( int i = 0; i < in_size; ++i )
    in[i] = rand()/(double)RAND_MAX;
  for( int i = 0; i < weight_size; ++i )
    weight[i] = rand()/(double)RAND_MAX;
  for( int i = 0; i < out_size; ++i )
    out_diff[i] = rand()/(double)RAND_MAX;
  sw_conv_backward_pad_impl_d(
        in,
        out_diff,
        weight,
        in_diff,
        weight_diff,
        Ci,
        Ri,
        K,
        Ni,
        No,
        B,
        pad);

  conv_backward_pad_impl<double>(
        in,
        out_diff,
        weight,
        in_diff_ref,
        weight_diff_ref,
        Ci,
        Ri,
        K,
        Ni,
        No,
        B,
        pad);

  for( int i = 0; i < in_size; ++i )
    if(fabs(in_diff[i] - in_diff_ref[i]) > 1e-4)
      printf("in_diff %lf vs ref %lf\n", in_diff[i], in_diff_ref[i]);
  for( int i = 0; i < weight_size; ++i )
    if(fabs(weight_diff[i] - weight_diff_ref[i]) > 1e-4)
      printf("weight_diff %lf vs ref %lf\n", weight_diff[i], weight_diff_ref[i]);
  printf("backward test OK!");

  free(in);
  free(in_diff);
  free(in_diff_ref);
  free(weight_diff);
  free(weight_diff_ref);
  free(weight);
  free(out_diff);
}


int main() {
  //test_forward_pad();
  //test_backward_pad();
  test_forward_pad_float();
  test_backward_pad_float();
  //test_backward();
  //test_forward();
  return 0;
}
