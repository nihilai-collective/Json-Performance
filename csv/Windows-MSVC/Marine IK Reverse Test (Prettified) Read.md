
----
### Marine IK Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2197.36 | 0.115854 | 10084.4ms | 7351818 | 40 | 5.46596e+08 | 3.19075e+06 | 0.180925 | 1.12671 | 1(Win) | true |
| Jsonifier | 2120.84 | 0.168124 | 10164.9ms | 7351818 | 160 | 4.94257e+09 | 3.30588e+06 | 2.40343 | 1.16736 | 2(Loss) | true |
| Glaze | 697.513 | 0.574739 | 7246.61ms | 7351818 | 30 | 1.00126e+11 | 1.00518e+07 | 0.00736135 | 3.54948 | 3(Loss) | true |
| simdjson (ondemand) DID NOT CONVERGE | 494.023 | 1.68835 | 9996.24ms | 7351818 | 30 | 1.72244e+12 | 1.41921e+07 | 2.77119 | 5.01149 | -(Loss) | false |
