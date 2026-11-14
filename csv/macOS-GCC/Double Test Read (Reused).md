
----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 357.105 | 0.776263 | 516.579ms | 1811 | 640 | 902075 | 4836.4 | 1.51973 | 1(Win) | true |
| simdjson (ondemand) | 178.686 | 0.218183 | 962.48ms | 1811 | 2560 | 1.13852e+06 | 9665.6 | 1.49103 | 2(Loss) | true |
