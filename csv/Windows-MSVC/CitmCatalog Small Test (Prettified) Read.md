
----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1217.92 | 0.182915 | 465.785ms | 5839 | 4890 | 342015 | 4572.13 | 0.107291 | 2.01344 | 1(Win) | true |
| Jsonifier | 1087.33 | 0.192444 | 527.921ms | 5839 | 80 | 7770.57 | 5121.25 | 0.0244141 | 2.25517 | 2(Loss) | true |
| simdjson (ondemand) | 866.525 | 0.106293 | 658.717ms | 5839 | 80 | 3732.59 | 6426.25 | 0.174757 | 2.84394 | 3(Loss) | true |
| Glaze | 778.449 | 0.229592 | 732.342ms | 5839 | 30 | 8091.95 | 7153.33 | 0.1396 | 3.15599 | 4(Loss) | true |
