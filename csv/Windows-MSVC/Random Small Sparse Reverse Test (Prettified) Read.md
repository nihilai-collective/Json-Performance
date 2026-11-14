
----
### Random Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Random%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1670.92 | 0.166147 | 468.036ms | 8150 | 2560 | 152909 | 4651.6 | 0.0293831 | 1.8115 | 1(Win) | true |
| simdjson (ondemand) | 1546.84 | 0.181726 | 509.742ms | 8150 | 2560 | 213452 | 5024.73 | 0.309585 | 1.95709 | 2(Loss) | true |
