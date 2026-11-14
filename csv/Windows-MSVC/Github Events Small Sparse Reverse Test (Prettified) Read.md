
----
### Github Events Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Github%20Events%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2772.46 | 0.145101 | 75.9336ms | 2158 | 4890 | 5673.12 | 742.311 | 0.230181 | 1.06958 | 1(Win) | true |
| simdjson (ondemand) | 2336.39 | 0.118318 | 89.3466ms | 2158 | 4890 | 5311.6 | 880.859 | 0.23895 | 1.27488 | 2(Loss) | true |
