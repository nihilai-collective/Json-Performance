
----
### Random Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Random%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Random%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1767.92 | 0.276422 | 6387.88ms | 409725 | 1280 | 4.77766e+08 | 221019 | 1.20125 | 1(Win) | true |
| simdjson (ondemand) | 1163.28 | 1.36054 | 8848.87ms | 409725 | 30 | 6.26564e+08 | 335900 | 2.28465 | 2(Loss) | true |
