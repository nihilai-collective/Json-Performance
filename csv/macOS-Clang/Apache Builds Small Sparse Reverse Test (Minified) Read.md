
----
### Apache Builds Small Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1623.9 | 0.335705 | 161.737ms | 2632 | 4890 | 131667 | 1545.7 | 2.45526 | 1(Win) | true |
| simdjson (ondemand) | 1491.13 | 0.254366 | 182.786ms | 2632 | 30 | 550.023 | 1683.33 | 0.164627 | 2(Loss) | true |
