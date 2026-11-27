
----
### Instruments Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3632.78 | 0.0713046 | 214.583ms | 7932 | 80 | 176.365 | 2082.3 | 0.00120058 | 1(Win) | true |
| simdjson (ondemand) | 2734.32 | 0.121586 | 284.203ms | 7932 | 2560 | 28964.9 | 2766.51 | 0.0194109 | 2(Loss) | true |
