
----
### Twitter Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5179.79 | 0.153127 | 54.8296ms | 2821 | 4890 | 3093.1 | 519.387 | 1.84339 | 0.566254 | 1(Win) | true |
| simdjson (ondemand) | 3888.64 | 0.104032 | 71.2432ms | 2821 | 4890 | 2533.12 | 691.84 | 1.21795 | 0.760862 | 2(Loss) | true |
