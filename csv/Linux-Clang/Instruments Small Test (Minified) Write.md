
----
### Instruments Small Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 11878.3 | 0.221323 | 773.587ms | 4669 | 4890 | 3365.89 | 374.86 | 0.149436 | 0.473529 | 1.40801 | 0.361963 | 0.000345095 | 3.7098e-05 | 7.40208e-06 | 1(Win) | true |
| Glaze | 2466 | 0.192207 | 918.538ms | 4669 | 4890 | 58898.9 | 1805.64 | 0.0842261 | 2.10518 | 3.68452 | 0.508461 | 0.000221274 | 7.90578e-05 | 3.10975e-05 | 2(Loss) | true |
