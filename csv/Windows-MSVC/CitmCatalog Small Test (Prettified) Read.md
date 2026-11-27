
----
### CitmCatalog Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/CitmCatalog%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1066.34 | 0.163404 | 889.055ms | 9739 | 40 | 8102.56 | 8710 | 0.0382555 | 2.84462 | 1(Win) | true |
| simdjson (ondemand) | 965.15 | 0.11196 | 967.932ms | 9739 | 1280 | 148586 | 9623.2 | 0.348683 | 3.14158 | 2(Loss) | true |
