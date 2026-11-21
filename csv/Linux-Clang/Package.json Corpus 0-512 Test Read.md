
----
### Package.json Corpus 0-512 Test Read Results [(View the data used in the following test)](./json/Package.json%20Corpus%200-512%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Package.json%20Corpus%200-512%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Package.json%20Corpus%200-512%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 3828.38 | 0.0776499 | 40.0824ms | 1497 | 1280 | 107.326 | 372.913 | 0.181516 | 0.60183 | 1(Win) | true |
| Jsonifier (generic) | 3557.73 | 0.0942672 | 42.8837ms | 1497 | 640 | 91.5796 | 401.281 | 0.000778749 | 0.647093 | 2(Loss) | true |
