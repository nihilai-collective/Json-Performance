
----
### Discord Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2052.04 | 0.189556 | 4004.62ms | 83958 | 640 | 3.50113e+06 | 39019.1 | 0.0485214 | 1.20569 | 1(Win) | true |
| simdjson (ondemand) | 1844.29 | 0.0764813 | 4386.94ms | 83958 | 2560 | 2.82239e+06 | 43414.4 | 0.0318797 | 1.3416 | 2(Loss) | true |
