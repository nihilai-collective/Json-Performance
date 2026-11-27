
----
### Random Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1484.22 | 0.117264 | 6663.66ms | 409725 | 1280 | 1.21991e+08 | 263266 | 0.475177 | 1.66776 | 1(Win) | true |
| simdjson (ondemand) | 1116.9 | 0.688483 | 8813.94ms | 409725 | 320 | 1.85651e+09 | 349848 | 0.116967 | 2.21645 | 2(Loss) | true |
