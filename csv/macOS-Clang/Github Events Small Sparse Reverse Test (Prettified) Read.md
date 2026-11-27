
----
### Github Events Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3184.08 | 0.255523 | 68.1473ms | 2158 | 160 | 436.43 | 646.35 | 0.164655 | 1(Win) | true |
| simdjson (ondemand) | 2073.22 | 0.494851 | 100.474ms | 2158 | 2560 | 61773.5 | 992.674 | 0.389232 | 2(Loss) | true |
