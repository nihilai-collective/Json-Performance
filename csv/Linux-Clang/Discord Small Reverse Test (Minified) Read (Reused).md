
----
### Discord Small Reverse Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Discord%20Small%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 858.488 | 0.0496906 | 1293.2ms | 4857 | 320 | 2300.21 | 5395.53 | 0.0222357 | 6.0471 | 26.6689 | 5.33189 | 0.00660451 | 2.38058e-05 | 6.43401e-07 | 1(Win) | true |
| simdjson (ondemand) | 228.096 | 0.0323134 | 2794.15ms | 4857 | 2560 | 110232 | 20307.2 | 0.108166 | 22.3629 | 113.403 | 21.7976 | 0.0430528 | 0.000132139 | 7.86558e-05 | 2(Loss) | true |
