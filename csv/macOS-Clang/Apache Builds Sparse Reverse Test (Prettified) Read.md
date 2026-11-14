
----
### Apache Builds Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Apache%20Builds%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1834.4 | 0.135319 | 6703.11ms | 124597 | 1280 | 9.8345e+06 | 64775.8 | 0.597036 | 1(Win) | true |
| simdjson (ondemand) | 1533.69 | 0.32247 | 7943.83ms | 124597 | 160 | 9.98706e+06 | 77476.3 | 0.26731 | 2(Loss) | true |
