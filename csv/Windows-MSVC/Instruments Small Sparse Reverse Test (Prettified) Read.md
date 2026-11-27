
----
### Instruments Small Sparse Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Sparse%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4397.99 | 0.43185 | 179.284ms | 7932 | 30 | 1655.17 | 1720 | 0.578035 | 0.681644 | 1(Win) | true |
| simdjson (ondemand) | 3470.47 | 0.289782 | 229.204ms | 7932 | 640 | 25533.5 | 2179.69 | 0.157955 | 0.868225 | 2(Loss) | true |
