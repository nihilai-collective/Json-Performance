
----
### Marine IK Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Marine%20IK%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1345.13 | 0.325979 | 7813.79ms | 7351818 | 40 | 1.15478e+10 | 5.21231e+06 | 0.975846 | 3.77718 | 16.6536 | 3.41596 | 0.0107985 | 0.186635 | 0.00708071 | 1(Win) | true |
| simdjson (ondemand) | 930.148 | 0.0980337 | 5296.4ms | 7351818 | 40 | 2.18422e+09 | 7.53777e+06 | 0.153446 | 5.50779 | 27.1972 | 5.33287 | 0.0118159 | 0.435952 | 0.000820729 | 2(Loss) | true |
