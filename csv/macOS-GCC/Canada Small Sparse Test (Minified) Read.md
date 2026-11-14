
----
### Canada Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4909.95 | 0.511597 | 92.2532ms | 4630 | 4890 | 103508 | 899.298 | 0.332688 | 1(Win) | true |
| simdjson (ondemand) | 4184.53 | 0.64048 | 108.714ms | 4630 | 1280 | 58464.2 | 1055.2 | 0.15186 | 2(Loss) | true |
