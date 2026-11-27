
----
### Canada Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 743.978 | 0.133632 | 599.733ms | 4630 | 2560 | 161028 | 5935 | 0.131251 | 1(Win) | true |
| Jsonifier (two-stage) | 613.807 | 0.114189 | 723.355ms | 4630 | 4890 | 329957 | 7193.65 | 0.156666 | 2(Loss) | true |
| simdjson (reflection) | 592.32 | 0.212469 | 754.015ms | 4630 | 1280 | 321107 | 7454.6 | 0.00804937 | 3(Loss) | true |
| Glaze | 532.118 | 0.201221 | 848.19ms | 4630 | 1280 | 356864 | 8298 | 0.0963159 | 4(Loss) | true |
| simdjson (ondemand) | 482.802 | 0.633786 | 1009.95ms | 4630 | 40 | 134391 | 9145.6 | 0.163551 | 5(Loss) | true |
