
----
### Prettify Test Write (Reused) Results [(View the data used in the following test)](./json/Prettify%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Prettify%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Prettify%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 5203.36 | 0.0928811 | 6588.79ms | 699405 | 640 | 9.07243e+06 | 128187 | 0.0984795 | 0.475704 | 1(Win) | true |
| Glaze | 3453.07 | 0.0844686 | 5140.36ms | 699405 | 640 | 1.70379e+07 | 193163 | 0.137642 | 0.716892 | 2(Loss) | true |
| simdjson (ondemand) | 2678.43 | 0.114942 | 6976.82ms | 767297 | 1280 | 1.26221e+08 | 273201 | 0.239829 | 0.924244 | 3(Loss) | true |
