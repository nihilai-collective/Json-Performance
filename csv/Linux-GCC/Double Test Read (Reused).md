
----
### Double Test Read (Reused) Results [(View the data used in the following test)](./json/Double%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Double%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 636.955 | 0.0372019 | 983.514ms | 1811 | 4890 | 4975.76 | 2711.5 | 0.160948 | 8.20258 | 40.3385 | 5.71618 | 0.00111588 | 9.57566e-05 | 1.18566e-05 | 1(Win) | true |
| simdjson (ondemand) | 334.088 | 0.0758179 | 1233.68ms | 1811 | 1280 | 19663.8 | 5169.6 | 0.0859608 | 15.3573 | 76.1773 | 9.5323 | 0.00150211 | 8.28272e-05 | 4.31391e-06 | 2(Loss) | true |
