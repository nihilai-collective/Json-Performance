
----
### Github Events Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 1668.13 | 0.0735513 | 4339.84ms | 65103 | 2560 | 1.91851e+06 | 37219.6 | 0.0687337 | 1(Win) | true |
| simdjson (ondemand) | 1181.3 | 0.174247 | 5990.19ms | 65103 | 320 | 2.68389e+06 | 52558.4 | 0.0699684 | 2(Loss) | true |
