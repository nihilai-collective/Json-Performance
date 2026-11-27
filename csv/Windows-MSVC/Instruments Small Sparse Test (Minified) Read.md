
----
### Instruments Small Sparse Test (Minified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Sparse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Sparse%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 4014.84 | 0.38733 | 121.257ms | 4669 | 320 | 5905.07 | 1109.06 | 0.31091 | 0.746281 | 1(Win) | true |
| simdjson (ondemand) | 3536.52 | 0.224243 | 138.602ms | 4669 | 320 | 2550.84 | 1259.06 | 1.333 | 0.846825 | 2(Loss) | true |
