
----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 2037.02 | 0.355226 | 3871.96ms | 83958 | 40 | 779837 | 39306.7 | 0.0320446 | 1.21459 | 1(Win) | true |
| simdjson (ondemand) | 1746.07 | 0.153197 | 4461.93ms | 83958 | 320 | 1.57925e+06 | 45856.4 | 0.196897 | 1.41708 | 2(Loss) | true |
