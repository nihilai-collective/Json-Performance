
----
### Marine IK Reverse Test (Minified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1164.6 | 0.0204159 | 9503.36ms | 1834197 | 320 | 3.009e+07 | 1.502e+06 | 0.00729206 | 4.33772 | 12.5783 | 0.909542 | 0.00132829 | 0.0593593 | 8.22584e-05 | 1(Win) | true |
| Glaze | 643.267 | 0.117703 | 8433.64ms | 1833577 | 160 | 1.638e+09 | 2.71837e+06 | 0.109838 | 7.86827 | 16.012 | 0.996538 | 0.00113379 | 0.0494162 | 0.000446624 | 2(Loss) | true |
