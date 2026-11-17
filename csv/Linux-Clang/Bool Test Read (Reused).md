
----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 384.338 | 0.0413262 | 233.925ms | 905 | 80 | 68.8986 | 2245.61 | 0.823315 | 6.36204 | 1(Win) | true |
| simdjson (ondemand) | 250.13 | 0.0741653 | 352.258ms | 905 | 30 | 196.466 | 3450.5 | 0.471131 | 9.81669 | 2(Loss) | true |
