
----
### Twitter Partial Small Test (Prettified) Read Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 4118.56 | 0.0819002 | 94.4063ms | 3808 | 640 | 333.774 | 881.763 | 0.0138198 | 1(Win) | true |
| simdjson (ondemand) STATISTICAL TIE | 3987.75 | 0.156556 | 101.315ms | 3808 | 320 | 650.473 | 910.688 | 0.567077 | 2(Tie) | true |
| Jsonifier STATISTICAL TIE | 3970.53 | 0.324049 | 96.2695ms | 3808 | 80 | 702.766 | 914.638 | 0.227713 | 2(Tie) | true |
| Glaze | 2122.24 | 0.475932 | 161.441ms | 3808 | 1280 | 84899 | 1711.2 | 1.57552 | 4(Loss) | true |
