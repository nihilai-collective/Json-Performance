
----
### Marine IK Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4878.81 | 0.845356 | 361.737ms | 18245 | 1280 | 1.16345e+06 | 3566.4 | 0.0224266 | 1(Win) | true |
| simdjson (ondemand) | 3881.11 | 0.524007 | 458.181ms | 18245 | 640 | 353207 | 4483.2 | 0.160342 | 2(Loss) | true |
