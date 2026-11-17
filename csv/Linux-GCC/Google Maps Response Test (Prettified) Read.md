
----
### Google Maps Response Test (Prettified) Read Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Google%20Maps%20Response%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 3058.39 | 0.0524287 | 792.261ms | 25388 | 30 | 516.809 | 7916.53 | 0.237197 | 0.806751 | 1(Win) | true |
| Jsonifier | 3047.85 | 0.0930966 | 798.632ms | 25388 | 4890 | 267453 | 7943.92 | 0.0228154 | 0.809617 | 2(Loss) | true |
| simdjson (reflection) | 2834.12 | 0.0503168 | 858.631ms | 25388 | 80 | 1478.22 | 8543.01 | 0.178045 | 0.87087 | 3(Loss) | true |
| Glaze | 2562.54 | 0.191294 | 957.111ms | 25388 | 1280 | 418145 | 9448.39 | 0.0296269 | 0.963503 | 4(Loss) | true |
| simdjson (ondemand) | 2338.24 | 0.0768937 | 1063.77ms | 25388 | 40 | 2535.83 | 10354.8 | 0.00917538 | 1.05613 | 5(Loss) | true |
