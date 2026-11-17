
----
### Marine IK Test (Minified) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 8734.73 | 0.0538499 | 5325.13ms | 1834197 | 1280 | 1.48858e+07 | 200261 | 0.101844 | 0.579054 | 2.89621 | 0.126786 | 0.00180264 | 0.0377712 | 2.35372e-06 | 1(Win) | true |
| simdjson (stage-1) | 7031.72 | 0.234994 | 6635.15ms | 1834197 | 80 | 2.73384e+07 | 248762 | 0.544332 | 0.727565 | 3.29419 | 0.16035 | 0.00494528 | 0.0376839 | 1.79915e-06 | 2(Loss) | true |
