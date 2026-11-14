
----
### Canada Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3623.48 | 1.37577 | 7050.13ms | 2090234 | 30 | 1.71851e+09 | 550135 | 1.44916 | 1(Win) | true |
| simdjson (ondemand) DID NOT CONVERGE | 3328.82 | 0.384546 | 7757.63ms | 2090234 | 160 | 8.48449e+08 | 598832 | 7.27204 | -(Loss) | false |
