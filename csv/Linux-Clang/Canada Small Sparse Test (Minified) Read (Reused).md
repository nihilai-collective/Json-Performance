
----
### Canada Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7778.43 | 0.109094 | 767.264ms | 4630 | 640 | 245.448 | 567.661 | 0.0129385 | 0.716695 | 3.59698 | 0.461987 | 0.000431965 | 2.83477e-05 | 1.51863e-05 | 1(Win) | true |
| simdjson (ondemand) | 6854.22 | 0.106517 | 773.782ms | 4630 | 1280 | 602.691 | 644.203 | 0.0138271 | 0.80881 | 4.0622 | 0.482506 | 0.000432472 | 2.59854e-05 | 9.28051e-06 | 2(Loss) | true |
