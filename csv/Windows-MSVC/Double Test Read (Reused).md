
----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1204.08 | 0.2626 | 145.98ms | 1811 | 160 | 2270.05 | 1434.38 | 0.043554 | 2.47201 | 1(Win) | true |
| Jsonifier (two-stage) | 630.33 | 0.286301 | 276.544ms | 1811 | 40 | 2461.54 | 2740 | 0.121507 | 4.75363 | 2(Loss) | true |
| Glaze | 579.17 | 0.116697 | 300.102ms | 1811 | 2560 | 31001.7 | 2982.03 | 0.149109 | 5.1828 | 3(Loss) | true |
| simdjson (ondemand) | 282.538 | 0.165894 | 623.954ms | 1811 | 320 | 32907.4 | 6112.81 | 0.117719 | 10.7042 | 4(Loss) | true |
