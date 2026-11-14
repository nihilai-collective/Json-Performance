
----
### Instruments Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Instruments%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2786.32 | 1.25267 | 6801.23ms | 183677 | 80 | 4.96145e+07 | 62867.2 | 2.9156 | 1(Win) | true |
| Jsonifier (two-stage) | 2439.53 | 0.130195 | 8042.02ms | 183677 | 4890 | 4.27358e+07 | 71803.9 | 2.1609 | 2(Loss) | true |
| Glaze | 2075.08 | 0.165126 | 8935.43ms | 183677 | 320 | 6.2176e+06 | 84415.2 | 0.141406 | 3(Loss) | true |
| simdjson (ondemand) | 1776.88 | 0.072846 | 5136.38ms | 183677 | 2560 | 1.32021e+07 | 98581.6 | 0.11409 | 4(Loss) | true |
| simdjson (reflection) | 1561.98 | 0.468856 | 5616.87ms | 183677 | 1280 | 3.53871e+08 | 112145 | 0.401626 | 5(Loss) | true |
