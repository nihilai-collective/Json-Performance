
----
### Github Events Small Test (Minified) Read (Reused) Results [(View the data used in the following test)](./json/Github%20Events%20Small%20Test%20%28Minified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Github%20Events%20Small%20Test%20%28Minified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1888.59 | 1.05359 | 113.428ms | 1691 | 2560 | 207205 | 853.9 | 0.939675 | 1(Win) | true |
| Jsonifier (two-stage) STATISTICAL TIE | 1615.25 | 1.42843 | 133.729ms | 1691 | 30 | 6101.63 | 998.4 | 0.847458 | 2(Tie) | true |
| Glaze STATISTICAL TIE | 1553.03 | 1.78808 | 130.802ms | 1691 | 320 | 110320 | 1038.4 | 1.66667 | 2(Tie) | true |
| simdjson (ondemand) | 1337.64 | 0.70434 | 148.753ms | 1691 | 2560 | 184591 | 1205.6 | 0.266134 | 4(Loss) | true |
| simdjson (reflection) | 1165.24 | 0.726016 | 174.985ms | 1691 | 4890 | 493690 | 1383.97 | 0.247185 | 5(Loss) | true |
