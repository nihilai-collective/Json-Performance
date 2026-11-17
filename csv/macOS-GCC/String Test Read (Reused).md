
----
### String Test Read (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/String%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/String%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1052.16 | 0.155295 | 1113.26ms | 9578 | 2560 | 465314 | 8681.5 | 0.245953 | 1(Win) | true |
| simdjson (ondemand) | 873.026 | 0.412248 | 1231.48ms | 9578 | 1280 | 2.38135e+06 | 10462.8 | 0.137441 | 2(Loss) | true |
