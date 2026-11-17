
----
### Github Events Small Test (Minified) Read Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1329.7 | 1.99292 | 124.744ms | 1691 | 320 | 186942 | 1212.8 | 3.41064 | 1(Win) | true |
| Glaze | 1155.7 | 1.00337 | 159.596ms | 1691 | 1280 | 250917 | 1395.4 | 1.5575 | 2(Loss) | true |
| simdjson (reflection) STATISTICAL TIE | 1093.48 | 1.36918 | 160.194ms | 1691 | 640 | 260957 | 1474.8 | 0.682687 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1074.54 | 2.6607 | 164.553ms | 1691 | 160 | 255127 | 1500.8 | 0.845666 | 3(Tie) | true |
| Jsonifier (two-stage) | 1036.68 | 1.28546 | 152.585ms | 1691 | 640 | 255913 | 1555.6 | 0.96054 | 5(Loss) | true |
