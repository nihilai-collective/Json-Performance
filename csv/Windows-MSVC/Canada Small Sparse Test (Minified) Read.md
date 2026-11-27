
----
### Canada Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 7165.13 | 0.236816 | 64.0282ms | 4630 | 640 | 1363.07 | 616.25 | 0.101523 | 0.41148 | 1(Win) | true |
| simdjson (ondemand) | 5146.24 | 0.176218 | 88.5562ms | 4630 | 2560 | 5852.22 | 858.008 | 0.159599 | 0.578278 | 2(Loss) | true |
