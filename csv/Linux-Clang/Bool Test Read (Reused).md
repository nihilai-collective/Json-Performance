
----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1768.19 | 0.101589 | 51.8048ms | 905 | 80 | 19.6707 | 488.113 | 0.808034 | 1.32145 | 1(Win) | true |
| Glaze | 1320.63 | 0.485148 | 68.3071ms | 905 | 4890 | 49158.2 | 653.535 | 0.463278 | 1.79083 | 2(Loss) | true |
| Jsonifier (two-stage) | 479.202 | 0.0703287 | 181.597ms | 905 | 30 | 48.1333 | 1801.07 | 0.368786 | 5.08983 | 3(Loss) | true |
| simdjson (ondemand) | 245.84 | 0.258206 | 355.746ms | 905 | 80 | 6573.75 | 3510.71 | 0.0837425 | 9.98878 | 4(Loss) | true |
