
----
### Apache Builds Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2486.78 | 0.106382 | 105.534ms | 2632 | 320 | 368.966 | 1009.37 | 0.103203 | 1(Win) | true |
| simdjson (ondemand) | 1828.59 | 0.0844943 | 141.613ms | 2632 | 320 | 430.47 | 1372.68 | 0.0939341 | 2(Loss) | true |
