
----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 3001.29 | 0.0399124 | 127.244ms | 3873 | 160 | 38.6024 | 1230.66 | 0.0497947 | 0.807475 | 1(Win) | true |
| Glaze | 1985.15 | 0.0263528 | 189.84ms | 3873 | 160 | 38.4666 | 1860.61 | 0.0097405 | 1.2296 | 2(Loss) | true |
| Jsonifier (two-stage) | 823.657 | 0.0784997 | 459.558ms | 3873 | 30 | 371.757 | 4484.37 | 0.155855 | 2.98845 | 3(Loss) | true |
| simdjson (ondemand) | 554.508 | 0.0612259 | 703.782ms | 3873 | 30 | 498.966 | 6661 | 0.12495 | 4.44853 | 4(Loss) | true |
