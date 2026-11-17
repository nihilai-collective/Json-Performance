
----
### Marine IK Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 663.076 | 0.11668 | 8986.6ms | 1834197 | 80 | 7.57968e+08 | 2.63805e+06 | 0.114956 | 7.67816 | 32.2698 | 6.69537 | 0.0369107 | 0.118546 | 0.00500286 | 1(Win) | true |
| simdjson (ondemand) | 619.059 | 0.137231 | 9547.35ms | 1834197 | 40 | 6.0144e+08 | 2.82562e+06 | 0.0294948 | 8.1664 | 34.2314 | 5.66128 | 0.0436012 | 0.118117 | 0.0108664 | 2(Loss) | true |
