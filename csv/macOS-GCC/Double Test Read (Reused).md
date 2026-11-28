
----
### Double Test Read (Reused) Results [(Here is the data we used for this test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1093.38 | 1.6565 | 161.262ms | 1811 | 640 | 438182 | 1579.6 | 0.126454 | 1(Win) | true |
| Glaze | 1039.8 | 0.821388 | 178.781ms | 1811 | 1280 | 238257 | 1661 | 0.823979 | 2(Loss) | true |
| simdjson (reflection) | 282.405 | 0.268871 | 627.936ms | 1811 | 2560 | 692180 | 6115.7 | 1.13324 | 3(Loss) | true |
| simdjson (ondemand) | 279.667 | 0.25815 | 623.88ms | 1811 | 4890 | 1.24282e+06 | 6175.57 | 1.52337 | 4(Loss) | true |
