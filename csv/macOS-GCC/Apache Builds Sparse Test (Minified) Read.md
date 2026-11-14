
----
### Apache Builds Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1464.88 | 0.275021 | 6121.56ms | 94653 | 320 | 9.19065e+06 | 61621.6 | 0.587233 | 1(Win) | true |
| simdjson (ondemand) | 1087.95 | 0.062033 | 8582.68ms | 94653 | 2560 | 6.78162e+06 | 82970.5 | 0.0519732 | 2(Loss) | true |
