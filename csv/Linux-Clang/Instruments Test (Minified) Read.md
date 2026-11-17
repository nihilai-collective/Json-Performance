
----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 2433.88 | 0.106311 | 5010.37ms | 108313 | 320 | 651430 | 42440.6 | 0.00184084 | 2.07526 | 8.73898 | 1.75646 | 0.00298764 | 1.43104e-05 | 9.54987e-06 | 1(Win) | true |
| Glaze | 2261.45 | 0.0729084 | 5316.95ms | 108313 | 4890 | 5.42316e+06 | 45676.7 | 0.0126487 | 2.22407 | 10.5346 | 1.88219 | 0.00284379 | 1.93543e-05 | 1.15586e-05 | 2(Loss) | true |
| Jsonifier (two-stage) | 1909.8 | 0.067122 | 6174.06ms | 108313 | 4890 | 6.44501e+06 | 54086.9 | 0.181795 | 2.65102 | 11.8155 | 2.07091 | 0.00305074 | 3.64712e-05 | 2.4924e-05 | 3(Loss) | true |
| simdjson (ondemand) | 760.529 | 0.0955068 | 7341.62ms | 108313 | 1280 | 2.15382e+07 | 135820 | 0.120288 | 6.58685 | 28.4797 | 4.48486 | 0.00425269 | 7.16745e-05 | 4.57802e-05 | 4(Loss) | true |
