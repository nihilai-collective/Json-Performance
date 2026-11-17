
----
### Instruments Stream Test (NDJSON) Read Results [(View the data used in the following test)](./json/Instruments%20Stream%20Test%20%28NDJSON%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Stream%20Test%20%28NDJSON%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1782.96 | 0.251726 | 7293.19ms | 4197496 | 40 | 1.27765e+09 | 2.24517e+06 | 0.336361 | 1.38847 | 1(Win) | true |
| simdjson (ondemand) | 1425.3 | 0.0752061 | 9270.43ms | 4197496 | 160 | 7.13826e+08 | 2.80856e+06 | 0.866131 | 1.73692 | 2(Loss) | true |
