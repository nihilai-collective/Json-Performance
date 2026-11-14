
----
### Instruments Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5131.48 | 0.0435799 | 3432.23ms | 183677 | 4890 | 1.0822e+06 | 34136 | 0.0823385 | 0.591823 | 1(Win) | true |
| simdjson (ondemand) | 4763.64 | 0.289459 | 3676.42ms | 183677 | 640 | 7.25079e+06 | 36771.9 | 0.00424935 | 0.637543 | 2(Loss) | true |
