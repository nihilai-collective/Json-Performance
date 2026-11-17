
----
### Random Test (Prettified) Results [(View the data used in the following test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14500.9 | 0.0524327 | 5518.64ms | 728486 | 2560 | 1.61546e+06 | 47909.9 | 0.148172 | 0.34784 | 1.88741 | 0.0866016 | 0.000233667 | 3.87951e-06 | 3.38405e-06 | 1(Win) | true |
| simdjson (stage-1) | 13759.2 | 0.0218237 | 5785.75ms | 728486 | 4890 | 593777 | 50492.8 | 0.319456 | 0.371337 | 1.77437 | 0.0748814 | 5.63822e-06 | 1.16001e-05 | 3.94437e-06 | 2(Loss) | true |
