
----
### Uint64 Test Read (Reused) Results [(Here is the data we used for this test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1838.15 | 0.431533 | 66.0155ms | 1213 | 30 | 221.264 | 629.333 | 0.159151 | 1.29233 | 1(Win) | true |
| Glaze | 1010.17 | 0.0428434 | 118.12ms | 1213 | 160 | 38.5143 | 1145.16 | 0.102711 | 2.39544 | 2(Loss) | true |
| simdjson (ondemand) | 326.082 | 0.078061 | 361.492ms | 1213 | 40 | 306.759 | 3547.6 | 0.146793 | 7.54046 | 3(Loss) | true |
