
----
### CitmCatalog Small Test (Minified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 883.905 | 0.0709173 | 349.946ms | 3223 | 4890 | 29738.8 | 3477.4 | 0.197859 | 3.42004 | 1(Win) | true |
| Jsonifier (two-stage) | 750.21 | 0.113976 | 415.004ms | 3223 | 1280 | 27911.9 | 4097.11 | 0.199817 | 4.02971 | 2(Loss) | true |
| Glaze | 662.813 | 0.191219 | 467.886ms | 3223 | 640 | 50324.7 | 4637.34 | 0.0505153 | 4.56322 | 3(Loss) | true |
| simdjson (ondemand) | 560.981 | 0.151129 | 553.869ms | 3223 | 1280 | 87766.3 | 5479.14 | 0.350561 | 5.39669 | 4(Loss) | true |
