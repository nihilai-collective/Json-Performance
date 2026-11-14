
----
### Marine IK Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1153.94 | 0.31162 | 9645.7ms | 1834197 | 160 | 3.57021e+09 | 1.51587e+06 | 1.21036 | 4.36269 | 12.5596 | 0.909504 | 0.00138702 | 0.0596734 | 0.000263146 | 1(Win) | true |
| Glaze | 656.216 | 0.372778 | 8390.82ms | 1833577 | 30 | 2.96024e+09 | 2.66473e+06 | 0.556393 | 7.7086 | 16.0106 | 0.996384 | 0.000999031 | 0.0492379 | 0.00049488 | 2(Loss) | true |
