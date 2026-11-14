
----
### Marine IK Sparse Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Marine%20IK%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 4341.11 | 0.760309 | 5012.85ms | 7351818 | 80 | 1.20631e+10 | 1.61508e+06 | 1.28056 | 1(Win) | true |
| simdjson (ondemand) | 3486.08 | 0.629373 | 6243.2ms | 7351818 | 160 | 2.56361e+10 | 2.01121e+06 | 1.13105 | 2(Loss) | true |
