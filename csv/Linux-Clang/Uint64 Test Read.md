
----
### Uint64 Test Read Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1595.13 | 0.483388 | 73.9149ms | 1213 | 80 | 983.131 | 725.212 | 0.254018 | 1.49471 | 1(Win) | true |
| Glaze | 921.089 | 0.186256 | 128.905ms | 1213 | 80 | 437.752 | 1255.91 | 0.0984369 | 2.62966 | 2(Loss) | true |
| simdjson (ondemand) | 298.976 | 0.0957829 | 387.403ms | 1213 | 30 | 412.047 | 3869.23 | 0.112984 | 8.22295 | 3(Loss) | true |
