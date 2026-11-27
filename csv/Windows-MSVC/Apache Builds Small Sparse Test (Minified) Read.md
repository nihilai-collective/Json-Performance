
----
### Apache Builds Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1799.94 | 0.107018 | 142.744ms | 2632 | 640 | 1425.45 | 1394.53 | 0.325989 | 1.67026 | 1(Win) | true |
| simdjson (ondemand) | 1490.76 | 0.136029 | 174.459ms | 2632 | 320 | 1678.68 | 1683.75 | 0.259163 | 2.01463 | 2(Loss) | true |
