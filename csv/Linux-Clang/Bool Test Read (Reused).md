
----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 566.251 | 0.0637111 | 861.32ms | 905 | 4890 | 4611.25 | 1524.19 | 0.00433189 | 9.34577 | 48.7514 | 6.25194 | 0.00297281 | 9.8973e-05 | 6.77897e-06 | 1(Win) | true |
| simdjson (ondemand) | 290.043 | 0.0878003 | 1009.29ms | 905 | 320 | 2184.31 | 2975.68 | 0.0854527 | 18.0018 | 88.3271 | 9.35912 | 0.0244199 | 0.000172652 | 0 | 2(Loss) | true |
