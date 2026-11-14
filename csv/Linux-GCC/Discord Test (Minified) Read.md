
----
### Discord Test (Minified) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 10980.1 | 0.152412 | 1209.61ms | 56369 | 320 | 17818 | 4895.93 | 0.0454027 | 0.468842 | 2.28846 | 0.097199 | 0.000102228 | 3.49261e-06 | 4.43506e-07 | 1(Win) | true |
| simdjson (stage-1) | 10249.6 | 0.0780098 | 1244.72ms | 56369 | 640 | 10713.7 | 5244.83 | 0.18671 | 0.504741 | 2.58342 | 0.102929 | 5.36365e-05 | 2.74419e-06 | 0 | 2(Loss) | true |
