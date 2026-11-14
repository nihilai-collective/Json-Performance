
----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1584.35 | 0.176676 | 697.175ms | 11579 | 2560 | 388184 | 6969.8 | 0.641501 | 1(Win) | true |
| Jsonifier (two-stage) | 1529.11 | 0.339987 | 768.784ms | 11579 | 320 | 192904 | 7221.6 | 0.210924 | 2(Loss) | true |
| simdjson (reflection) | 1210.1 | 0.217171 | 929.132ms | 11579 | 4890 | 1.92048e+06 | 9125.33 | 1.60206 | 3(Loss) | true |
| Glaze | 1048.93 | 0.141374 | 1072.68ms | 11579 | 2560 | 567063 | 10527.5 | 0.0484211 | 4(Loss) | true |
| simdjson (ondemand) | 965.411 | 0.283095 | 1165.57ms | 11579 | 4890 | 5.12732e+06 | 11438.2 | 2.95711 | 5(Loss) | true |
