
----
### Marine IK Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 6440.4 | 0.311177 | 278.222ms | 18245 | 4890 | 345610 | 2701.66 | 0.823619 | 1(Win) | true |
| simdjson (ondemand) | 5523.39 | 0.351655 | 334.524ms | 18245 | 1280 | 157079 | 3150.2 | 0.26098 | 2(Loss) | true |
