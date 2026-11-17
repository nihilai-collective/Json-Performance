
----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1451.48 | 0.0616236 | 5049.81ms | 124597 | 640 | 1.6288e+06 | 81864.7 | 0.0951406 | 2.09331 | 1(Win) | true |
| Jsonifier | 1426.07 | 0.0344941 | 5130.52ms | 124597 | 2560 | 2.11478e+06 | 83323.6 | 0.0078753 | 2.13064 | 2(Loss) | true |
| Glaze | 1284 | 0.0398191 | 5623.7ms | 124597 | 1280 | 1.73812e+06 | 92543 | 0.0019417 | 2.36631 | 3(Loss) | true |
| simdjson (ondemand) | 1126.12 | 0.0850901 | 6194.94ms | 124597 | 320 | 2.57963e+06 | 105518 | 0.00355404 | 2.69848 | 4(Loss) | true |
