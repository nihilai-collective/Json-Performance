
----
### Google Maps Response Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1469.85 | 0.382439 | 795.746ms | 11812 | 320 | 274902 | 7663.93 | 0.222058 | 1(Win) | true |
| simdjson (ondemand) | 1213.43 | 0.969399 | 940.624ms | 11812 | 30 | 242963 | 9283.4 | 0.105676 | 2(Loss) | true |
