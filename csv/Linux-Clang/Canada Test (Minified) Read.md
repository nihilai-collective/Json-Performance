
----
### Canada Test (Minified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14160.5 | 0.0938104 | 8229.79ms | 2251027 | 640 | 1.29445e+07 | 151601 | 0.240952 | 0.357626 | 1.7439 | 0.0767384 | 0.00151847 | 0.02474 | 1.86651e-06 | 1(Win) | true |
| simdjson (stage-1) | 11462.9 | 0.153349 | 10074.5ms | 2251027 | 40 | 3.29906e+06 | 187277 | 0.699295 | 0.445487 | 1.89627 | 0.0806442 | 0.00166777 | 0.024297 | 7.21893e-07 | 2(Loss) | true |
