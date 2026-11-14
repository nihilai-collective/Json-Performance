
----
### Instruments Test (Prettified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2652.61 | 0.138026 | 7076.33ms | 183677 | 640 | 5.31699e+06 | 66036 | 0.524223 | 1(Win) | true |
| Jsonifier (two-stage) | 2039.4 | 0.157859 | 8598.3ms | 183677 | 4890 | 8.98989e+07 | 85891.9 | 0.331208 | 2(Loss) | true |
| Glaze | 1903.76 | 0.0874051 | 9301.03ms | 183677 | 1280 | 8.27885e+06 | 92011.8 | 0.47011 | 3(Loss) | true |
| simdjson (reflection) | 1809.11 | 0.462759 | 9818.1ms | 183677 | 40 | 8.03064e+06 | 96825.6 | 0.0595238 | 4(Loss) | true |
| simdjson (ondemand) | 1695.12 | 0.185411 | 5301.19ms | 183677 | 1280 | 4.69883e+07 | 103337 | 0.241729 | 5(Loss) | true |
