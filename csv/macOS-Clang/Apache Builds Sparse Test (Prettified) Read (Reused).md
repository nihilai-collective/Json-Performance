
----
### Apache Builds Sparse Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2055.6 | 0.424841 | 5777.12ms | 124597 | 640 | 3.85986e+07 | 57805.5 | 1.40885 | 1(Win) | true |
| simdjson (ondemand) | 1733.1 | 1.26996 | 6960.1ms | 124597 | 80 | 6.0651e+07 | 68561.9 | 0.877448 | 2(Loss) | true |
