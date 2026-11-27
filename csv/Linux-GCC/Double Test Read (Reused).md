
----
### Double Test Read (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 979.771 | 0.0278446 | 189.679ms | 1811 | 160 | 38.547 | 1762.76 | 0.0411455 | 2.49088 | 1(Win) | true |
| simdjson (ondemand) | 380.601 | 0.0933878 | 465.203ms | 1811 | 30 | 538.764 | 4537.83 | 0.213302 | 6.47 | 2(Loss) | true |
