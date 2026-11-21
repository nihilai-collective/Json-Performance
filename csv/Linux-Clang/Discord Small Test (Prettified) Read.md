
----
### Discord Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 2330.92 | 0.146379 | 281.615ms | 6701 | 40 | 644.233 | 2741.65 | 0.0796992 | 1.05206 | 1(Win) | true |
| Glaze | 1858.83 | 0.125879 | 346.508ms | 6701 | 4890 | 91583.4 | 3437.95 | 0.0140516 | 1.322 | 2(Loss) | true |
| Jsonifier | 1738.05 | 0.287219 | 374.02ms | 6701 | 1280 | 142755 | 3676.86 | 0.0120035 | 1.41269 | 3(Loss) | true |
| simdjson (ondemand) | 1112.56 | 0.276144 | 587.27ms | 6701 | 1280 | 322042 | 5744.02 | 0.194042 | 2.21504 | 4(Loss) | true |
