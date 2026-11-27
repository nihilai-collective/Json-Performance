
----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2797.59 | 0.0935953 | 398.764ms | 9378 | 40 | 358.112 | 3196.88 | 0.66058 | 1(Win) | true |
| Jsonifier (two-stage) | 2319.66 | 0.280163 | 421.664ms | 9378 | 1280 | 149350 | 3855.55 | 1.12433 | 2(Loss) | true |
| simdjson (ondemand) | 1796.18 | 0.159421 | 516.673ms | 9378 | 30 | 1890.3 | 4979.2 | 0.0020084 | 3(Loss) | true |
| Glaze | 1701.81 | 1.21362 | 544.949ms | 9378 | 40 | 162713 | 5255.32 | 0.127494 | 4(Loss) | true |
