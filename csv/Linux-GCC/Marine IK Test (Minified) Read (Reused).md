
----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 942.715 | 0.0920447 | 6474.1ms | 1834197 | 80 | 2.33356e+08 | 1.85552e+06 | 0.29491 | 5.32984 | 22.1049 | 4.95266 | 0.0362165 | 0.0567797 | 0.000225276 | 1(Win) | true |
| Jsonifier (two-stage) | 802.534 | 0.0503429 | 7531.66ms | 1834197 | 160 | 1.92646e+08 | 2.17963e+06 | 0.22637 | 6.27687 | 26.3978 | 5.37607 | 0.041543 | 0.120093 | 0.000245325 | 2(Loss) | true |
| Glaze | 719.855 | 0.0553663 | 8306.58ms | 1834197 | 30 | 5.4302e+07 | 2.42997e+06 | 0.0206602 | 7.01229 | 29.3558 | 5.62413 | 0.0337915 | 0.0594703 | 0.000267074 | 3(Loss) | true |
| simdjson (reflection) | 690.582 | 0.145058 | 8563.27ms | 1834197 | 30 | 4.0501e+08 | 2.53297e+06 | 0.00029741 | 7.3153 | 31.8243 | 5.79337 | 0.0318403 | 0.11217 | 0.00109905 | 4(Loss) | true |
| simdjson (ondemand) | 583.182 | 0.0646741 | 10052.6ms | 1834197 | 160 | 6.02093e+08 | 2.99945e+06 | 0.00569009 | 8.63065 | 34.453 | 6.64592 | 0.0372631 | 0.118976 | 0.000544697 | 5(Loss) | true |
