
----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1608.64 | 0.0342998 | 944.211ms | 3873 | 640 | 396.955 | 2296.09 | 0.205525 | 3.24943 | 16.5944 | 2.00852 | 0.00103642 | 3.10644e-05 | 1.2103e-06 | 1(Win) | true |
| simdjson (ondemand) | 734.692 | 0.0612383 | 1223.93ms | 3873 | 320 | 3033.06 | 5027.39 | 0.0854584 | 7.06594 | 27.4216 | 3.45624 | 0.0186846 | 3.46953e-05 | 1.2103e-05 | 2(Loss) | true |
