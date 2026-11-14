
----
### Google Maps Response Small Sparse Test (Minified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1477.9 | 0.146756 | 323.705ms | 4390 | 80 | 1382.68 | 2832.82 | 0.420068 | 1(Win) | true |
| simdjson (ondemand) | 1304.18 | 0.181073 | 357.824ms | 4390 | 160 | 5406.12 | 3210.17 | 0.515664 | 2(Loss) | true |
