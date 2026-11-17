
----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2571.66 | 0.0926356 | 5443.09ms | 1151920 | 320 | 5.01098e+07 | 427178 | 0.131943 | 1.18173 | 1(Win) | true |
| Jsonifier | 2329.06 | 0.0469882 | 6024.94ms | 1151920 | 640 | 3.14369e+07 | 471673 | 0.0234483 | 1.30486 | 2(Loss) | true |
| Glaze | 1517.91 | 0.205844 | 9205.69ms | 1151920 | 40 | 8.8775e+07 | 723730 | 0.0138154 | 2.00227 | 3(Loss) | true |
| simdjson (ondemand) | 1198.38 | 0.12097 | 5822.96ms | 1151920 | 160 | 1.96758e+08 | 916702 | 0.00852167 | 2.53608 | 4(Loss) | true |
