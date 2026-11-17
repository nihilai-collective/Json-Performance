
----
### Discord Test (Minified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10926.7 | 0.15024 | 1214.39ms | 56369 | 40 | 2185.41 | 4919.85 | 0.064662 | 0.467495 | 2.28846 | 0.0971988 | 5.32207e-05 | 2.21753e-06 | 0 | 1(Win) | true |
| simdjson (stage-1) | 10294.8 | 0.0298006 | 1250.48ms | 56369 | 1280 | 3099.59 | 5221.82 | 0.0773049 | 0.504083 | 2.58342 | 0.102929 | 3.53696e-05 | 3.03525e-06 | 8.31574e-08 | 2(Loss) | true |
