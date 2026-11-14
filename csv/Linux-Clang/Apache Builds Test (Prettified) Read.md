
----
### Apache Builds Test (Prettified) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 15898.7 | 0.0568606 | 1466.78ms | 124597 | 160 | 2889.57 | 7473.86 | 0.159811 | 0.325816 | 1.76336 | 0.0810052 | 9.15953e-05 | 1.75566e-06 | 7.02264e-07 | 1(Win) | true |
| simdjson (stage-1) | 14741.4 | 0.0273253 | 1521.99ms | 124597 | 2560 | 12419.6 | 8060.65 | 0.0176124 | 0.351031 | 1.64946 | 0.0692553 | 2.46106e-05 | 1.98766e-06 | 9.43667e-07 | 2(Loss) | true |
