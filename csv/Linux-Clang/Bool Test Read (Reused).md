
----
### Bool Test Read (Reused) Results [(Here is the data we used for this test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1931.14 | 0.123889 | 48.2956ms | 905 | 80 | 24.5259 | 446.925 | 0.0559065 | 1.20931 | 1(Win) | true |
| Glaze | 1474.67 | 0.15714 | 62.966ms | 905 | 30 | 25.3747 | 585.267 | 0.210287 | 1.60862 | 2(Loss) | true |
| simdjson (ondemand) | 474.696 | 0.500271 | 186.086ms | 905 | 640 | 52948.9 | 1818.16 | 0.101941 | 5.14123 | 3(Loss) | true |
