
----
### Google Maps Response Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Google%20Maps%20Response%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1931.17 | 0.0964766 | 231.268ms | 4390 | 4890 | 21391.5 | 2167.93 | 0.0710755 | 1(Win) | true |
| Jsonifier (two-stage) | 1461.09 | 0.0297846 | 318.714ms | 4390 | 640 | 466.167 | 2865.43 | 0.0393858 | 2(Loss) | true |
| Glaze | 1123.63 | 0.222541 | 393.145ms | 4390 | 40 | 2750.21 | 3726 | 0.376995 | 3(Loss) | true |
| simdjson (ondemand) | 797.454 | 0.215477 | 531.718ms | 4390 | 4890 | 625790 | 5250 | 2.01436 | 4(Loss) | true |
