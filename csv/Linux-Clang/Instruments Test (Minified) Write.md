
----
### Instruments Test (Minified) Write Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier | 18189.2 | 0.1654 | 1312.71ms | 108313 | 640 | 56466.2 | 5678.95 | 0.0868267 | 0.278931 | 1.2473 | 0.328252 | 0.000206015 | 6.56373e-06 | 3.57759e-06 | 1(Win) | true |
| Glaze | 4692.18 | 0.0993827 | 2946.48ms | 108313 | 2560 | 1.22539e+06 | 22014.3 | 0.123582 | 1.07932 | 3.26353 | 0.411382 | 0.000277321 | 2.66444e-05 | 1.73867e-05 | 2(Loss) | true |
