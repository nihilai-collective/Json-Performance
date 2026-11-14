
----
### Apache Builds Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2556.61 | 0.324814 | 5818.65ms | 124597 | 320 | 7.29301e+06 | 46477.6 | 0.845339 | 1(Win) | true |
| simdjson (ondemand) | 1730.58 | 0.125964 | 7886.21ms | 124597 | 2560 | 1.91499e+07 | 68662 | 0.212765 | 2(Loss) | true |
