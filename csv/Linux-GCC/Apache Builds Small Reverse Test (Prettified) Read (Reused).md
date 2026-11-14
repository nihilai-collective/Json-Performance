
----
### Apache Builds Small Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Apache%20Builds%20Small%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1716.1 | 0.0648439 | 914.533ms | 3370 | 320 | 471.917 | 1872.79 | 0.0444054 | 3.06642 | 12.0148 | 2.28368 | 0.00388817 | 4.26558e-05 | 2.7819e-06 | 1(Win) | true |
| simdjson (ondemand) | 1011.94 | 0.130833 | 1045.38ms | 3370 | 40 | 690.64 | 3175.97 | 0.0643261 | 5.15512 | 21.6774 | 4.29021 | 0.00772997 | 1.48368e-05 | 0 | 2(Loss) | true |
