
----
### Github Events Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3819.7 | 0.168012 | 55.516ms | 2158 | 4890 | 4007.13 | 538.793 | 0.974469 | 0.768939 | 1(Win) | true |
| simdjson (ondemand) | 3683.27 | 0.698715 | 58.7259ms | 2158 | 160 | 2438.68 | 558.75 | 1.10619 | 0.800348 | 2(Loss) | true |
