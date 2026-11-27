
----
### Google Maps Response Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1405.22 | 0.299727 | 801.447ms | 11812 | 640 | 369480 | 8016.41 | 0.0370471 | 2.15755 | 1(Win) | true |
| simdjson (ondemand) | 1164.69 | 0.216368 | 974.153ms | 11812 | 1280 | 560565 | 9671.95 | 0.0703235 | 2.60323 | 2(Loss) | true |
