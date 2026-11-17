
----
### Twitter Partial Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 4261.06 | 0.0728322 | 95.4401ms | 3808 | 1280 | 493.19 | 852.273 | 0.03647 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 4258.06 | 0.197922 | 94.5893ms | 3808 | 160 | 455.909 | 852.875 | 0.0953569 | 1(Tie) | true |
| simdjson (ondemand) | 4177.28 | 0.678837 | 104.083ms | 3808 | 30 | 1044.86 | 869.367 | 0.79224 | 3(Loss) | true |
| Glaze | 2502.67 | 0.273719 | 155.248ms | 3808 | 80 | 1262.08 | 1451.09 | 0.583118 | 4(Loss) | true |
