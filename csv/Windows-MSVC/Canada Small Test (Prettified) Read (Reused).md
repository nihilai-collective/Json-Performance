
----
### Canada Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/Windows-MSVC/Canada%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier (two-stage) | 1680.84 | 0.146287 | 838.832ms | 11579 | 4890 | 451656 | 6569.69 | 0.36071 | 1.46672 | 1(Win) | true |
| Jsonifier | 1592.2 | 0.178191 | 853.232ms | 11579 | 4890 | 746837 | 6935.42 | 0.174191 | 1.54895 | 2(Loss) | true |
| simdjson (ondemand) | 454.521 | 0.206041 | 2666.26ms | 11579 | 640 | 1.6037e+06 | 24295 | 0.0629877 | 5.441 | 3(Loss) | true |
| Glaze | 446.842 | 0.0697691 | 2703.61ms | 11579 | 40 | 11891 | 24712.5 | 0.312626 | 5.53484 | 4(Loss) | true |
