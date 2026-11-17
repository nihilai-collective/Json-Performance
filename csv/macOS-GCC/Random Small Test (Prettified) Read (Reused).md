
----
### Random Small Test (Prettified) Read (Reused) Results [(View the data used in the following test)](./json/Random%20Small%20Test%20%28Prettified%29.json):

<p align="left"><a href="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png" target="_blank"><img src="./graphs/macOS-GCC/Random%20Small%20Test%20%28Prettified%29%20Read%20%28Reused%29_Results.png?raw=true" 
alt="" width="1200"/></a></p>

| Library | Throughput (MB/s) | RSE (%) | Window Duration | File Size (Bytes) | Window Samples (k) | Variance | Latency / Run (ns) | Mean Convergence (%) | Position | Converged |
| ------- | ----------- | ------- | --------- | --------------- | -------------------- | ---------- | ---- | ---------------- | -------- | --------- |
| Jsonifier | 1910.34 | 0.923775 | 512.051ms | 8051 | 30 | 41355.5 | 4019.2 | 0.211864 | 1(Win) | true |
| Jsonifier (two-stage) | 1854.33 | 0.14733 | 557.399ms | 8051 | 4890 | 181977 | 4140.6 | 0.385572 | 2(Loss) | true |
| Glaze STATISTICAL TIE | 1454.93 | 0.156902 | 662.944ms | 8051 | 4890 | 335262 | 5277.26 | 1.5399 | 3(Tie) | true |
| simdjson (reflection) STATISTICAL TIE | 1450.33 | 0.403634 | 616.045ms | 8051 | 640 | 292229 | 5294 | 0.022662 | 3(Tie) | true |
| simdjson (ondemand) | 1358.1 | 0.221767 | 666.112ms | 8051 | 2560 | 402409 | 5653.5 | 0.224136 | 5(Loss) | true |
