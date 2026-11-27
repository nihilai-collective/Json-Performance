
----
### Twitter Sparse Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Sparse%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5211.46 | 0.0338058 | 5632.31ms | 264040 | 4890 | 1.30471e+06 | 48318.2 | 0.0298925 | 0.972116 | 5.09516 | 0.854428 | 0.00173973 | 1.08298e-05 | 8.50478e-06 | 1(Win) | true |
| simdjson (ondemand) | 3942.52 | 0.031156 | 7195.85ms | 264040 | 4890 | 1.93635e+06 | 63869.8 | 0.0244209 | 1.28059 | 6.29742 | 0.918039 | 0.00179925 | 1.38465e-05 | 1.13317e-05 | 2(Loss) | true |
