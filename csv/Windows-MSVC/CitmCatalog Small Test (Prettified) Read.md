
----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1118.11 | 0.166051 | 512.414ms | 5839 | 4890 | 334425 | 4980.27 | 0.0761758 | 2.19501 | 1(Win) | true |
| Jsonifier | 1035.04 | 0.13769 | 555.213ms | 5839 | 160 | 8779.87 | 5380 | 0.0232288 | 2.37058 | 2(Loss) | true |
| Glaze | 752.324 | 0.143592 | 752.103ms | 5839 | 4890 | 552378 | 7401.74 | 0.0530662 | 3.27133 | 3(Loss) | true |
| simdjson (ondemand) | 744.849 | 0.225925 | 766.283ms | 5839 | 1280 | 365155 | 7476.02 | 0.0699666 | 3.31139 | 4(Loss) | true |
