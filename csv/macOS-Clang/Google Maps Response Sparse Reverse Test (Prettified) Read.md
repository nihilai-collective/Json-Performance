
----
### Google Maps Response Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 2380.08 | 0.177197 | 1028.28ms | 25388 | 640 | 207953 | 10172.7 | 0.0519274 | 1(Win) | true |
| simdjson (ondemand) | 2285.17 | 0.0614377 | 1074.82ms | 25388 | 80 | 3389.85 | 10595.2 | 0.0916346 | 2(Loss) | true |
