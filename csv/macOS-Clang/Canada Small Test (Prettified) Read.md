
----
### Canada Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1158.07 | 0.760929 | 1022.83ms | 11579 | 320 | 1.68467e+06 | 9535.38 | 2.37385 | 1(Win) | true |
| Jsonifier (two-stage) | 1091.45 | 0.251134 | 1001.74ms | 11579 | 4890 | 3.15688e+06 | 10117.4 | 1.95703 | 2(Loss) | true |
| Glaze | 960.101 | 0.302895 | 1178.23ms | 11579 | 640 | 776735 | 11501.5 | 0.0287923 | 3(Loss) | true |
| simdjson (ondemand) | 830.528 | 0.528466 | 1308.3ms | 11579 | 640 | 3.15972e+06 | 13295.9 | 0.642718 | 4(Loss) | true |
