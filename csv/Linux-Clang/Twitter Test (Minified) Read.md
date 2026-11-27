
----
### Twitter Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 15635.4 | 0.0851149 | 3551.66ms | 466906 | 160 | 94009.4 | 28478.7 | 0.324029 | 0.32343 | 1.71062 | 0.11295 | 1.39482e-05 | 1.36537e-06 | 1.04411e-06 | 1(Win) | true |
| simdjson (stage-1) | 13926 | 0.100779 | 3930.16ms | 466906 | 40 | 41534.5 | 31974.5 | 0.015635 | 0.369981 | 1.74384 | 0.0739315 | 6.7626e-05 | 1.12442e-06 | 5.88984e-07 | 2(Loss) | true |
