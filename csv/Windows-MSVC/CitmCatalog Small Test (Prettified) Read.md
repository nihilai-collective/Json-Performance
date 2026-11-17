
----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1199.34 | 0.15605 | 466.943ms | 5839 | 640 | 33596.8 | 4642.97 | 0.0840619 | 2.52082 | 1(Win) | true |
| Jsonifier | 1096.46 | 0.0988395 | 509.156ms | 5839 | 4890 | 123215 | 5078.63 | 0.0361051 | 2.7588 | 2(Loss) | true |
| Glaze | 922.803 | 0.0590147 | 608.801ms | 5839 | 4890 | 62013.7 | 6034.34 | 0.0588823 | 3.28286 | 3(Loss) | true |
| simdjson (ondemand) | 847.996 | 0.197725 | 662.231ms | 5839 | 30 | 5057.47 | 6566.67 | 0.152053 | 3.57534 | 4(Loss) | true |
