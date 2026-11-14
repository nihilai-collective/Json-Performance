
----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 400.885 | 0.281033 | 216.683ms | 905 | 2560 | 93715.7 | 2152.92 | 0.314513 | 6.09708 | 1(Win) | true |
| simdjson (ondemand) | 199.353 | 0.0504438 | 433.564ms | 905 | 80 | 381.557 | 4329.39 | 0.235285 | 12.3416 | 2(Loss) | true |
