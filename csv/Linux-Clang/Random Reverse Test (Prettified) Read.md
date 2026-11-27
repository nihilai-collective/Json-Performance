
----
### Random Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1258.58 | 0.112116 | 6676.74ms | 676745 | 320 | 1.05772e+08 | 512795 | 0.364404 | 4.04554 | 18.2038 | 3.67752 | 0.00890404 | 0.024664 | 1.31512e-05 | 1(Win) | true |
| simdjson (ondemand) | 728.879 | 0.060111 | 5630.12ms | 676745 | 320 | 9.0656e+07 | 885461 | 0.212687 | 6.94917 | 30.8713 | 5.5912 | 0.0228554 | 0.0402431 | 0.00019984 | 2(Loss) | true |
