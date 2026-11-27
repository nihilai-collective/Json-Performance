
----
### Apache Builds Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2037.36 | 0.0623963 | 6072ms | 124597 | 4890 | 6.47596e+06 | 58322.9 | 0.627811 | 1(Win) | true |
| simdjson (ondemand) | 1355.72 | 0.165821 | 8716.65ms | 124597 | 1280 | 2.70376e+07 | 87647.2 | 0.0182583 | 2(Loss) | true |
