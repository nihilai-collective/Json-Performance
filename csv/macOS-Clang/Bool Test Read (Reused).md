
----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1305.92 | 0.148493 | 74.206ms | 905 | 640 | 616.386 | 660.894 | 0.213234 | 1(Win) | true |
| Glaze | 1192.78 | 0.120946 | 74.5628ms | 905 | 640 | 490.159 | 723.583 | 0.372148 | 2(Loss) | true |
| Jsonifier (two-stage) | 867.907 | 1.48811 | 83.8253ms | 905 | 30 | 6569.63 | 994.433 | 0.698711 | 3(Loss) | true |
| simdjson (ondemand) | 280.874 | 0.209671 | 326.796ms | 905 | 40 | 1660.4 | 3072.82 | 0.296618 | 4(Loss) | true |
