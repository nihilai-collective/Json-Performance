
----
### Instruments Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2023.06 | 0.0931555 | 8870.45ms | 183677 | 2560 | 1.66552e+07 | 86585.7 | 0.513011 | 1.22339 | 1(Win) | true |
| Jsonifier (two-stage) | 1784.33 | 0.660862 | 5016.6ms | 183677 | 40 | 1.6836e+07 | 98170 | 0.511928 | 1.38679 | 2(Loss) | true |
| Glaze | 1409.21 | 0.104551 | 6474.13ms | 183677 | 1280 | 2.16184e+07 | 124303 | 0.0710963 | 1.75652 | 3(Loss) | true |
| simdjson (ondemand) | 1382.72 | 0.142406 | 6532.53ms | 183677 | 640 | 2.08295e+07 | 126684 | 0.145875 | 1.79008 | 4(Loss) | true |
