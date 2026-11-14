
----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5034.85 | 0.176727 | 5956.71ms | 9930848 | 30 | 3.31535e+08 | 1.88105e+06 | 0.183862 | 0.999385 | 3.38769 | 0.427912 | 0.000545757 | 0.0246516 | 0.000199755 | 1(Win) | true |
| Glaze | 3654.62 | 0.216658 | 8114.9ms | 9930228 | 80 | 2.52159e+09 | 2.5913e+06 | 0.0358901 | 1.38445 | 4.21673 | 0.484712 | 0.00107237 | 0.0413375 | 0.00329146 | 2(Loss) | true |
