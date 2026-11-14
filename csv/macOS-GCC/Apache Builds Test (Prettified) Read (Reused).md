
----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1811.32 | 0.524063 | 8918.94ms | 124597 | 640 | 7.56433e+07 | 65601.2 | 0.311824 | 1(Win) | true |
| Glaze STATISTICAL TIE | 1676.26 | 0.321365 | 9662.96ms | 124597 | 640 | 3.3213e+07 | 70886.8 | 0.55386 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1663.2 | 0.342262 | 9414.81ms | 124597 | 1280 | 7.65338e+07 | 71443.6 | 1.13302 | 2(Tie) | true |
| simdjson (reflection) | 1302.67 | 0.433423 | 5727.06ms | 124597 | 640 | 1.00035e+08 | 91216.8 | 0.248458 | 4(Loss) | true |
| simdjson (ondemand) | 1136.84 | 0.197147 | 6436.32ms | 124597 | 1280 | 5.43516e+07 | 104523 | 0.389778 | 5(Loss) | true |
