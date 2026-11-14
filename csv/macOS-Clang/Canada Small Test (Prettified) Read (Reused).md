
----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-Clang/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1827.28 | 0.112687 | 725.78ms | 11579 | 80 | 3709.96 | 6043.2 | 0.0948244 | 1(Win) | true |
| Jsonifier (two-stage) | 1789.45 | 0.125871 | 759.595ms | 11579 | 4890 | 295026 | 6170.93 | 0.174788 | 2(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 1174.62 | 0.105341 | 1049.21ms | 11579 | 4890 | 479572 | 9401.03 | 0.00894083 | 3(Tie) | true |
| Glaze STATISTICAL TIE | 1174.19 | 0.0308108 | 1061.16ms | 11579 | 160 | 1343.35 | 9404.41 | 0.120034 | 3(Tie) | true |
