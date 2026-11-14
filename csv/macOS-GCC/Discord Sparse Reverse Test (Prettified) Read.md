
----
### Discord Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1901.81 | 0.0533186 | 4304.53ms | 83958 | 4890 | 2.46409e+06 | 42101.3 | 0.0221426 | 1(Win) | true |
| simdjson (ondemand) | 1445.62 | 0.0460593 | 5645.07ms | 83958 | 4890 | 3.18245e+06 | 55387.2 | 0.0263588 | 2(Loss) | true |
