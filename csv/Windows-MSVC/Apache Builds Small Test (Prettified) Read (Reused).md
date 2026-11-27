
----
### Apache Builds Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1745.49 | 0.212034 | 217.462ms | 3370 | 160 | 2438.68 | 1841.25 | 0.135593 | 1.39637 | 1(Win) | true |
| Glaze | 1722.11 | 0.285067 | 219.635ms | 3370 | 80 | 2264.24 | 1866.25 | 0.333778 | 1.4163 | 2(Loss) | true |
| Jsonifier (two-stage) | 1624.15 | 0.260381 | 229.108ms | 3370 | 4890 | 129819 | 1978.81 | 0.111141 | 1.50132 | 3(Loss) | true |
| simdjson (ondemand) | 1080.89 | 0.499421 | 344.221ms | 3370 | 1280 | 282253 | 2973.36 | 0.118377 | 2.26849 | 4(Loss) | true |
