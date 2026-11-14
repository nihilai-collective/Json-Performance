
----
### Apache Builds Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1863.27 | 0.269458 | 5197.6ms | 94653 | 320 | 5.45322e+06 | 48446.2 | 0.29558 | 1(Win) | true |
| simdjson (ondemand) | 1031.95 | 0.782383 | 7165.61ms | 94653 | 160 | 7.4939e+07 | 87473.1 | 0.0456289 | 2(Loss) | true |
