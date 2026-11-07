
----
### Discord Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Discord%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Glaze | 1807.48 | 0.193192 | 412.016ms | 6701 | 160 | 7465.02 | 3535.62 | 0.301418 | 1.36049 | 1(Win) | true |
| Jsonifier (two-stage) | 1522.07 | 0.293075 | 475.313ms | 6701 | 2560 | 387618 | 4198.59 | 0.272783 | 1.61542 | 2(Loss) | true |
| Jsonifier | 1461.61 | 0.215229 | 546.89ms | 6701 | 4890 | 433041 | 4372.29 | 0.289976 | 1.68337 | 3(Loss) | true |
| simdjson (ondemand) | 1299.56 | 0.0817369 | 550.363ms | 6701 | 160 | 2584.91 | 4917.5 | 0.050813 | 1.89801 | 4(Loss) | true |
