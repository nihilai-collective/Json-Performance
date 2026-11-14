
----
### Apache Builds Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1488.52 | 0.239493 | 6258.74ms | 94653 | 320 | 6.74982e+06 | 60642.7 | 0.217642 | 1(Win) | true |
| simdjson (ondemand) | 1088.14 | 0.412435 | 8716.19ms | 94653 | 640 | 7.49183e+07 | 82956.1 | 0.511678 | 2(Loss) | true |
