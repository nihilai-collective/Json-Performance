
----
### Double Test Read Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Double%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Double%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (stage-1) | 3133.6 | 0.040364 | 58.1608ms | 1811 | 320 | 15.8376 | 551.156 | 0.0521903 | 0.753244 | 1(Win) | true |
| simdjson (stage-1) | 1444.97 | 0.0652031 | 123.566ms | 1811 | 40 | 24.2949 | 1195.25 | 0.018124 | 1.67675 | 2(Loss) | true |
