
----
### Github Events Test (Prettified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1453.28 | 0.123231 | 4307.19ms | 65103 | 4890 | 1.35534e+07 | 42721.9 | 0.000857034 | 1.70237 | 1(Win) | true |
| simdjson (ondemand) | 1199.53 | 0.457236 | 5452.24ms | 65103 | 30 | 1.68029e+06 | 51759.6 | 0.110956 | 2.0629 | 2(Loss) | true |
