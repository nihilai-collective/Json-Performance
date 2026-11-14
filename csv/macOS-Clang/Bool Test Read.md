
----
### Bool Test Read Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 184.734 | 0.220518 | 526.668ms | 905 | 80 | 8491.47 | 4672 | 2.94015 | 1(Win) | true |
| simdjson (ondemand) | 173.661 | 0.422532 | 559.365ms | 905 | 40 | 17638.8 | 4969.88 | 1.83196 | 2(Loss) | true |
