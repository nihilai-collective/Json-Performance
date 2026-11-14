
----
### Marine IK Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Marine%20IK%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 1270.01 | 0.103474 | 8741ms | 1834197 | 30 | 6.09338e+07 | 1.37733e+06 | 0.115409 | 3.97539 | 13.1197 | 0.79904 | 0.00299713 | 0.061835 | 7.56007e-05 | 1(Win) | true |
| Glaze | 1006.91 | 0.264785 | 5418.86ms | 1833577 | 160 | 3.38317e+09 | 1.73663e+06 | 0.286461 | 5.01117 | 16.0427 | 1.0527 | 0.00100195 | 0.0495036 | 1.17223e-05 | 2(Loss) | true |
| simdjson (reflection) | 890.417 | 0.0101982 | 6409.5ms | 1922245 | 40 | 1.76333e+06 | 2.05881e+06 | 0.0270298 | 5.67228 | 18.1619 | 2.01848 | 0.0244728 | 0.0519406 | 6.08403e-05 | 3(Loss) | true |
