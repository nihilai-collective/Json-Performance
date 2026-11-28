
----
### String Test Read Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 831.727 | 0.460728 | 485.931ms | 4215 | 2560 | 1.26929e+06 | 4833 | 2.22141 | 1(Win) | true |
| Glaze | 639.434 | 0.78684 | 694.993ms | 4215 | 320 | 782937 | 6286.4 | 0.46024 | 2(Loss) | true |
| simdjson (reflection) | 589.698 | 0.586292 | 728.384ms | 4215 | 1280 | 2.04444e+06 | 6816.6 | 1.02509 | 3(Loss) | true |
| simdjson (ondemand) | 484.399 | 0.439332 | 875.75ms | 4215 | 1280 | 1.70132e+06 | 8298.4 | 0.717841 | 4(Loss) | true |
