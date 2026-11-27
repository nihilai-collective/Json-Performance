
----
### Discord Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Instructions/Byte | Branches/Byte | Branch Misses/Byte | Cache References/Byte | Cache Misses/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 1901.06 | 0.0471476 | 1073.72ms | 6701 | 2560 | 6430.53 | 3361.59 | 0.0366056 | 2.72746 | 10.9357 | 1.97389 | 0.00100865 | 6.36565e-05 | 2.82724e-05 | 1(Win) | true |
| simdjson (ondemand) | 1786.02 | 0.0455259 | 1090.4ms | 6701 | 2560 | 6793.05 | 3578.11 | 0.404503 | 2.89502 | 11.5026 | 1.88554 | 0.000463084 | 5.17647e-05 | 1.98198e-05 | 2(Loss) | true |
