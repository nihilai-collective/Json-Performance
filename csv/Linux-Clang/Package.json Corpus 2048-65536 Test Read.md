
----
### Package.json Corpus 2048-65536 Test Read Results [(View the data used in the following test)](./json/Package.json%20Corpus%202048-65536%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Package.json%20Corpus%202048-65536%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Package.json%20Corpus%202048-65536%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 10099.7 | 0.58517 | 565.104ms | 59099 | 160 | 170619 | 5580.48 | 0.169054 | 0.243972 | 1(Win) | true |
| simdjson (ondemand) | 8762.12 | 0.053025 | 654.57ms | 59099 | 30 | 348.999 | 6432.37 | 0.0570359 | 0.28147 | 2(Loss) | true |
