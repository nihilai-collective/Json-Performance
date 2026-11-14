
----
### Uint64 Test Read (Reused) Results [(View the data used in the following test)](./json/Uint64%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Uint64%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1594.69 | 0.052718 | 941.96ms | 3873 | 160 | 238.552 | 2316.18 | 0.0644504 | 3.29747 | 16.5882 | 2.00697 | 0.00201394 | 4.51846e-05 | 0 | 1(Win) | true |
| simdjson (ondemand) | 733.403 | 0.020832 | 1216.41ms | 3873 | 4890 | 5382.47 | 5036.22 | 0.058846 | 7.07549 | 27.4216 | 3.45624 | 0.0183404 | 4.84715e-05 | 6.33614e-06 | 2(Loss) | true |
