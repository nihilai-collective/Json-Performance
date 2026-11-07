
----
### Instruments Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Instruments%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Instruments%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1967.37 | 0.145572 | 414.906ms | 7932 | 80 | 2506.33 | 3845 | 0.324044 | 1.24947 | 1(Win) | true |
| Jsonifier | 1717.91 | 0.17159 | 471.621ms | 7932 | 30 | 1712.64 | 4403.33 | 0 | 1.43261 | 2(Loss) | true |
| Glaze | 1475.83 | 0.069726 | 542.525ms | 7932 | 160 | 2043.63 | 5125.62 | 0.207722 | 1.66629 | 3(Loss) | true |
| simdjson (ondemand) | 1240.09 | 0.13614 | 670.036ms | 7932 | 30 | 2068.97 | 6100 | 0.109409 | 1.98692 | 4(Loss) | true |
