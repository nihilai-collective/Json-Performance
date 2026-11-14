
----
### Instruments Small Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Small%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 12272.8 | 0.211162 | 768.739ms | 4669 | 4890 | 2870.1 | 362.81 | 0.105099 | 0.458776 | 1.4093 | 0.362176 | 0.00028798 | 1.85271e-05 | 2.93455e-06 | 1(Win) | true |
| Glaze | 2255.08 | 0.222796 | 935.539ms | 4669 | 2560 | 49542.5 | 1974.52 | 0.0159625 | 2.28854 | 3.69265 | 0.510388 | 0.000224971 | 3.12902e-05 | 2.34258e-06 | 2(Loss) | true |
