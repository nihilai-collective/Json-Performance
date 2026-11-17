
----
### Canada Small Test (Minified) Read Results [(View the data used in the following test)](./json/Canada%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png" target="_blank"><img src="./graphs/Linux-Clang/Canada%20Small%20Test%20%28Minified%29%20Read_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Cycles/Byte | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | ----------- | -------- | --------- |
| Jsonifier | 905.09 | 0.219462 | 492.564ms | 4630 | 2560 | 293452 | 4878.54 | 0.081429 | 2.72088 | 1(Win) | true |
| Jsonifier (two-stage) | 841.873 | 0.0478056 | 546.824ms | 4630 | 30 | 188.602 | 5244.87 | 0.456765 | 2.92662 | 2(Loss) | true |
| simdjson (ondemand) STATISTICAL TIE | 696.324 | 0.0907922 | 643.348ms | 4630 | 80 | 2651.72 | 6341.18 | 0.0532519 | 3.53983 | 3(Tie) | true |
| Glaze STATISTICAL TIE | 693.119 | 0.217176 | 672.275ms | 4630 | 2560 | 490014 | 6370.5 | 0.684725 | 3.5571 | 3(Tie) | true |
