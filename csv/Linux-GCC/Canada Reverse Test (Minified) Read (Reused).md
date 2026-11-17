
----
### Canada Reverse Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Canada%20Reverse%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 853.593 | 0.0780038 | 8478.2ms | 2090234 | 160 | 5.30934e+08 | 2.33531e+06 | 0.0676436 | 5.96587 | 28.5482 | 5.76888 | 0.0213732 | 0.130074 | 0.000218968 | 1(Win) | true |
| simdjson (ondemand) | 844.322 | 0.212687 | 8555.52ms | 2090234 | 160 | 4.03436e+09 | 2.36095e+06 | 0.482181 | 6.01999 | 29.379 | 5.3176 | 0.0222502 | 0.155225 | 7.46597e-05 | 2(Loss) | true |
