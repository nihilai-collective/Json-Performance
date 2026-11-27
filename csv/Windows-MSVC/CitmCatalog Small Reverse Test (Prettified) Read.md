
----
### CitmCatalog Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 744.736 | 0.0418584 | 1291.6ms | 9739 | 4890 | 133259 | 12471.3 | 0.0584511 | 4.07334 | 1(Win) | true |
| simdjson (ondemand) | 558.085 | 0.0857623 | 1674.89ms | 9739 | 1280 | 260754 | 16642.3 | 0.0441074 | 5.43866 | 2(Loss) | true |
