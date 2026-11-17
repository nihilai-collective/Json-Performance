
----
### Discord Small Test (Minified) Read Results [(View the data used in the following test)](./json/Discord%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Discord%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 1807.71 | 0.20584 | 264.197ms | 4857 | 40 | 1112.75 | 2562.35 | 0.294214 | 1.35473 | 1(Win) | true |
| Glaze STATISTICAL TIE | 1559.73 | 0.261888 | 301.338ms | 4857 | 2560 | 154849 | 2969.74 | 0.145227 | 1.572 | 2(Tie) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1554.32 | 0.609241 | 302.569ms | 4857 | 320 | 105483 | 2980.08 | 0.176376 | 1.57792 | 2(Tie) | true |
| simdjson (ondemand) | 771.277 | 0.130797 | 600.209ms | 4857 | 4890 | 301732 | 6005.62 | 0.337752 | 3.19491 | 4(Loss) | true |
