
----
### Google Maps Response Sparse Reverse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1166.29 | 0.178855 | 979.66ms | 11812 | 4890 | 1.45931e+06 | 9658.68 | 0.65181 | 1(Win) | true |
| simdjson (ondemand) | 1042.43 | 0.0586303 | 1145.19ms | 11812 | 80 | 3211.33 | 10806.2 | 0.0767485 | 2(Loss) | true |
