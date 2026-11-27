
----
### Google Maps Response Test (Minified) Read Results [(Here is the data we used for this test)](./json/Google%20Maps%20Response%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Google%20Maps%20Response%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2233.34 | 0.0807593 | 511.105ms | 11812 | 30 | 497.789 | 5043.93 | 0.0726418 | 1.10255 | 1(Win) | true |
| Jsonifier (two-stage) | 1845.02 | 0.0653387 | 615.031ms | 11812 | 30 | 477.43 | 6105.53 | 0.120801 | 1.33595 | 2(Loss) | true |
| Glaze | 1691.06 | 0.086076 | 732.089ms | 11812 | 30 | 986.317 | 6661.4 | 0.498868 | 1.45854 | 3(Loss) | true |
| simdjson (ondemand) | 1007.78 | 0.157929 | 1124.53ms | 11812 | 1280 | 398890 | 11177.9 | 0.0201809 | 2.45101 | 4(Loss) | true |
