
----
### Canada Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6074.82 | 0.211879 | 6628.07ms | 6661897 | 160 | 7.85639e+08 | 1.04584e+06 | 0.210865 | 0.829698 | 2.50625 | 0.117138 | 0.000103824 | 0.0279742 | 4.7054e-05 | 1(Win) | true |
| Glaze | 3918.75 | 0.144302 | 5084.01ms | 6661897 | 40 | 2.18931e+08 | 1.62125e+06 | 0.148918 | 1.28672 | 4.33307 | 0.464028 | 0.00373796 | 0.0248763 | 5.07363e-05 | 2(Loss) | true |
| simdjson (reflection) | 383.946 | 0.320165 | 11494.5ms | 6661989 | 40 | 1.12273e+11 | 1.65476e+07 | 1.12265 | 13.0913 | 41.3255 | 5.67482 | 0.0241782 | 0.255712 | 0.121477 | 3(Loss) | true |
