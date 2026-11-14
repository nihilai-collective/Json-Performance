
----
### CitmCatalog Small Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1327.61 | 0.319368 | 426.243ms | 5839 | 160 | 28710.3 | 4194.38 | 0.0149031 | 2.27901 | 1(Win) | true |
| Jsonifier | 1183.43 | 0.0870528 | 473.049ms | 5839 | 4890 | 82047.2 | 4705.38 | 0.12525 | 2.55607 | 2(Loss) | true |
| Glaze | 1015.35 | 0.0873522 | 550.66ms | 5839 | 2560 | 58752.9 | 5484.3 | 0.0484103 | 2.98245 | 3(Loss) | true |
| simdjson (ondemand) | 978.218 | 0.149136 | 576.531ms | 5839 | 80 | 5765.82 | 5692.5 | 0.175362 | 3.09657 | 4(Loss) | true |
