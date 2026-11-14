
----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2963.13 | 0.0838878 | 844.736ms | 3770 | 160 | 165.767 | 1213.36 | 0.00824224 | 1.79772 | 6.90743 | 1.16764 | 0.000268568 | 3.97878e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 2763.17 | 0.0488455 | 853.738ms | 3770 | 2560 | 1034.09 | 1301.17 | 0.0666023 | 1.92268 | 7.47427 | 1.08912 | 0.000266599 | 5.15998e-05 | 1.32626e-05 | 2(Loss) | true |
