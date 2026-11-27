
----
### Apache Builds Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2215.52 | 0.138036 | 148.299ms | 3370 | 640 | 2566.12 | 1450.62 | 0.0860956 | 1.35411 | 1(Win) | true |
| simdjson (ondemand) | 1874.88 | 0.107862 | 175.068ms | 3370 | 2560 | 8751.57 | 1714.18 | 0.106988 | 1.60427 | 2(Loss) | true |
