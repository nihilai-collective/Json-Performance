
----
### Apache Builds Test (Minified) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 16210.2 | 0.0214823 | 1272.44ms | 94653 | 4890 | 6997.81 | 5568.59 | 0.0280825 | 0.319779 | 1.76926 | 0.088946 | 2.1724e-05 | 1.97903e-06 | 5.31486e-07 | 1(Win) | true |
| simdjson (stage-1) | 13596.3 | 0.0743225 | 1378.92ms | 94653 | 40 | 973.926 | 6639.15 | 0.0917122 | 0.381502 | 1.81501 | 0.0771766 | 5.54658e-05 | 1.84886e-06 | 2.64123e-07 | 2(Loss) | true |
