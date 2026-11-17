
----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2880.89 | 0.0816602 | 840.285ms | 3370 | 160 | 132.785 | 1115.59 | 0 | 1.85357 | 7.52255 | 1.28457 | 0.000602745 | 5.93472e-05 | 1.8546e-06 | 1(Win) | true |
| simdjson (ondemand) | 2392.24 | 0.0482377 | 862.283ms | 3370 | 2560 | 1075.13 | 1343.46 | 0.0480687 | 2.21956 | 8.40861 | 1.35846 | 0.00124073 | 3.74397e-05 | 1.06639e-05 | 2(Loss) | true |
