
----
### Github Events Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Github%20Events%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2448.12 | 0.119111 | 3094.24ms | 65103 | 1280 | 1.16801e+06 | 25361.1 | 0.0233602 | 1(Win) | true |
| Jsonifier (two-stage) | 2333 | 0.0346028 | 3464.03ms | 65103 | 30 | 2543.98 | 26612.5 | 0.18811 | 2(Loss) | true |
| Glaze | 2130.44 | 0.14672 | 3608.28ms | 65103 | 640 | 1.1701e+06 | 29142.8 | 0.0936733 | 3(Loss) | true |
| simdjson (ondemand) | 1224.02 | 0.088643 | 5704.93ms | 65103 | 1280 | 2.58776e+06 | 50723.9 | 0.255633 | 4(Loss) | true |
