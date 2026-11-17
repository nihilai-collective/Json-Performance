
----
### Uint64 Test Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Uint64%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2842.53 | 0.0811277 | 134.006ms | 3873 | 40 | 44.4513 | 1299.4 | 0.0410614 | 0.854209 | 1(Win) | true |
| simdjson (stage-1) | 1398.43 | 0.0358486 | 300.195ms | 3873 | 80 | 71.7209 | 2641.22 | 0.000946539 | 1.75194 | 2(Loss) | true |
