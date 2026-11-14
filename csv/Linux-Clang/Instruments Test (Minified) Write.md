
----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18259.8 | 0.0795062 | 1321.76ms | 108313 | 4890 | 98918.9 | 5656.97 | 0.0898322 | 0.278145 | 1.2473 | 0.328252 | 0.000217838 | 6.05494e-06 | 2.93401e-06 | 1(Win) | true |
| Glaze | 4887.02 | 0.0758745 | 2867.95ms | 108313 | 4890 | 1.25769e+06 | 21136.7 | 0.00749635 | 1.03654 | 3.26353 | 0.411382 | 0.000318423 | 1.19079e-05 | 6.1229e-06 | 2(Loss) | true |
