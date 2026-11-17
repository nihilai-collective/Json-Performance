
----
### Apache Builds Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Apache%20Builds%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Apache%20Builds%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1449.6 | 0.0913721 | 5176.11ms | 124597 | 2560 | 1.4361e+07 | 81970.7 | 0.178019 | 1.70731 | 1(Win) | true |
| Jsonifier | 1378.88 | 0.593377 | 5510.5ms | 124597 | 40 | 1.04588e+07 | 86175 | 0.117838 | 1.79492 | 2(Loss) | true |
| Glaze STATISTICAL TIE | 1275.58 | 0.636148 | 5787.38ms | 124597 | 30 | 1.0535e+07 | 93153.3 | 0.406272 | 1.94027 | 3(Tie) | true |
| simdjson (ondemand) STATISTICAL TIE | 1259.17 | 0.0758724 | 5852.49ms | 124597 | 2560 | 1.31236e+07 | 94367.6 | 0.192687 | 1.96564 | 3(Tie) | true |
