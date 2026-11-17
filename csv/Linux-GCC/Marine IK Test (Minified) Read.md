
----
### Marine IK Test (Minified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 636.549 | 0.0729692 | 8588.33ms | 1834197 | 160 | 6.4332e+08 | 2.74798e+06 | 0.0629956 | 8.03145 | 33.6916 | 7.1199 | 0.0376337 | 0.138988 | 2.57504e-05 | 1(Win) | true |
| simdjson (ondemand) | 604.955 | 0.227649 | 9019.12ms | 1834197 | 30 | 1.29987e+09 | 2.8915e+06 | 0.384614 | 8.38055 | 34.9304 | 6.32115 | 0.044178 | 0.1397 | 0.000563934 | 2(Loss) | true |
