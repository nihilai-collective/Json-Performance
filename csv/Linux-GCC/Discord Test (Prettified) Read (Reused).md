
----
### Discord Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2324.34 | 0.119016 | 3830.73ms | 83958 | 1280 | 2.15153e+06 | 34447.9 | 0.0325023 | 1.06431 | 1(Win) | true |
| simdjson (ondemand) | 2190.49 | 0.114496 | 4033.77ms | 83958 | 1280 | 2.24199e+06 | 36552.8 | 0.0333619 | 1.12942 | 2(Loss) | true |
