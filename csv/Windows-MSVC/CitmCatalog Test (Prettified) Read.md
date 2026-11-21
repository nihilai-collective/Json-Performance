
----
### CitmCatalog Test (Prettified) Read Results [(View the data used in the following test)](./json/CitmCatalog%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/CitmCatalog%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2482.93 | 0.338207 | 5612.51ms | 1151920 | 30 | 6.71743e+07 | 442443 | 1.13915 | 0.997053 | 1(Win) | true |
| Jsonifier | 2271.96 | 0.153125 | 6531.57ms | 1151920 | 160 | 8.77116e+07 | 483528 | 0.183211 | 1.08965 | 2(Loss) | true |
| Glaze | 1427.38 | 0.208229 | 9810.07ms | 1151920 | 160 | 4.1093e+08 | 769629 | 0.768979 | 1.73444 | 3(Loss) | true |
| simdjson (ondemand) | 1409.7 | 0.234455 | 5162.33ms | 1151920 | 30 | 1.00146e+08 | 779283 | 1.88026 | 1.75618 | 4(Loss) | true |
