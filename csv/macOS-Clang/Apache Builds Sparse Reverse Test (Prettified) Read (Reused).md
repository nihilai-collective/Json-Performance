
----
### Apache Builds Sparse Reverse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2078.97 | 0.0477755 | 6563.86ms | 124597 | 30 | 22369.2 | 57155.7 | 0.102457 | 1(Win) | true |
| simdjson (ondemand) | 1692.25 | 0.172854 | 7560.97ms | 124597 | 320 | 4.71407e+06 | 70217.2 | 0.0701843 | 2(Loss) | true |
