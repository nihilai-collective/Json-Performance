
----
### Int64 Test Write Results [(Here is the data we used for this test)](./json/Int64%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Int64%20Test%20Write_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Int64%20Test%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 248.576 | 0.436301 | 513.639ms | 1313 | 2560 | 1.23659e+06 | 5037.4 | 2.65141 | 1(Win) | true |
| simdjson (reflection) | 243.709 | 0.419303 | 531.56ms | 1313 | 2560 | 1.18818e+06 | 5138 | 0.0544662 | 2(Loss) | true |
| Glaze | 176.263 | 0.727045 | 852.82ms | 1313 | 40 | 106706 | 7104 | 0.41866 | 3(Loss) | true |
