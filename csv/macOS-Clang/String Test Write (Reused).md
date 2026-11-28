
----
### String Test Write (Reused) Results [(Here is the data we used for this test)](./json/String%20Test.json):

<p align="left"><a href="./graphs/macOS-Clang/String%20Test%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/String%20Test%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 3335.43 | 0.161004 | 141.437ms | 4215 | 160 | 602.401 | 1205.16 | 0.0849785 | 1(Win) | true |
| Glaze | 1965.09 | 0.0635525 | 231.401ms | 4215 | 320 | 540.81 | 2045.57 | 0.0129871 | 2(Loss) | true |
