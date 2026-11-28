
----
### Double Test Read (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1550.43 | 0.0497341 | 113.322ms | 1811 | 80 | 24.5544 | 1113.95 | 0.132237 | 1.55957 | 1(Win) | true |
| Glaze | 1063.42 | 0.0463752 | 161.245ms | 1811 | 80 | 45.3823 | 1624.1 | 0.067684 | 2.28927 | 2(Loss) | true |
| simdjson (ondemand) | 429.468 | 0.162687 | 405.31ms | 1811 | 2560 | 109577 | 4021.5 | 0.0494265 | 5.72832 | 3(Loss) | true |
| simdjson (reflection) | 402.052 | 0.136787 | 432.331ms | 1811 | 4890 | 168839 | 4295.73 | 0.0343955 | 6.12114 | 4(Loss) | true |
