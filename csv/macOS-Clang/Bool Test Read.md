
----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1208.9 | 0.160422 | 74.9236ms | 905 | 320 | 419.754 | 713.934 | 0.101215 | 1(Win) | true |
| Glaze | 1103.42 | 0.14764 | 80.1973ms | 905 | 320 | 426.751 | 782.181 | 0.118917 | 2(Loss) | true |
| Jsonifier (two-stage) | 1083.79 | 0.294682 | 87.5735ms | 905 | 80 | 440.559 | 796.35 | 0.322308 | 3(Loss) | true |
| simdjson (ondemand) | 278.714 | 0.17522 | 315.993ms | 905 | 2560 | 75368.6 | 3096.64 | 0.11276 | 4(Loss) | true |
