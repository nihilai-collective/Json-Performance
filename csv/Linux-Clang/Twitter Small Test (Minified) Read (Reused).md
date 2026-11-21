
----
### Twitter Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 2441.01 | 0.140961 | 122.297ms | 2889 | 30 | 75.9414 | 1128.7 | 0.239787 | 0.991116 | 1(Win) | true |
| Glaze STATISTICAL TIE | 2389.05 | 0.211104 | 123.225ms | 2889 | 4890 | 28983 | 1153.25 | 0.00987892 | 1.01237 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 2382.43 | 0.0494989 | 123.654ms | 2889 | 320 | 104.856 | 1156.45 | 0.0199925 | 1.01581 | 2(Tie) | true |
| simdjson (ondemand) | 1091.34 | 0.19008 | 260.73ms | 2889 | 4890 | 112604 | 2524.56 | 0.305252 | 2.24467 | 4(Loss) | true |
