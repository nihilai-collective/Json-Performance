
----
### Github Events Small Sparse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Sparse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3733.2 | 0.102847 | 46.6519ms | 1691 | 4890 | 965.206 | 431.979 | 0.210918 | 1(Win) | true |
| simdjson (ondemand) | 3373.24 | 0.210959 | 51.5561ms | 1691 | 640 | 650.983 | 478.075 | 0.142948 | 2(Loss) | true |
