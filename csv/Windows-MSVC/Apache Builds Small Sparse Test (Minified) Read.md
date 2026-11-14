
----
### Apache Builds Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1733.32 | 0.287001 | 148.903ms | 2632 | 160 | 2763.76 | 1448.12 | 0.215332 | 1.72487 | 1(Win) | true |
| simdjson (ondemand) | 1502.45 | 0.215436 | 170.139ms | 2632 | 4890 | 63346.1 | 1670.65 | 0.478686 | 2.00117 | 2(Loss) | true |
