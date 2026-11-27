
----
### Twitter Partial Test (Minified) Read (Reused) Results [(Here is the data we used for this test)](./json/Twitter%20Partial%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) STATISTICAL TIE | 10451.5 | 0.0645735 | 4344.3ms | 466906 | 4890 | 3.70101e+06 | 42604.1 | 0.0756659 | 0.236732 | 1(Tie) | true |
| Jsonifier STATISTICAL TIE | 10431.4 | 0.117982 | 4353.47ms | 466906 | 1280 | 3.24651e+06 | 42686.3 | 0.116557 | 0.23719 | 1(Tie) | true |
| simdjson (ondemand) | 8057 | 0.0547727 | 5585.77ms | 466906 | 4890 | 4.48074e+06 | 55265.8 | 0.0349884 | 0.3071 | 3(Loss) | true |
| Glaze | 3346.13 | 0.104108 | 6847.71ms | 466906 | 320 | 6.14179e+06 | 133072 | 0.0395878 | 0.739754 | 4(Loss) | true |
