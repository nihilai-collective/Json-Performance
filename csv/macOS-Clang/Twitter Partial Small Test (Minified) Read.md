
----
### Twitter Partial Small Test (Minified) Read Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 4033.47 | 0.2426 | 71.5144ms | 2889 | 160 | 439.378 | 683.075 | 0.191777 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 4020.45 | 0.173695 | 71.5188ms | 2889 | 320 | 453.39 | 685.288 | 0.364309 | 1(Tie) | true |
| simdjson (ondemand) | 3544.27 | 0.106854 | 81.1655ms | 2889 | 640 | 441.576 | 777.358 | 0.0190988 | 3(Loss) | true |
| Glaze | 2228.33 | 0.125492 | 130.514ms | 2889 | 160 | 385.202 | 1236.42 | 0.168105 | 4(Loss) | true |
