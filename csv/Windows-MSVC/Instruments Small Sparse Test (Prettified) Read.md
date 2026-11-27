
----
### Instruments Small Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 5922.09 | 0.214962 | 129.174ms | 7932 | 1280 | 9650.48 | 1277.34 | 0.479351 | 0.505547 | 1(Win) | true |
| simdjson (ondemand) | 5225.94 | 0.388145 | 156.705ms | 7932 | 80 | 2525.32 | 1447.5 | 0 | 0.573347 | 2(Loss) | true |
