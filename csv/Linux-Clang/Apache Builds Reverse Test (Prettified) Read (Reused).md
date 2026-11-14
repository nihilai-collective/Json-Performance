
----
### Apache Builds Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1846.55 | 0.0220077 | 8393.46ms | 124597 | 2560 | 513427 | 64349.6 | 0.223483 | 2.74939 | 13.6237 | 2.63462 | 0.00597345 | 2.95014e-06 | 4.89077e-07 | 1(Win) | true |
| simdjson (ondemand) | 1099.95 | 0.0241752 | 6507.1ms | 124597 | 2560 | 1.74603e+06 | 108028 | 0.0897984 | 4.62346 | 23.7486 | 4.65715 | 0.00697834 | 7.53053e-06 | 2.80592e-06 | 2(Loss) | true |
