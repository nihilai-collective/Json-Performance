
----
### Twitter Test (Minified) Read Results [(View the data used in the following test)](./json/Twitter%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1712.94 | 0.253905 | 6496.1ms | 466906 | 1280 | 5.57603e+08 | 259948 | 2.01632 | 1(Win) | true |
| Glaze | 1521.09 | 0.0660653 | 7565.67ms | 466906 | 1280 | 4.7875e+07 | 292736 | 0.227273 | 2(Loss) | true |
| Jsonifier (two-stage) | 1383.66 | 1.58304 | 8128.2ms | 466906 | 40 | 1.03812e+09 | 321811 | 0.136082 | 3(Loss) | true |
| simdjson (reflection) | 1207.91 | 0.076221 | 9416.77ms | 466906 | 640 | 5.05264e+07 | 368633 | 0.109388 | 4(Loss) | true |
| simdjson (ondemand) | 940.786 | 0.106875 | 6053.31ms | 466906 | 640 | 1.6376e+08 | 473302 | 0.712924 | 5(Loss) | true |
