
----
### Github Events Test (Prettified) Write Results [(Here is the data we used for this test)](./json/Github%20Events%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Github%20Events%20Test%20%28Prettified%29%20Write_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 16541.7 | 0.0955528 | 457.001ms | 78778 | 30 | 565.013 | 4541.77 | 0.169251 | 0.148847 | 1(Win) | true |
| Glaze | 5168.96 | 0.120263 | 1470.12ms | 78778 | 2560 | 782181 | 14534.6 | 0.126282 | 0.478123 | 2(Loss) | true |
