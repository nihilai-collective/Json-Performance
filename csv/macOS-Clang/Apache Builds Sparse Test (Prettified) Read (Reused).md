
----
### Apache Builds Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2642.43 | 0.102151 | 5211.85ms | 124597 | 1280 | 2.70089e+06 | 44968.1 | 0.0781146 | 1(Win) | true |
| simdjson (ondemand) | 2049.53 | 0.318534 | 6442.84ms | 124597 | 80 | 2.72839e+06 | 57976.6 | 0.097937 | 2(Loss) | true |
