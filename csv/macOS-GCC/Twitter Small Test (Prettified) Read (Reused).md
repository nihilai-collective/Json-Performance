
----
### Twitter Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Twitter%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier (two-stage) | 2355.81 | 0.858876 | 181.887ms | 3808 | 4890 | 857205 | 1541.55 | 2.55694 | 1(Win) | true |
| Jsonifier STATISTICAL TIE | 2217.9 | 1.04867 | 176.641ms | 3808 | 2560 | 754787 | 1637.4 | 2.61687 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 2169.93 | 3.61961 | 193.379ms | 3808 | 80 | 293574 | 1673.6 | 0.191571 | 2(Tie) | true |
| simdjson (reflection) | 1739.93 | 0.771773 | 230.759ms | 3808 | 1280 | 332137 | 2087.2 | 0.928433 | 4(Loss) | true |
| simdjson (ondemand) | 1343.04 | 1.74815 | 291.1ms | 3808 | 160 | 357511 | 2704 | 1.31894 | 5(Loss) | true |
