
----
### Twitter Small Reverse Test (Prettified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Small%20Reverse%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Small%20Reverse%20Test%20%28Prettified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (generic) | 812.789 | 0.370635 | 432.845ms | 3770 | 2560 | 688113 | 4423.48 | 0.31038 | 1(Win) | true |
| simdjson (ondemand) | 281.459 | 0.0958661 | 1283.57ms | 3770 | 4890 | 733317 | 12774 | 0.161845 | 2(Loss) | true |
