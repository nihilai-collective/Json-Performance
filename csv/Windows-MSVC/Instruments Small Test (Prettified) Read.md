
----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2336.54 | 0.121711 | 329.791ms | 7932 | 160 | 2484.28 | 3237.5 | 0.115964 | 1.29322 | 1(Win) | true |
| Jsonifier | 2129.36 | 0.158154 | 362.379ms | 7932 | 80 | 2525.32 | 3552.5 | 0.210674 | 1.42391 | 2(Loss) | true |
| Glaze | 1707.57 | 0.130049 | 444.464ms | 7932 | 2560 | 84969.1 | 4430 | 0.130332 | 1.77179 | 3(Loss) | true |
| simdjson (ondemand) | 1402.28 | 0.0679541 | 543.432ms | 7932 | 4890 | 65710.7 | 5394.46 | 0.103023 | 2.15941 | 4(Loss) | true |
