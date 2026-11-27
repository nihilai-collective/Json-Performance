
----
### Random Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Random%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1542.75 | 0.0899287 | 5827.5ms | 728486 | 640 | 1.0496e+08 | 450324 | 0.248884 | 1(Win) | true |
| Jsonifier (two-stage) | 1367.63 | 0.13332 | 6693.35ms | 728486 | 80 | 3.66932e+07 | 507987 | 0.174816 | 2(Loss) | true |
| simdjson (reflection) | 1205.77 | 0.116083 | 7358.63ms | 728486 | 640 | 2.86309e+08 | 576178 | 0.241562 | 3(Loss) | true |
| Glaze | 1144.76 | 0.0876341 | 7802.31ms | 728486 | 640 | 1.81024e+08 | 606883 | 0.00935842 | 4(Loss) | true |
| simdjson (ondemand) | 1059.35 | 0.0955706 | 8550.91ms | 728486 | 320 | 1.25708e+08 | 655817 | 0.0386544 | 5(Loss) | true |
