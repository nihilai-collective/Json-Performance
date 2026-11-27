
----
### Github Events Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1845.26 | 0.0997686 | 4662.49ms | 65103 | 320 | 360601 | 33646.9 | 0.106634 | 2.76788 | 9.90329 | 1.86175 | 0.00841066 | 4.00327e-05 | 2.80805e-05 | 1(Win) | true |
| simdjson (ondemand) | 1453.2 | 0.0390847 | 5578.9ms | 65103 | 2560 | 713844 | 42724.2 | 0.103883 | 3.49672 | 13.7963 | 2.44986 | 0.0129112 | 3.13326e-05 | 2.07544e-05 | 2(Loss) | true |
