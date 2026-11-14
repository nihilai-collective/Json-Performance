
----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 2673.62 | 0.0467119 | 157.102ms | 3808 | 1280 | 515.301 | 1358.31 | 0.0110994 | 1(Win) | true |
| Jsonifier | 2635.91 | 0.0729618 | 158.4ms | 3808 | 640 | 646.703 | 1377.74 | 0.182128 | 2(Loss) | true |
| Glaze | 2387.91 | 0.240074 | 170.121ms | 3808 | 40 | 533.225 | 1520.83 | 0.00931425 | 3(Loss) | true |
| simdjson (ondemand) | 1163.19 | 0.0864109 | 329.819ms | 3808 | 160 | 1164.54 | 3122.11 | 0.0406542 | 4(Loss) | true |
