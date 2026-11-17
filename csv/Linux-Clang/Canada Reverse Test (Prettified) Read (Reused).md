
----
### Canada Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1814.71 | 0.218459 | 9752.14ms | 5212421 | 80 | 2.86481e+09 | 2.73926e+06 | 0.293909 | 2.78639 | 12.9527 | 2.34309 | 0.0099929 | 0.090384 | 0.000632141 | 1(Win) | true |
| simdjson (ondemand) | 1769.41 | 0.0795822 | 10035.7ms | 5212421 | 160 | 7.99791e+08 | 2.80939e+06 | 0.402237 | 2.85536 | 13.0604 | 2.16865 | 0.0100516 | 0.110355 | 0.000389725 | 2(Loss) | true |
