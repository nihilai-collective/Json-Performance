
----
### CitmCatalog Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2589.97 | 0.0826442 | 221.418ms | 5839 | 80 | 252.582 | 2150.03 | 0.220249 | 0.943267 | 1(Win) | true |
| Jsonifier | 2532.36 | 0.375238 | 227.329ms | 5839 | 80 | 5446.64 | 2198.94 | 0.25798 | 0.965576 | 2(Loss) | true |
| simdjson (reflection) | 2267.33 | 0.134076 | 252.723ms | 5839 | 40 | 433.717 | 2455.97 | 0.0701876 | 1.07989 | 3(Loss) | true |
| simdjson (ondemand) | 2238.66 | 0.163357 | 250.227ms | 5839 | 4890 | 80739.5 | 2487.42 | 0.325969 | 1.09362 | 4(Loss) | true |
| Glaze | 1863.4 | 0.284306 | 311.125ms | 5839 | 1280 | 92395 | 2988.36 | 0.0731495 | 1.31687 | 5(Loss) | true |
