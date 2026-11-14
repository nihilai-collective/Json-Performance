
----
### Canada Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 6956.36 | 0.471235 | 160.829ms | 11579 | 4890 | 273629 | 1587.41 | 0.0825551 | 1(Win) | true |
| simdjson (ondemand) | 6121.17 | 0.488605 | 183.111ms | 11579 | 2560 | 198897 | 1804 | 0.022168 | 2(Loss) | true |
