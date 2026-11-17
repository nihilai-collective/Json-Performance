
----
### Marine IK Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Marine%20IK%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Marine%20IK%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 660.631 | 0.133678 | 838.336ms | 4604 | 80 | 6314.87 | 6646.25 | 0.0188111 | 3.73078 | 1(Win) | true |
| Jsonifier (two-stage) | 566.377 | 0.220739 | 916.543ms | 4604 | 4890 | 1.43195e+06 | 7752.29 | 0.664891 | 4.35531 | 2(Loss) | true |
| simdjson (ondemand) | 196.668 | 0.102661 | 2429.74ms | 4604 | 4890 | 2.56875e+06 | 22325.5 | 0.810843 | 12.5727 | 3(Loss) | true |
| Glaze | 165.957 | 0.132694 | 2851.68ms | 4604 | 2560 | 3.15521e+06 | 26457 | 0.0658931 | 14.9019 | 4(Loss) | true |
