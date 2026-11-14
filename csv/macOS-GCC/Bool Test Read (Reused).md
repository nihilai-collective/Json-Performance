
----
### Bool Test Read (Reused) Results [(View the data used in the following test)](./json/Bool%20Test.json):

<p align="left"><a href="./graphs/macOS-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Bool%20Test%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1500.48 | 2.41943 | 61.4572ms | 905 | 1280 | 247899 | 575.2 | 0.621977 | 1(Win) | true |
| Glaze | 1304.53 | 2.85567 | 66.945ms | 905 | 640 | 228447 | 661.6 | 3.16159 | 2(Loss) | true |
| Jsonifier (two-stage) | 328.74 | 0.472077 | 292.211ms | 905 | 2560 | 393240 | 2625.4 | 1.5081 | 3(Loss) | true |
| simdjson (ondemand) | 147.868 | 1.65217 | 548.872ms | 905 | 80 | 743958 | 5836.8 | 2.47191 | 4(Loss) | true |
