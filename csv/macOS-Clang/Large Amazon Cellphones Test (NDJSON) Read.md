
----
### Large Amazon Cellphones Test (NDJSON) Read Results [(View the data used in the following test)](./json/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Large%20Amazon%20Cellphones%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 3178.62 | 0.0470681 | 9988.17ms | 10548466 | 80 | 1.77519e+08 | 3.16483e+06 | 0.169418 | 1(Win) | true |
| simdjson (ondemand) | 2811.81 | 0.0481637 | 5562.34ms | 10548466 | 80 | 2.37539e+08 | 3.57769e+06 | 0.333509 | 2(Loss) | true |
