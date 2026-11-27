
----
### Stream Formats Large Test (NDJSON) Read Results [(Here is the data we used for this test)](./json/Stream%20Formats%20Large%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Stream%20Formats%20Large%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 10122 | 0.388561 | 9883.57ms | 16197086 | 40 | 1.40643e+09 | 1.52605e+06 | 1.10327 | 1(Win) | true |
| simdjson (ondemand) | 8663.03 | 0.155873 | 5922.47ms | 16197086 | 30 | 2.31737e+08 | 1.78307e+06 | 0.186297 | 2(Loss) | true |
