
----
### Instruments Reverse Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Instruments%20Reverse%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 996.936 | 0.0173961 | 9457.35ms | 183677 | 2560 | 2.39177e+06 | 175706 | 0.00310186 | 5.15019 | 23.742 | 4.69358 | 0.00560066 | 1.80641e-05 | 1.128e-05 | 1(Win) | true |
| simdjson (ondemand) | 424.227 | 0.0730591 | 5372.34ms | 183677 | 640 | 5.82428e+07 | 412911 | 0.0185346 | 11.9926 | 58.3352 | 10.4679 | 0.0363959 | 0.000109542 | 8.75518e-05 | 2(Loss) | true |
