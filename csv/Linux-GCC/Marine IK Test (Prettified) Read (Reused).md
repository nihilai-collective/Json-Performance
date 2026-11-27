
----
### Marine IK Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2835.03 | 0.0668591 | 8521.98ms | 7351818 | 160 | 4.37438e+08 | 2.47308e+06 | 0.405862 | 1.788 | 7.49457 | 1.40783 | 0.0121221 | 0.0548667 | 0.000841067 | 1(Win) | true |
| Jsonifier | 2776.96 | 0.09676 | 8615.14ms | 7351818 | 160 | 9.54909e+08 | 2.52479e+06 | 0.0218333 | 1.81725 | 7.50676 | 1.69668 | 0.00892244 | 0.0277085 | 0.000431563 | 2(Loss) | true |
| simdjson (reflection) | 2662.28 | 0.0812758 | 8912.1ms | 7351818 | 160 | 7.33037e+08 | 2.63355e+06 | 0.135979 | 1.89571 | 8.32142 | 1.35862 | 0.00656205 | 0.0520583 | 0.000597685 | 3(Loss) | true |
| simdjson (ondemand) | 2236.68 | 0.0836911 | 5075.35ms | 7351818 | 80 | 5.50595e+08 | 3.13467e+06 | 0.547132 | 2.24961 | 9.4908 | 1.64843 | 0.0079031 | 0.053795 | 0.000578061 | 4(Loss) | true |
| Glaze | 2207.12 | 0.127439 | 5143.85ms | 7351818 | 40 | 6.55541e+08 | 3.17664e+06 | 0.131299 | 2.30123 | 10.4916 | 2.06527 | 0.00880636 | 0.0279183 | 0.000114849 | 5(Loss) | true |
