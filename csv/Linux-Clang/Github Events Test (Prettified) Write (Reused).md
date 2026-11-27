
----
### Github Events Test (Prettified) Write (Reused) Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16650.3 | 0.11052 | 453.029ms | 78778 | 30 | 746.051 | 4512.13 | 0.0066483 | 0.147757 | 1(Win) | true |
| Glaze | 6021.33 | 0.0360026 | 1268.79ms | 78778 | 40 | 807.148 | 12477.1 | 0.117877 | 0.410337 | 2(Loss) | true |
