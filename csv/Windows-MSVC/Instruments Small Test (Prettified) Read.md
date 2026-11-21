
----
### Instruments Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1818.4 | 0.272745 | 432.63ms | 7932 | 30 | 3862.07 | 4160 | 0 | 1.3555 | 1(Win) | true |
| Jsonifier | 1590.39 | 0.175696 | 508.383ms | 7932 | 4890 | 341502 | 4756.42 | 0.00195829 | 1.54826 | 2(Loss) | true |
| simdjson (ondemand) | 1353.93 | 0.252361 | 578.791ms | 7932 | 2560 | 508931 | 5587.11 | 0.262169 | 1.82004 | 3(Loss) | true |
| Glaze | 1319.01 | 0.0935715 | 590.457ms | 7932 | 80 | 2303.8 | 5735 | 0.043573 | 1.86875 | 4(Loss) | true |
