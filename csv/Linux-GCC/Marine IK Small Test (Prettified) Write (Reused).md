
----
### Marine IK Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 6593.91 | 0.0876523 | 1089.17ms | 24579 | 2560 | 24854.8 | 3554.85 | 0.135331 | 0.774122 | 1.86513 | 0.100655 | 6.67808e-05 | 7.48543e-06 | 1.90712e-06 | 1(Win) | true |
| Glaze | 3908.62 | 0.139005 | 1333.58ms | 24579 | 1280 | 88951.2 | 5997.09 | 0.038484 | 1.30296 | 3.76179 | 0.442166 | 0.000324051 | 3.22303e-05 | 1.82447e-05 | 2(Loss) | true |
| simdjson (reflection) | 529.97 | 0.123376 | 5233.81ms | 24893 | 2560 | 7.81909e+06 | 44794.7 | 0.0199464 | 9.54563 | 36.8171 | 6.04773 | 0.00763416 | 0.000118005 | 7.24193e-05 | 3(Loss) | true |
