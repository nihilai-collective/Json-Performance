
----
### Marine IK Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5049.42 | 0.0620756 | 5862.17ms | 9930848 | 40 | 5.42241e+07 | 1.87562e+06 | 0.0950195 | 0.998533 | 3.40486 | 0.427912 | 0.000506452 | 0.0247348 | 0.000810034 | 1(Win) | true |
| Glaze | 2890.3 | 0.46527 | 10167.5ms | 9930228 | 40 | 9.29612e+09 | 3.27654e+06 | 0.13559 | 1.73817 | 4.21669 | 0.484737 | 0.00104552 | 0.0752967 | 0.0198649 | 2(Loss) | true |
