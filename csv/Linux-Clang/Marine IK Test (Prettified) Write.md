
----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 4852.59 | 0.11372 | 6110.1ms | 9930848 | 40 | 1.97041e+08 | 1.9517e+06 | 0.421159 | 0.510172 | 1(Win) | true |
| Glaze | 2815.24 | 0.488164 | 5022.82ms | 9930228 | 80 | 2.1573e+10 | 3.36391e+06 | 1.45827 | 0.879322 | 2(Loss) | true |
