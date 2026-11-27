
----
### Apache Builds Small Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Apache%20Builds%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Apache%20Builds%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 2056.54 | 0.513979 | 148.917ms | 2632 | 4890 | 192440 | 1220.53 | 1.1879 | 1(Win) | true |
| Glaze | 1912.87 | 0.724136 | 158.126ms | 2632 | 2560 | 231143 | 1312.2 | 0.0304925 | 2(Loss) | true |
| Jsonifier (two-stage) | 1848.77 | 0.710782 | 166.441ms | 2632 | 2560 | 238408 | 1357.7 | 0.0221011 | 3(Loss) | true |
| simdjson (reflection) | 1283.27 | 0.76886 | 230.892ms | 2632 | 640 | 144748 | 1956 | 0.741656 | 4(Loss) | true |
| simdjson (ondemand) | 1186.35 | 0.490204 | 240.543ms | 2632 | 1280 | 137693 | 2115.8 | 0.122734 | 5(Loss) | true |
