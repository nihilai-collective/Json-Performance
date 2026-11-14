
----
### Instruments Test (Minified) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 21991.6 | 0.0491723 | 476.114ms | 108313 | 30 | 160.033 | 4697.03 | 0.135019 | 0.111924 | 1(Win) | true |
| simdjson (stage-1) | 18756.2 | 0.0355343 | 567.813ms | 108313 | 30 | 114.892 | 5507.27 | 0.0478385 | 0.131296 | 2(Loss) | true |
