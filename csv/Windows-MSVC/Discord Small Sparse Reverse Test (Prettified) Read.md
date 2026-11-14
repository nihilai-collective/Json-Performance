
----
### Discord Small Sparse Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2407.1 | 0.159437 | 269.089ms | 6701 | 4890 | 87614.7 | 2654.89 | 0.225802 | 1.25368 | 1(Win) | true |
| simdjson (ondemand) | 1971.18 | 0.156774 | 328.184ms | 6701 | 4890 | 126323 | 3242 | 0.210046 | 1.53347 | 2(Loss) | true |
