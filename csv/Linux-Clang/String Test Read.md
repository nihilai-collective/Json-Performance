
----
### String Test Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/String%20Test%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/String%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 7641.36 | 0.0666257 | 123.542ms | 9578 | 80 | 50.7437 | 1195.38 | 0.025103 | 0.316777 | 1(Win) | true |
| simdjson (stage-1) | 4948.69 | 0.13335 | 193.961ms | 9578 | 30 | 181.752 | 1845.8 | 0.0180558 | 0.4925 | 2(Loss) | true |
