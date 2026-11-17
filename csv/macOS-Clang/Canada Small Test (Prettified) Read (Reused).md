
----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 1327.25 | 0.212298 | 980.084ms | 11579 | 4890 | 1.52559e+06 | 8319.91 | 1.00704 | 1(Win) | true |
| Jsonifier | 1279.71 | 0.285624 | 1000.05ms | 11579 | 4890 | 2.97041e+06 | 8628.98 | 1.47037 | 2(Loss) | true |
| Glaze | 1072.31 | 0.234023 | 1265.97ms | 11579 | 640 | 371708 | 10298 | 0.350626 | 3(Loss) | true |
| simdjson (ondemand) | 1005.79 | 0.348331 | 1243.29ms | 11579 | 2560 | 3.74417e+06 | 10979.1 | 0.103261 | 4(Loss) | true |
