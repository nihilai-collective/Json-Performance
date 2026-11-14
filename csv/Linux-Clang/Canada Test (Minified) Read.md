
----
### Canada Test (Minified) Results [(View the data used in the following test)](./json/Canada%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 14278.6 | 0.0229672 | 8106.72ms | 2251027 | 2560 | 3.05245e+06 | 150347 | 0.167334 | 0.357046 | 1.7439 | 0.0767384 | 0.00152989 | 0.0248706 | 1.88247e-06 | 1(Win) | true |
| simdjson (stage-1) | 11465.9 | 0.0310113 | 9968.85ms | 2251027 | 640 | 2.15759e+06 | 187229 | 0.142635 | 0.447819 | 1.89627 | 0.0806442 | 0.00173416 | 0.0244882 | 1.32578e-06 | 2(Loss) | true |
