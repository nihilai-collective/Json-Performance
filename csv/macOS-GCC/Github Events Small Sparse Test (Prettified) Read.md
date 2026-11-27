
----
### Github Events Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3979.17 | 1.92096 | 57.5229ms | 2158 | 2560 | 252692 | 517.2 | 1.78504 | 1(Win) | true |
| simdjson (ondemand) | 3378.25 | 1.59611 | 70.0621ms | 2158 | 2560 | 242039 | 609.2 | 0.684708 | 2(Loss) | true |
