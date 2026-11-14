
----
### Canada Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4932.43 | 0.981368 | 93.5501ms | 4630 | 1280 | 98790.1 | 895.2 | 0.400534 | 1(Win) | true |
| simdjson (ondemand) | 4228.58 | 0.307273 | 107.108ms | 4630 | 4890 | 50342.1 | 1044.21 | 0.171341 | 2(Loss) | true |
