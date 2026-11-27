
----
### Apache Builds Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1623.69 | 0.141351 | 202.336ms | 3370 | 1280 | 10019.9 | 1979.38 | 0.126462 | 1.85473 | 1(Win) | true |
| Jsonifier (two-stage) | 1550.73 | 0.191088 | 213.874ms | 3370 | 160 | 2509.43 | 2072.5 | 0 | 1.95017 | 2(Loss) | true |
| Glaze | 1149.74 | 0.22686 | 286.371ms | 3370 | 640 | 25737 | 2795.31 | 0.291513 | 2.6265 | 3(Loss) | true |
| simdjson (ondemand) | 1047.41 | 0.248453 | 308.337ms | 3370 | 2560 | 148782 | 3068.4 | 0.154278 | 2.88052 | 4(Loss) | true |
