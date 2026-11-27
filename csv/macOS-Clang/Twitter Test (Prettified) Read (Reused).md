
----
### Twitter Test (Prettified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2708.55 | 0.695246 | 6507.73ms | 631514 | 160 | 3.82375e+08 | 222355 | 2.09245 | 1(Win) | true |
| Glaze | 2298.18 | 0.12554 | 7757.71ms | 631514 | 160 | 1.73173e+07 | 262059 | 0.430733 | 2(Loss) | true |
| Jsonifier (two-stage) | 2134.91 | 1.22546 | 7910.04ms | 631514 | 80 | 9.56088e+08 | 282101 | 2.06364 | 3(Loss) | true |
| simdjson (ondemand) DID NOT CONVERGE | 1118.96 | 0.221175 | 7519.48ms | 631514 | 640 | 9.06964e+08 | 538231 | 5.29213 | -(Loss) | false |
