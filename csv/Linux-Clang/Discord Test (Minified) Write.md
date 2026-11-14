
----
### Discord Test (Minified) Write Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14480.5 | 0.0874529 | 1117.24ms | 56369 | 2560 | 26983.7 | 3712.41 | 0.048084 | 0.352821 | 1.42142 | 0.238677 | 0.000220838 | 8.81469e-06 | 3.3263e-06 | 1(Win) | true |
| Glaze | 4935.57 | 0.0809043 | 1837.91ms | 56369 | 4890 | 379715 | 10891.9 | 0.0508476 | 1.02491 | 3.48779 | 0.484202 | 0.000110566 | 1.09307e-05 | 4.98468e-06 | 2(Loss) | true |
