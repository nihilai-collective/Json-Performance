
----
### CitmCatalog Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 18941 | 0.215002 | 5817.74ms | 1151920 | 1280 | 1.99036e+07 | 57998.8 | 0.415385 | 0.130643 | 1(Win) | true |
| simdjson (stage-1) | 17637.3 | 0.142858 | 6293.79ms | 1151920 | 2560 | 2.02689e+07 | 62286 | 0.153665 | 0.140298 | 2(Loss) | true |
