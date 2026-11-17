
----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 564.316 | 0.107393 | 867.677ms | 905 | 160 | 431.641 | 1529.42 | 0.0535621 | 9.36285 | 48.7514 | 6.25193 | 0.00446823 | 5.52486e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 291.988 | 0.114625 | 1015.83ms | 905 | 160 | 1836.72 | 2955.86 | 0.269497 | 17.8671 | 88.3271 | 9.35912 | 0.0224931 | 6.90608e-05 | 0 | 2(Loss) | true |
