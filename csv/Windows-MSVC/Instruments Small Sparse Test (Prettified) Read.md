
----
### Instruments Small Sparse Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 5089.69 | 0.181386 | 150.438ms | 7932 | 1280 | 9302.58 | 1486.25 | 0.0947069 | 0.588969 | 1(Win) | true |
| Jsonifier (generic) | 5040.93 | 0.16178 | 156.198ms | 7932 | 160 | 943.003 | 1500.62 | 0.125104 | 0.596041 | 2(Loss) | true |
