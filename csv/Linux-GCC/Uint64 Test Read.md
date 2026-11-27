
----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 873.655 | 0.0276985 | 136.629ms | 1213 | 320 | 43.0433 | 1324.1 | 0.0458068 | 2.77965 | 1(Win) | true |
| simdjson (ondemand) | 326.034 | 0.122243 | 358.367ms | 1213 | 4890 | 91991.9 | 3548.11 | 0.137515 | 7.53882 | 2(Loss) | true |
