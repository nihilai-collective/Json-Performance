
----
### Discord Test (Minified) Write (Reused) Results [(View the data used in the following test)](./json/Discord%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Discord%20Test%20%28Minified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15183.4 | 0.0403401 | 1095.04ms | 56369 | 2560 | 5222.2 | 3540.54 | 0.00343135 | 0.336881 | 1.40929 | 0.222197 | 0.000182662 | 9.55617e-06 | 4.38655e-06 | 1(Win) | true |
| simdjson (reflection) | 13345 | 0.0638876 | 1148.18ms | 56369 | 40 | 264.933 | 4028.3 | 0.011586 | 0.38298 | 1.68962 | 0.275222 | 0.000173854 | 1.19747e-05 | 5.76558e-06 | 2(Loss) | true |
| Glaze | 7181.64 | 0.0757971 | 1491.95ms | 56369 | 1280 | 41204.9 | 7485.43 | 0.0711501 | 0.707217 | 2.97538 | 0.448722 | 4.81759e-05 | 2.83705e-05 | 1.67839e-05 | 3(Loss) | true |
