
----
### Marine IK Small Sparse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Marine%20IK%20Small%20Sparse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 6459.32 | 0.048135 | 273.965ms | 18245 | 320 | 538.006 | 2693.75 | 0.00951367 | 1(Win) | true |
| simdjson (ondemand) | 6242.94 | 0.111037 | 285.682ms | 18245 | 2560 | 24517.9 | 2787.12 | 0.121058 | 2(Loss) | true |
