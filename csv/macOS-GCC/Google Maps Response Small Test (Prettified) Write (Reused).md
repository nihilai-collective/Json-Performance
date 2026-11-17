
----
### Google Maps Response Small Test (Prettified) Write (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Write%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 18394.9 | 1.6334 | 62.273ms | 11521 | 2560 | 243673 | 597.3 | 3.48233 | 1(Win) | true |
| Glaze | 2880.47 | 0.707414 | 421.462ms | 11521 | 640 | 465993 | 3814.4 | 1.31747 | 2(Loss) | true |
| simdjson (reflection) | 308.732 | 0.129957 | 3567.48ms | 11521 | 2560 | 5.47591e+06 | 35588.4 | 0.439774 | 3(Loss) | true |
