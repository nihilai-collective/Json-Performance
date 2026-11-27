
----
### Bool Test Read (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 322.364 | 0.992628 | 260.602ms | 905 | 640 | 452018 | 2677.33 | 0.533915 | 1(Win) | true |
| simdjson (ondemand) | 238.975 | 0.32595 | 385.246ms | 905 | 2560 | 354760 | 3611.58 | 0.150342 | 2(Loss) | true |
