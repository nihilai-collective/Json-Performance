
----
### Google Maps Response Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2958.73 | 0.0402771 | 357.152ms | 9378 | 320 | 474.327 | 3022.77 | 0.0476818 | 1(Win) | true |
| Jsonifier (two-stage) | 2405.34 | 0.45575 | 445.184ms | 9378 | 1280 | 367563 | 3718.21 | 2.93727 | 2(Loss) | true |
| Glaze | 1621.14 | 0.514873 | 565.738ms | 9378 | 640 | 516370 | 5516.84 | 1.59449 | 3(Loss) | true |
| simdjson (ondemand) | 1453.98 | 2.19463 | 600.946ms | 9378 | 40 | 728928 | 6151.07 | 3.21752 | 4(Loss) | true |
