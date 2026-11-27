
----
### Discord Sparse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Sparse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Sparse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 3347.88 | 0.171858 | 2410.7ms | 83958 | 640 | 1.08119e+06 | 23916.2 | 0.116853 | 0.738711 | 1(Win) | true |
| simdjson (ondemand) | 3152.59 | 0.110514 | 2567.12ms | 83958 | 1280 | 1.0084e+06 | 25397.7 | 0.000618286 | 0.784432 | 2(Loss) | true |
