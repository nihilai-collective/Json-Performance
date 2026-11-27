
----
### Marine IK Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 6112.91 | 0.694556 | 283.433ms | 18245 | 640 | 250142 | 2846.4 | 0.112296 | 1(Win) | true |
| simdjson (ondemand) | 5328.21 | 0.232867 | 329.673ms | 18245 | 4890 | 282780 | 3265.6 | 0.0613071 | 2(Loss) | true |
