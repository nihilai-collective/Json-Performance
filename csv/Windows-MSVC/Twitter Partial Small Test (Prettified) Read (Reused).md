
----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier STATISTICAL TIE | 6939.35 | 1.50077 | 60.9493ms | 3808 | 30 | 1850.57 | 523.333 | 0 | 0.340651 | 1(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 6925.56 | 0.458424 | 57.2327ms | 3808 | 320 | 1849.14 | 524.375 | 0.94451 | 0.340619 | 1(Tie) | true |
| simdjson (ondemand) | 5117.17 | 0.233355 | 75.8999ms | 3808 | 320 | 877.645 | 709.688 | 0.0440141 | 0.465858 | 3(Loss) | true |
| Glaze | 3502.44 | 0.369013 | 109.772ms | 3808 | 160 | 2342.37 | 1036.88 | 0.0603136 | 0.686026 | 4(Loss) | true |
