
----
### Discord Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2525.76 | 0.0772391 | 3202.42ms | 83958 | 4890 | 2.93173e+06 | 31700.8 | 0.376768 | 0.979364 | 1(Win) | true |
| Jsonifier | 2038.96 | 0.0923028 | 4000.46ms | 83958 | 2560 | 3.36339e+06 | 39269.3 | 0.202025 | 1.21339 | 2(Loss) | true |
| Glaze | 1984.7 | 0.167428 | 4147.23ms | 83958 | 320 | 1.45996e+06 | 40342.9 | 0.352071 | 1.24663 | 3(Loss) | true |
| simdjson (ondemand) | 1186.28 | 0.115796 | 6714.22ms | 83958 | 640 | 3.9095e+06 | 67495.6 | 0.327749 | 2.08619 | 4(Loss) | true |
