
----
### Instruments Test (Minified) Read Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1500.85 | 0.0170535 | 7598.25ms | 108313 | 4890 | 673632 | 68824.8 | 0.0891372 | 3.38143 | 14.88 | 3.01818 | 0.00414307 | 1.49249e-05 | 6.85735e-06 | 1(Win) | true |
| simdjson (ondemand) | 1396.9 | 0.0383465 | 8158.12ms | 108313 | 1280 | 1.02918e+06 | 73946.2 | 0.0190463 | 3.6635 | 16.6552 | 2.51372 | 0.00709797 | 3.98945e-05 | 2.66011e-05 | 2(Loss) | true |
