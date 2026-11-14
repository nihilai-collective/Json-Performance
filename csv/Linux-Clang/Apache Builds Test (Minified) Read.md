
----
### Apache Builds Test (Minified) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16292.8 | 0.0548548 | 1276.21ms | 94653 | 80 | 738.921 | 5540.38 | 0.0428855 | 0.318544 | 1.76926 | 0.0889459 | 2.11298e-05 | 3.82978e-06 | 2.24504e-06 | 1(Win) | true |
| simdjson (stage-1) | 13620.4 | 0.0245379 | 1377.77ms | 94653 | 40 | 105.785 | 6627.4 | 0.0155943 | 0.380575 | 1.81501 | 0.0771766 | 1.90168e-05 | 2.11298e-06 | 0 | 2(Loss) | true |
