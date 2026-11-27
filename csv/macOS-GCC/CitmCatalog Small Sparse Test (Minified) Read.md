
----
### CitmCatalog Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/CitmCatalog%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3350.77 | 0.520423 | 149.683ms | 5092 | 4890 | 278170 | 1449.25 | 0.0101304 | 1(Win) | true |
| simdjson (ondemand) | 2938.86 | 0.463399 | 167.236ms | 5092 | 4890 | 286707 | 1652.38 | 0.436294 | 2(Loss) | true |
