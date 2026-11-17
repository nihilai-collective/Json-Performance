
----
### Marine IK Reverse Test (Prettified) Write Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 5019.95 | 0.170141 | 5862.53ms | 9930848 | 30 | 3.09112e+08 | 1.88663e+06 | 0.384207 | 0.999003 | 3.39349 | 0.427912 | 0.000356307 | 0.0247486 | 0.000464388 | 1(Win) | true |
| Glaze | 3605.4 | 0.150537 | 8169.96ms | 9930228 | 160 | 2.5016e+09 | 2.62667e+06 | 0.377463 | 1.40008 | 4.21673 | 0.484712 | 0.00106741 | 0.0413034 | 0.00284833 | 2(Loss) | true |
