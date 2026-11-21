
----
### Package.json Corpus All Test Read Results [(View the data used in the following test)](./json/Package.json%20Corpus%20All%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Package.json%20Corpus%20All%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Package.json%20Corpus%20All%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 8130.3 | 0.123218 | 2835.44ms | 238993 | 1280 | 1.52726e+06 | 28033.6 | 0.0725583 | 0.304237 | 1(Win) | true |
| simdjson (ondemand) | 7739.94 | 0.0399366 | 3004.01ms | 238993 | 30 | 4149.15 | 29447.5 | 0.0158499 | 0.319605 | 2(Loss) | true |
