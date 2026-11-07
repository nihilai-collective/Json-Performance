
----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1927.81 | 0.066748 | 48.2023ms | 905 | 320 | 28.5755 | 447.697 | 0.0788137 | 1.21378 | 1(Win) | true |
| Glaze | 1507.27 | 0.0380906 | 59.9311ms | 905 | 320 | 15.2231 | 572.609 | 0.00163721 | 1.5683 | 2(Loss) | true |
| Jsonifier (two-stage) | 529.368 | 0.0285602 | 164.51ms | 905 | 160 | 34.6917 | 1630.39 | 0.0782635 | 4.6032 | 3(Loss) | true |
| simdjson (ondemand) | 257.655 | 0.0471462 | 340.24ms | 905 | 30 | 74.823 | 3349.73 | 0.0984183 | 9.5361 | 4(Loss) | true |
