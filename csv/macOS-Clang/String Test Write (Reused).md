
----
### String Test Write (Reused) Results [(View the data used in the following test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 7889.29 | 0.0752892 | 127.415ms | 9578 | 640 | 486.317 | 1157.81 | 0.0226773 | 1(Win) | true |
| Glaze | 4296.94 | 0.0643801 | 255.541ms | 9578 | 320 | 599.357 | 2125.77 | 0.0473582 | 2(Loss) | true |
