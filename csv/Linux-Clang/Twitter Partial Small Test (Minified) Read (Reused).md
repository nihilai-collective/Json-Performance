
----
### Twitter Partial Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Twitter%20Partial%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Twitter%20Partial%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| simdjson (ondemand) | 6646.15 | 0.3572 | 44.6476ms | 2889 | 4890 | 10722.2 | 414.55 | 0.223595 | 0.346543 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 6554.6 | 0.477815 | 45.2807ms | 2889 | 2560 | 10326.7 | 420.341 | 0.590603 | 0.352943 | 2(Tie) | true |
| Jsonifier STATISTICAL TIE | 6479.28 | 0.624194 | 45.8477ms | 2889 | 2560 | 18035.2 | 425.227 | 0.0141488 | 0.357205 | 2(Tie) | true |
| Glaze | 3144.96 | 0.327546 | 91.2548ms | 2889 | 2560 | 21079 | 876.057 | 0.120401 | 0.762903 | 4(Loss) | true |
