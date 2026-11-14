
----
### CitmCatalog Small Reverse Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 766.244 | 0.191742 | 1239.13ms | 9739 | 80 | 43213.6 | 12121.2 | 0.0103135 | 3.96028 | 1(Win) | true |
| simdjson (ondemand) | 574.359 | 0.0870107 | 1616.78ms | 9739 | 2560 | 506813 | 16170.8 | 0.214968 | 5.28356 | 2(Loss) | true |
