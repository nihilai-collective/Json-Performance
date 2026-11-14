
----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (generic) | 305.1 | 0.158143 | 285.465ms | 905 | 4890 | 97864 | 2828.83 | 0.319011 | 8.03305 | 1(Win) | true |
| simdjson (ondemand) | 252.923 | 0.0574505 | 380.441ms | 905 | 40 | 153.733 | 3412.4 | 0.255276 | 9.70898 | 2(Loss) | true |
