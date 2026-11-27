
----
### Apache Builds Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2823.2 | 0.0642408 | 5477.36ms | 124597 | 4890 | 3.57488e+06 | 42088.7 | 0.0788225 | 0.876419 | 1(Win) | true |
| Jsonifier (two-stage) | 2348.95 | 0.268414 | 6309.55ms | 124597 | 160 | 2.94984e+06 | 50586.3 | 0.108336 | 1.05348 | 2(Loss) | true |
| Glaze | 2217.97 | 0.191066 | 6591.15ms | 124597 | 320 | 3.35291e+06 | 53573.7 | 0.0864067 | 1.11571 | 3(Loss) | true |
| simdjson (ondemand) | 1842.44 | 0.0623278 | 7694.41ms | 124597 | 1280 | 2.06825e+06 | 64493.2 | 0.0934133 | 1.34319 | 4(Loss) | true |
