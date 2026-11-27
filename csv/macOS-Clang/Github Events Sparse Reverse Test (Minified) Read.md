
----
### Github Events Sparse Reverse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4258.08 | 0.0482791 | 1208.75ms | 53331 | 30 | 997.633 | 11944.4 | 0.197748 | 1(Win) | true |
| simdjson (ondemand) | 2661.99 | 0.209461 | 1967.62ms | 53331 | 1280 | 2.05004e+06 | 19106.1 | 0.161272 | 2(Loss) | true |
