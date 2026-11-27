
----
### Canada Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1870.99 | 0.248429 | 9425.81ms | 5212421 | 160 | 6.9704e+09 | 2.65685e+06 | 0.319736 | 2.70358 | 12.7285 | 2.34156 | 0.00982399 | 0.0906286 | 0.001077 | 1(Win) | true |
| simdjson (ondemand) | 1795.54 | 0.164748 | 9904.62ms | 5212421 | 40 | 8.32127e+08 | 2.7685e+06 | 0.189117 | 2.82941 | 13.0603 | 2.16862 | 0.00988567 | 0.110176 | 0.000340307 | 2(Loss) | true |
