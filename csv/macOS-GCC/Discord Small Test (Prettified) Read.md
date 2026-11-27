
----
### Discord Small Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Discord%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1886.82 | 0.227732 | 356.658ms | 6701 | 4890 | 290920 | 3386.95 | 0.208529 | 1(Win) | true |
| Jsonifier (two-stage) | 1761.36 | 0.294566 | 368.235ms | 6701 | 2560 | 292407 | 3628.2 | 0.640815 | 2(Loss) | true |
| Glaze | 1546.13 | 0.145845 | 418.161ms | 6701 | 4890 | 177698 | 4133.27 | 0.254007 | 3(Loss) | true |
| simdjson (reflection) | 1423.54 | 0.339143 | 457.088ms | 6701 | 1280 | 296698 | 4489.2 | 0.0445712 | 4(Loss) | true |
| simdjson (ondemand) | 1249.3 | 0.128458 | 517.132ms | 6701 | 4890 | 211144 | 5115.34 | 0.126068 | 5(Loss) | true |
