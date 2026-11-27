
----
### Instruments Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2678.9 | 0.2069 | 305.519ms | 7932 | 640 | 21845.1 | 2823.75 | 0.264901 | 1.1269 | 1(Win) | true |
| Jsonifier (two-stage) | 2339.25 | 0.128277 | 333.32ms | 7932 | 160 | 2753.14 | 3233.75 | 0.423403 | 1.29034 | 2(Loss) | true |
| Glaze | 1716.53 | 0.278714 | 460.757ms | 7932 | 1280 | 193104 | 4406.88 | 0.525518 | 1.76295 | 3(Loss) | true |
| simdjson (ondemand) | 1456.44 | 0.452972 | 529.953ms | 7932 | 4890 | 2.70664e+06 | 5193.84 | 0.41493 | 2.07806 | 4(Loss) | true |
