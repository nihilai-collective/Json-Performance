
----
### Instruments Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1634.53 | 0.0349752 | 7247.3ms | 108313 | 1280 | 625327 | 63195.8 | 0.0940385 | 3.12971 | 14.1474 | 2.84873 | 0.00347974 | 1.01413e-05 | 5.81359e-06 | 1(Win) | true |
| simdjson (ondemand) | 1505.5 | 0.0364009 | 7805ms | 108313 | 1280 | 798430 | 68612.1 | 0.194758 | 3.40771 | 15.9279 | 2.34549 | 0.00607275 | 3.12967e-05 | 2.25403e-05 | 2(Loss) | true |
