
----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 817.064 | 0.137174 | 383.029ms | 3223 | 160 | 4260.61 | 3761.88 | 0.0830013 | 3.6966 | 1(Win) | true |
| Jsonifier (two-stage) | 686.865 | 0.0909118 | 451.957ms | 3223 | 2560 | 42370.1 | 4474.96 | 0.107253 | 4.40191 | 2(Loss) | true |
| Glaze | 599.992 | 0.125434 | 519.134ms | 3223 | 1280 | 52853.2 | 5122.89 | 0.010674 | 5.0455 | 3(Loss) | true |
| simdjson (ondemand) | 482.905 | 0.150827 | 639.274ms | 3223 | 320 | 29492.2 | 6365 | 0.0294493 | 6.27566 | 4(Loss) | true |
