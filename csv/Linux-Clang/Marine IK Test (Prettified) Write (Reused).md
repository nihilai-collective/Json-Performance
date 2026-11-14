
----
### Marine IK Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5023.78 | 0.0680537 | 5875.76ms | 9930848 | 80 | 1.31676e+08 | 1.88519e+06 | 0.0943237 | 1.00509 | 3.40689 | 0.427905 | 0.00051521 | 0.0246522 | 0.00111161 | 1(Win) | true |
| Glaze | 4075.12 | 0.0943429 | 7275.85ms | 9930228 | 160 | 7.69088e+08 | 2.32391e+06 | 0.157139 | 1.24032 | 4.21632 | 0.484654 | 0.00108185 | 0.0220135 | 0.00192174 | 2(Loss) | true |
