
----
### Double Test Read (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1130.21 | 0.233334 | 160.1ms | 1811 | 160 | 2034.2 | 1528.12 | 0.204918 | 2.15181 | 1(Win) | true |
| Glaze | 474.438 | 0.0754445 | 361.861ms | 1811 | 320 | 2413.7 | 3640.31 | 0.00858516 | 5.17661 | 2(Loss) | true |
| simdjson (ondemand) | 347.04 | 0.157817 | 514.194ms | 1811 | 30 | 1850.57 | 4976.67 | 0.0670241 | 7.0989 | 3(Loss) | true |
