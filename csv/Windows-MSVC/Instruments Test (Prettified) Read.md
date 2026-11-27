
----
### Instruments Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2573.76 | 0.537746 | 6773.72ms | 183677 | 1280 | 1.7145e+08 | 68059.1 | 0.142252 | 1.18034 | 1(Win) | true |
| Jsonifier (two-stage) | 2272.15 | 0.747822 | 7782.21ms | 183677 | 1280 | 4.25445e+08 | 77093.6 | 0.509151 | 1.33706 | 2(Loss) | true |
| Glaze | 1721.94 | 2.01664 | 5284.67ms | 183677 | 160 | 6.73364e+08 | 101727 | 0.134733 | 1.76465 | 3(Loss) | true |
| simdjson (ondemand) | 1455.63 | 0.353394 | 6232.32ms | 183677 | 1280 | 2.31494e+08 | 120339 | 0.29523 | 2.08737 | 4(Loss) | true |
