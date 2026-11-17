
----
### Twitter Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Twitter%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 905.55 | 0.114363 | 5136.86ms | 360584 | 320 | 6.03545e+07 | 379747 | 0.0963559 | 5.63374 | 21.0413 | 3.9695 | 0.0159898 | 0.000120178 | 9.93181e-06 | 1(Win) | true |
| simdjson (ondemand) | 455.863 | 0.0720402 | 9922.63ms | 360584 | 640 | 1.89005e+08 | 754349 | 0.130929 | 11.1012 | 45.8953 | 9.2365 | 0.0529672 | 0.000286241 | 1.8074e-05 | 2(Loss) | true |
